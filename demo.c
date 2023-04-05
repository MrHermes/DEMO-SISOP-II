#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <wait.h>

int main(int argc, char** argv){
    pid_t child_id = fork();
    int status;

    if (child_id < 0){
            exit(EXIT_FAILURE);
    }
    if (child_id == 0){
        execlp("bash", "bash", "-c", "ps aux | grep daemon > output/daemon-process.txt",  NULL);
    }
    // sedangkan parent ga ngelakuin apa2 jadi dimatiin pada no 3
    else {
        wait(&status);
        execlp("bash", "bash", "-c", "cat output/daemon-process.txt | wc -l > output/total-daemon-process.txt",  NULL);
    }

    pid_t cid = fork();
    if (cid < 0){
        exit(EXIT_FAILURE);
    }
    if (cid == 0){
        execlp("chmod", "chmod", "u+x", "daemon-process.txt", NULL);
        exit(0);
    }else {
        execlp("chown", "chown", "root:root", "total-daemon-process.txt", NULL);
        exit(0);
    }

    cid = fork();
    if (cid < 0){
        exit(EXIT_FAILURE);
    }
    if (cid == 0){
        execlp("rm", "rm", "output/daemon-process.txt",  NULL);
        // execlp("bash", "bash", "-c", "rm *daemon-process.txt",  NULL);
        exit(0);
    }else {
        execlp("rmdir", "rmdir", "ouput", NULL);
    }

}