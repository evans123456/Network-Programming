#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void dosomework(char *name,int cid){
	int count = 3;
	for (int i = 0; i < count; ++i)
	{
		printf("loop: %d, process: %s id: %d \n",i,name,cid);
	}
}



int main(int argc, char const *argv[])
{
	pid_t pid[10];
	// int i;
	int n = 5;
	int pipeEnds1[2];
	int pipeEnds2[2];
	int ret1;
	int ret2;
	char prompt[] = "How are you doing my child proccess\n";
	char answer[] = "Fine thank you my parent process\n";
	int count = 10;

	pipe(pipeEnds1);
 	pipe(pipeEnds2);




	printf("i am the parent process: %d \n\n", getpid() );







for (int i = 0; i < count; ++i){
	

  if ((pid[i] = fork()) < 0) {//error
    perror("fork error");
    abort();





  } else if (pid[i] == 0) {// child process ..does some work and exits gracefully
  	printf("child process: %d, parent:  %d\n", getpid(),(int) getppid());
  	//receive message from parent

  	// parent: reading only, so close the write-descriptor
        close(pipeEnds1[1]);

        // now read the data (will block)
        read(pipeEnds1[0], &prompt, sizeof(prompt));
        printf("Child(%d) received value: %s\n", getpid(), prompt);

        // close the read-descriptor
        close(pipeEnds1[0]);

    dosomework("child",(int)getpid());

    //send to parent

    // parent: writing only, so close read-descriptor.
        close(pipeEnds2[0]);

        // send the value on the write-descriptor.
        
        write(pipeEnds2[1], &answer, sizeof(answer));
        printf("Child(%d) send value: %s\n", getpid(), answer);

        // close the write descriptor
        close(pipeEnds2[1]);


    exit(0);
    





  }else{ // parent process(waits for child to finish and finishes)

	printf(" parent process:  %d  ......waiting for child to end\n",getpid());
	//send to child

	 // parent: writing only, so close read-descriptor.
        close(pipeEnds1[0]);

        // send the value on the write-descriptor.
        //val = 36969;
        write(pipeEnds1[1], &prompt, sizeof(prompt));
        printf("Parent(%d) send value: %s\n", getpid(), prompt);

        // close the write descriptor
        close(pipeEnds1[1]);



	wait(NULL);//waiting for the children to finish excecuting


	printf("child finished doing some work \n");
	//receive message from child

	// parent: reading only, so close the write-descriptor
        close(pipeEnds2[1]);

        // now read the data (will block)
        read(pipeEnds2[0], &answer, sizeof(answer));
        printf("Parent(%d) received value: %s\n", getpid(), answer);

        // close the read-descriptor
        close(pipeEnds2[0]);
	

	

	printf("parent finished\n");

	

  }
 







}
	return 0;
}


