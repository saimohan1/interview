#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE	1024

#define MQ_NAME	"/my_test_mq"

static char buffer[MAX_BUFFER_SIZE];


int main() {
	mqd_t msgid;
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = 5;	/* Maximum 5 message */
	attr.mq_msgsize = MAX_BUFFER_SIZE;

	/* mqname, flags, permission, attribute */
	msgid = mq_open(MQ_NAME, O_RDONLY, 0644, &attr);
	if (msgid == -1) {
		perror("mq_open");
		exit(1);
	}

	memset(buffer, 0, MAX_BUFFER_SIZE);

	if (mq_receive(msgid, buffer, MAX_BUFFER_SIZE, 0) < 0) {
		perror("mq_send");
	}

	printf("Message Received from MQ is: %s\n", buffer);
	
	mq_close(msgid);

	return 0;
}

