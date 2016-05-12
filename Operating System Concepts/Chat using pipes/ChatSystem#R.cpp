#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_BUF 120

int main()
{
    int fd;
    char readfifo[] = "/tmp/myfifo1";
    char writefifo[] = "/tmp/myfifo2";
    char buf[MAX_BUF];
    mkfifo(writefifo, 0666);

    while(1) {
        fd = open(readfifo, O_RDONLY);
        read(fd, buf, MAX_BUF);
        printf("Received: %s\n", buf);
        close(fd);

        fd = open(writefifo, O_WRONLY);
        printf("Enter Message: ");
        scanf("%s",buf);
        write(fd, buf, 120);
        close(fd);
    }
    unlink(writefifo);
    return 0;
}