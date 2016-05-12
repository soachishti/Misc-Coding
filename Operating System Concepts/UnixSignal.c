// TASK
/*
2. In a c/c++ program create a process using the fork() system call & do the following:
	- The parent process sends a Termination signal to the child with a delay of 1 second for 5 consecutive seconds.
	- The child process keeps ignoring the signal and prints "I am not going to die" each time it recieves the termination signal.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int sigCount = 1;
void sigHandler(int sigNum) {
	printf("I am not going to die. | sigNum: %d | sigCount: %d\n", sigNum, sigCount);
	sigCount++;
}

int main() {
	int pid = fork();
	if (pid > 0) {
		// Parent here		
		sleep(3);
		int i;
		for (i = 0; i < 5; i++) {
			printf("Termination signal sent to %d\n", pid);
			kill(pid, SIGTERM);			
			sleep(1);
		}
		kill(pid, SIGKILL);
		exit(0);
	}
	else {
		// Child here
		if (signal(SIGTERM, sigHandler) == SIG_ERR) {       
			printf("Could not attach signal handler\n");
			return EXIT_FAILURE;                        
		}    

		while(1) {
			printf("Child Process\n");
			sleep(1);
		}
	}
}