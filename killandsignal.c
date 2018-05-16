#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void interrupthandler(){
	printf("killed\n");
}

void dosomework(){
	signal(SIGINT,interrupthandler);
	for (int i = 0; i < 3; ++i)
	{
		printf("done work: %d ,processid: %d\n",i,(int)getpid() );
		sleep(1);
	}


}



int main(int argc, char const *argv[])
{




  pid_t pid[5];
  int answer;
  int nextchild;

printf("i am the parent process: %d \n\n", getpid() );
for (int i = 0; i < 5; ++i){
	
  if ((pid[i] = fork()) < 0) {//error
    perror("fork error");
    abort();

  } else if (pid[i] == 0) {// child process ..does some work and exits gracefully

  	printf("child process: %d, parent:  %d\n", getpid(),(int) getppid());
  	dosomework();
  	printf("KILL PARENT(1/0)\n");
  	scanf("%d",&answer);

  	if (answer == 1)
  	{
  	 	kill( getppid() , SIGKILL ); 
  	}
  	else if (answer == 0)
  	{
  		printf("-------------parent lives to see another loop-----------------\n");
  	}else{
  		printf("invalid input\n");
  	}
  	


    nextchild = (int)getpid() + 1;


    exit(0);
    
  }else{ // parent process(waits for child to finish and finishes)

  	

	
	//send to child
	wait(NULL);//waiting for the children to finish excecuting



	printf("KILL NEXT CHILD(1/0)\n");
  	scanf("%d",&answer);

  	if (answer == 1)
  	{
  	 	kill( (key_t)nextchild, SIGKILL ); 
  	}
  	else if (answer == 0)
  	{
  		printf("-------------child lives to see another loop-----------------\n");
  	}else{
  		printf("invalid input\n");
  	}
  }}

	

















	return 0;
}