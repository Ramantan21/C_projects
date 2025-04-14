#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define BUFFER_SIZE 4096
#define PERMS 0644
#define REPORT_FD 3
typedef struct{
    int filies_coppied;
    int files_skipped;
    int errors_count;
    char error_messages[10][256];
}SyncReport;


SyncReport report = {0};

void add_error(SyncReport *report, const char *message){
    if(report->errors_count < 10){
        strncpy(report->error_messages[report->errors_count],message,255);
        report->errors_count++;
    }
}

void send_report(int fd,const SyncReport *report){
    char buffer[2048];
    int len = 0;
    len += snprintf(buffer + len, sizeof(buffer) - len, "EXEC_REPORT_START\n");
    len += snprintf(buffer + len, sizeof(buffer) - len, "STATUS: %s\n",
                    (report->errors_count == 0) ? "SUCCESS" : "PARTIAL");
    len += snprintf(buffer + len,sizeof(buffer)- len, "DETAIL: %d files copied, %d skipped\n",
                    report->filies_coppied,report->files_skipped);

    if(report -> errors_count > 0){
        len += snprintf(buffer + len,sizeof(buffer) - len,"ERRORS:\n");
        for(int i = 0; i<report->errors_count; i++)
            len += snprintf(buffer + len,sizeof(buffer) - len,"- %s\n",report->error_messages[i]);
    }
    len += snprintf(buffer + len,sizeof(buffer) - len,"EXEC_REPORT_END\n");

    write(fd,buffer,len);
}

void sync_file(const char *source_path,const char *target_path){
    printf("[SYNC] Copying %s to %s\n", source_path, target_path);
    int source_fd, target_fd;
    ssize_t bytes_read,bytes_written;
    char error_msg[256];
    char buffer[BUFFER_SIZE];

    //ανοιγουμε το source αρχειο(μονο για διαβασμα)
    if((source_fd = open(source_path,O_RDONLY)) == -1 ){
        snprintf(error_msg,sizeof(error_msg),"OPEN SOURCE FAILED :%s [%s]",source_path,strerror(errno));
        add_error(&report,error_msg);
        report.files_skipped++;
        return ;
    }

    //Ανοιγουμε το target αρχειο(Το δημιουργουμε αν δεν υπαρχει με δικαιωματα 644)
    if((target_fd = open(target_path,O_WRONLY | O_CREAT | O_TRUNC,PERMS)) == -1){
        snprintf(error_msg,sizeof(error_msg),"OPEN TARGET FAILED :%s [%s]",target_path,strerror(errno));
        close(source_fd);
        report.files_skipped++;
        return;
    }
    //Αντιγραφη δεδομενων
    while((bytes_read = read(source_fd,buffer,BUFFER_SIZE)) > 0){
        bytes_written = write(target_fd,buffer,bytes_read);
        if(bytes_written != bytes_read){
            snprintf(error_msg,sizeof(error_msg),"WRITE ERROR: %s [%s]",target_path,strerror(errno));
            add_error(&report,error_msg);
            break;
            
        }
    }
    close(source_fd);
    close(target_fd);

    if(bytes_read == -1){
        snprintf(error_msg,sizeof(error_msg),"READ ERROR: %s [%s]",source_path,strerror(errno));
        add_error(&report,error_msg);
        report.files_skipped++;
        return;
    }

    report.filies_coppied++;
}



int main(int argc,char *argv[]){
    if(argc !=5){
        fprintf(stderr,"Usage: %s <source_dir> <target_dir> <filename> <operation>\n",argv[0]);
        fprintf(stderr,"Operations: ADDED, FULL, MODIFIED, DELETED");
        exit(EXIT_FAILURE);
    }
    int report_fd = 3;

    printf("\n[DEBUG] Worker started with args:\n");
    printf("Source Dir: '%s'\n", argv[1]);
    printf("Target Dir: '%s'\n", argv[2]);
    printf("Filename: '%s'\n", argv[3]);
    printf("Operation: '%s'\n\n", argv[4]);

    const char *source_dir = argv[1];
    const char *target_dir = argv[2];
    const char *filename = argv[3];
    const char *operation = argv[4]; // "ADDED", "MODIFIED", "DELETED"

    char source_path[512];
    char target_path[512];

    snprintf(source_path,sizeof(source_path),"%s/%s",source_dir,filename);
    snprintf(target_path,sizeof(target_path),"%s/%s",target_dir,filename);

    if(strcmp(operation,"DELETED") == 0){
        //διαγραφη αρχειου στον προορισμο
        if(unlink(target_path) == -1){
            fprintf(stderr,"Error deleting %s: %s\n",target_path,strerror(errno));
            exit(EXIT_FAILURE);
        }

        printf("Worker: Deleted %s\n",target_path);
    }else if(strcmp(operation,"FULL") == 0){
        

        printf("Worker: Full sync");
        exit(EXIT_FAILURE);
    }else{
        sync_file(source_path,target_path);
        printf("Worker: Synced %s -> %s (%s)\n",source_path,target_path,operation);
    }
    send_report(report_fd,&report);
    close(report_fd);
    

    return (report.errors_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}