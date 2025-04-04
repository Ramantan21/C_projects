#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define FSS_IN "/tmp/fss_in"    // Pipe για εντολές προς τον manager
#define FSS_OUT "/tmp/fss_out"  // Pipe για απαντήσεις από τον manager
#define MAX_BUFFER 1024

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "-l") != 0) {
        fprintf(stderr, "Usage: %s -l <console-logfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *logfile = argv[2];
    FILE *log_fp = fopen(logfile, "a");
    if (!log_fp) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }

    printf("FSS Console started. Logging to: %s\n", logfile);
    printf("Available commands: add <source> <target>, cancel, status, sync, shutdown\n");

    char user_input[MAX_BUFFER];
    while (1) {
        printf("> ");
        if (!fgets(user_input, MAX_BUFFER, stdin)) {
            break;  // EOF (Ctrl+D)
        }

        // Αφαίρεση newline (\n)
        user_input[strcspn(user_input, "\n")] = '\0';

        // Έλεγχος για shutdown
        if (strcmp(user_input, "shutdown") == 0) {
            fprintf(log_fp, "[SHUTDOWN] User requested shutdown\n");
            break;
        }

        // Άνοιγμα pipe για εγγραφή (στέλνουμε εντολή στον manager)
        int write_fd = open(FSS_IN, O_WRONLY);
        if (write_fd == -1) {
            perror("Failed to open FSS_IN");
            continue;
        }

        write(write_fd, user_input, strlen(user_input) + 1);  // +1 για null terminator
        close(write_fd);

        // Άνοιγμα pipe για ανάγνωση (λαμβάνουμε απάντηση από manager)
        int read_fd = open(FSS_OUT, O_RDONLY);
        if (read_fd == -1) {
            perror("Failed to open FSS_OUT");
            continue;
        }

        char response[MAX_BUFFER];
        ssize_t bytes_read = read(read_fd, response, MAX_BUFFER - 1);
        close(read_fd);

        if (bytes_read > 0) {
            response[bytes_read] = '\0';
            printf("Response: %s\n", response);
            fprintf(log_fp, "[COMMAND] %s -> [RESPONSE] %s\n", user_input, response);
        }
    }

    fclose(log_fp);
    printf("Console terminated.\n");
    return 0;
}














































/*int main (){
int retval=0;
printf("I am process %lu and I will execute an ls -l .;\n",(long)getpid());
retval=execl ("/bin/ls", "ls", "-l", ".", NULL);
if (retval==-1) // do we ever get here ?
perror("execl ");
}*/