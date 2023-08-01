/*
 * Write a C program where the parent first executes
 * till the time parent executes the child has to wait
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	int fd[2];
	pid_t pid;

	/* Create PIPE to communicate Parent and child */
	if (pipe(fd) < 0) {
		printf("Failed to create a pipe\n");
		return -1;
	}
	
	/* Create a child process */	
	pid = fork();
	if (pid < 0) {
		printf("Failed to create a child process\n");
		return -1;
	}
	
	if (pid == 0) {
		/* Child Process */
		int n = 0, i;
		char buf[100];
		printf("I am a child process. my pid:%u parent pid:%u\n",
				getpid(), getppid());
		printf("Child: I am waiting for parent to signal me to continue\n");
		/* Wait till the parent notify child */
		while(n == 0) {
			n = read(fd[0], buf, 100);
		}
				
		/* Parent has signaled to child to continue process */
		for (i = 0; i < 5; i++) {
			printf("I am a child writing. %d\n", i);
			sleep(1);
		}	
		
		printf("Child: I am going to exit now\n");	
	} else {
		int status;
		/* Parent Process */
		printf("I am a parent process. my pid:%u parent pid:%u\n",
				getpid(), getppid());
		
		for (int i = 0; i < 5; i++) {
			printf("I am a parent writing. %d\n", i);
			sleep(1);
		}	

		printf("Parent: Now i am going to signal Child to continue\n");
		write(fd[1], "proceed", sizeof("proceed"));

		wait(&status);
		printf("Parent: I am going to exit now!!\n");

	}



	return 0;
}
