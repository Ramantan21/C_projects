#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <sys/inotify.h>
#include <time.h>
#include <poll.h>
#define SERVER_STATUS "manager_log_file.txt"
#define FSS_IN "/tmp/fss_in" //pipe για να διαβασει εντολες απτον console
#define FSS_OUT "/tmp/fss_out" //pipe για να στειλει απαντηση στον console
#define PERMS 0666
#define EVENT_SIZE (sizeof(struct inotify_event)) // μεγεθος inotify
#define BUF_LEN (1024*(EVENT_SIZE+16)) // μεγεθος buffer για inotify
#define MAX_WORKERS 5 // default workers
#define MAX_SYNC_PAIRS 100 //μεγιστος αριθμος sync_pairs


const char* source_dir = "/home/ramantan21/hw1-Ramantan21-1/src";
const char* target_dir = "/home/ramantan21/hw1-Ramantan21-1/tmp";


char *timestamp(){
    static char buffer[32];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer,sizeof(buffer),"[%Y-%m-%d %H:%M:%S]",tm_info);
    return buffer;
}


//Δομη για αποθηκευση πληροφοριων συχγρονισμου
typedef struct{
    char source_dir[256];
    char target_dir[256];
    int is_active;
    int wd;
    time_t last_sync;
    int error_count;
}SyncPair;

typedef struct{
    SyncPair pairs[MAX_SYNC_PAIRS];
    int count;
}SyncList;

typedef struct{
    char source[256];
    char target[256];
    char filename[256];
    char operation[16];
}QueuedTask;

SyncList sync_list ={0};
QueuedTask task_queue[MAX_SYNC_PAIRS];
int queue_front = 0, queue_rear = 0;
int active_workers = 0;
FILE *log_file;
int inotify_fd;

void enqueue_task(const QueuedTask *task){
    if((queue_rear + 1) % MAX_SYNC_PAIRS != queue_front){
        task_queue[queue_rear] = *task;
        queue_rear = (queue_rear + 1) % MAX_SYNC_PAIRS;
    }
}

int dequeue_task(QueuedTask *task){
    if(queue_front == queue_rear) return 0;
    *task = task_queue[queue_front];
    queue_front = (queue_front + 1) % MAX_SYNC_PAIRS;
    return 1;
}

void worker(const char *source_dir,const char *target_dir,const char *filename, const char *operation){
    if(active_workers >= MAX_WORKERS){
        QueuedTask task = {0};
        strcpy(task.source,source_dir);
        strcpy(task.target,target_dir);
        strcpy(task.filename,filename);
        strcpy(task.operation,operation);
        enqueue_task(&task);
        return ;
    }
    pid_t pid = fork();
    if(pid == 0){
        //child process(worker)
        execl("./worker","worker",source_dir,target_dir,filename,operation,NULL);
        perror("execl failed");
        exit(EXIT_FAILURE);
    }else if(pid > 0){
        active_workers++;
        fprintf(log_file,"%s Worker spawned for %s-> %s (%s)\n",timestamp(),source_dir,target_dir,operation);
        fflush(log_file);
    }else{
        perror("fork failed");
    } 
}

void process_command(char *command_str,int write_fd){
    char buffer[512];
    char *cmd, *arg1, *arg2;

    cmd = strtok(command_str," ");
    arg1 = strtok(NULL," ");
    arg2 = strtok(NULL," ");

    if(cmd && strcmp(cmd,"add") == 0 && arg1 && arg2){
        if(sync_list.count < MAX_SYNC_PAIRS){
            strncpy(sync_list.pairs[sync_list.count].source_dir, arg1, sizeof(sync_list.pairs[sync_list.count].source_dir) - 1);

            strcpy(sync_list.pairs[sync_list.count].target_dir,arg2);
            sync_list.pairs[sync_list.count].is_active = 1;

            int wd = inotify_add_watch(inotify_fd,arg1,IN_CREATE | IN_MODIFY | IN_DELETE);
            if(wd == -1){
                snprintf(buffer,sizeof(buffer),"Error whatching dir: %s\n",strerror(errno));
            }else{
                sync_list.pairs[sync_list.count].wd = wd;
                sync_list.pairs[sync_list.count].last_sync = time(NULL);
                sync_list.pairs[sync_list.count].error_count = 0;
                sync_list.count++;
                snprintf(buffer,sizeof(buffer),"Added: %s -> %s",arg1,arg2);
            }
        }else{
            snprintf(buffer,sizeof(buffer),"Error: sync pair limit reached\n");
        }
        write(write_fd,buffer,strlen(buffer)+1);
        return;
    }

    if(cmd && strcmp(cmd,"cancel") == 0 && arg1){
        int found = 0;
        for(int i = 0; i<sync_list.count; i++){
            if(strcmp(sync_list.pairs[i].source_dir,arg1) == 0 && sync_list.pairs[i].is_active){
                sync_list.pairs[i].is_active = 0;
                inotify_rm_watch(inotify_fd,sync_list.pairs[i].wd);
                snprintf(buffer,sizeof(buffer),"Canceled: %s\n",arg1);
                write(write_fd,buffer,strlen(buffer) + 1);
                found = 1;
                break;
            }
        }
        if(!found){
            snprintf(buffer,sizeof(buffer),"Directory not monitored: %s\n",arg1);
            write(write_fd,buffer,strlen(buffer)+1);
        }

        return;
    }

    if(cmd && strcmp(cmd,"shutdown") == 0){
        snprintf(buffer,sizeof(buffer),"Shutingdown manager..\n");
        write(write_fd,buffer,strlen(buffer)+1);

        exit(0);
    }

}

void handler_inotify_events(int inotify_fd){
    char buffer[BUF_LEN];
    int lenght = read(inotify_fd,buffer,BUF_LEN);
    for(int i = 0; i < lenght;){
        struct inotify_event *event = (struct inotify_event *)&buffer[i];

        if(event->len){
            for(int j = 0; j<sync_list.count; j++){
                if(sync_list.pairs[j].wd == event->wd && sync_list.pairs[j].is_active){
                    char *operation = NULL;
                    if(event->mask & IN_CREATE) operation = "ADDED";
                    else if(event->mask & IN_MODIFY) operation = "MODIFIED";
                    else if(event->mask &IN_DELETE) operation = "DELETED";

                    if(operation){
                        QueuedTask task = {0};
                        strncpy(task.source,sync_list.pairs[j].source_dir,sizeof(task.source) - 1);
                        strncpy(task.target,sync_list.pairs[j].target_dir,sizeof(task.target) - 1);
                        strncpy(task.filename,event->name,sizeof(task.filename) - 1 );
                        strncpy(task.operation,operation,sizeof(task.operation) - 1);
                        enqueue_task(&task);
                    }
                    break;
                }
            }
        }
        i+=EVENT_SIZE + event->len;
    }
}
void handle_sigchld(int sig){
    while(waitpid(-1,NULL,WNOHANG) >0){
        active_workers--; //wait for any child process and return imidiately if no child has exite
        QueuedTask task;
        if(dequeue_task(&task)){
            worker(task.source,task.target,task.filename,task.operation);
        }
    } 
}

void cleanup_pipes(){
    unlink(FSS_IN); //διαγραφη pipe κατα το shutdown
    unlink(FSS_OUT);
    if(log_file){
        fprintf(log_file,"%s Manager shutting down\n",timestamp());
        fclose(log_file);
    }
}
int main(int argc,char* argv[]){
    if(argc != 7 || strcmp(argv[1],"-l") != 0 ||strcmp(argv[3],"-c")||strcmp(argv[5],"-n")){
        fprintf(stderr,"wrong usage of %s",argv[0]);
        exit(EXIT_FAILURE);
    }
    log_file = fopen(argv[2],"a");
    if(!log_file){
        perror("failed to open log file");
        exit(EXIT_FAILURE);
    }
    int fd[2];
    int inotify_fd = inotify_init();
    if(inotify_fd<0){
        perror("inotify_init failed");
        exit(EXIT_FAILURE);
    }
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigchld;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP; // Επανεκκίνηση syscalls
    sigaction(SIGCHLD, &sa, NULL);      
    unlink(FSS_IN);  // Διαγραφή παλιού pipe (αν υπάρχει)
    unlink(FSS_OUT);
    if (mkfifo(FSS_IN, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo(FSS_IN) failed");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(FSS_OUT, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo(FSS_OUT) failed");
        exit(EXIT_FAILURE);
    }
    fd[0] = open(FSS_IN, O_RDONLY | O_NONBLOCK);
    fd[1] = open(FSS_OUT, O_WRONLY | O_NONBLOCK); 
    if (fd[0] == -1 || fd[1] == -1) {
        perror("open pipes failed");
        exit(EXIT_FAILURE);
    }
    struct pollfd fds[2] = {
        {fd[0],POLLIN,0},
        {inotify_fd,POLLIN,0}
    };
     signal(SIGCHLD, handle_sigchld);
    while(1){
        int ret = poll(fds,2,1000);

        if(fds[0].revents & POLLIN){
            char command[256];
            ssize_t bytes = read(fd[0],command,sizeof(command));
            if(bytes > 0){
                command[bytes] = '\0';
                process_command(command,fd[1]);
            }
        }

        if(fds[1].revents & POLLIN){
            handler_inotify_events(inotify_fd);
        }
    }

    close(fd[0]);
    close(fd[1]);

    cleanup_pipes(fd[0],fd[1]);
    fclose(log_file);

    return EXIT_SUCCESS;

}