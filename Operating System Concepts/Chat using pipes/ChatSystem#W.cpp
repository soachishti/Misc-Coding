#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;
    char writefifo[] = "/tmp/myfifo1";
    char readfifo[] = "/tmp/myfifo2";
    char msg[120];

    /* create the FIFO (named pipe) */
    mkfifo(writefifo, 0666);
    printf("CHAT STARTED\n\n");
    while(1) {
        // Writing to Pipe
        fd = open(writefifo, O_WRONLY);
        printf("Enter Message: ");
        scanf("%s",msg);
        write(fd, msg, 120);
        close(fd);
                
        // Reading from pipe
        printf("Waiting...");
        fd = open(readfifo, O_RDONLY);
        read(fd, msg, 120);
        printf("Received: %s\n", msg);
        close(fd);
    }
    unlink(writefifo);

    return 0;
}