#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int fd[2];
	pid_t pid;
	/* pipe()  creates  a pipe, a unidirectional data channel that can be used for
	 * interprocess communication.  The array pipefd is used to  return  two  file
	 * descriptors  referring  to  the  ends of the pipe.  pipefd[0] refers to the
	 * read end of the pipe.  pipefd[1] refers to the write end of the pipe.  Data
	 * written  to the write end of the pipe is buffered by the kernel until it is
	 * read from the read end of the pipe.
	 */       
	if (pipe(fd) < 0) {
		perror("pipe");
		return -1;
	}

	pid = fork();

	if (pid == 0) {
		char buf[100];
		/* THis is a child process */
		printf("Child: PID:%u PPID:%u\n", getpid(), getppid());
		printf("Child: Waiting on the read end\n");
		while(!read(fd[0], buf, 100));
		printf("Child: Data read is:%s\n", buf);

	} else {
		int status;
		/* This is a parent process */
		printf("Parent: PID:%u PPID:%u\n", getpid(), getppid());
		printf("Parent is writing to pipes write end\n");
		sleep(1);
		write(fd[1], "My Name is Saimohan", sizeof("My Name is Saimohan")); 
		printf("parent: Data written is:%s\n", "My name is saimohan");
		wait(&status);
	}


	return 0;
}
