#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

// This program generates a random 16 bits

volatile int x,quit,capture;
void signal_handle(int sig_no){
	capture=x;
	quit=1;
}

int main(int argc, char *argv[]){
	int y;
	//1.Register an alarm signal handler
	signal(SIGALRM,signal_handle);
	//2.Loop till no of random bits you want to get
	for(y=0;y<16;y++){
		quit=0;
		//3. Function to send SIGALRM signal every 1 sec
		alarm(1);
		//4. In infinite loop, keep xoring the x with 1
		while(!quit){
			x=x^1;
		}
		//5.When at particular instance after 1 sec, print the value of x
		printf("%d ",capture);
		fflush(stdout);
	}
	printf("\n");
	return 0;
}
