// PS IS1 322 LAB05
// Michał Sprysak
// sm49406@zut.edu.pl

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdbool.h>

int leave = 0;
int count = 0;

void sigHndler(int sig, siginfo_t *info, void *ucontext){

    (void) ucontext;
	time_t czasxd;
	struct tm * timeinfo;
	time ( &czasxd );
	timeinfo = localtime ( &czasxd );
	printf ( "\t\t[%d] [%d] [%s]", info->si_pid, info->si_value,asctime (timeinfo) );
	count--;
 }


void sigCtrlC(int sig){
	leave = 1;
}

int flag = 0;

void sigExitHndler(int sig)
{
	flag = 1;
}



int main(int argc, char **argv)
{
	int ret;
	int maxLifeTime = 0;
	int breakProcessCreation = 0;

	while ((ret = getopt(argc, argv, "w:m:")) != -1)
		switch (ret)
		{
		case 'w':
			breakProcessCreation = atoi(optarg);
			break;
		case 'm':
			maxLifeTime = atoi(optarg);
			break;
		case '?':
			fprintf(stderr, "Nieznana opcja `-%c'.\n", optopt);
		}

	printf("w = %d\nm = %d\n", breakProcessCreation, maxLifeTime);

	struct sigaction sigact, sigactExit, ctrlC;

	sigact.sa_sigaction = sigHndler;
	//sigemptyset(&(sigact.sa_mask));
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1,&sigact,NULL);

	ctrlC.sa_sigaction = sigCtrlC;
	//sigemptyset(&(sigactExit.sa_mask));
	ctrlC.sa_flags = SA_SIGINFO;
	sigaction(SIGINT,&ctrlC,NULL);

	sigactExit.sa_sigaction = sigExitHndler;
	//sigemptyset(&(sigactExit.sa_mask));
	sigactExit.sa_flags = SA_SIGINFO;


	pid_t parent;
    
while (true)
{	
	flag = 0;
	parent = fork();
	
	if(parent == 0)
	{
		srand(time(NULL));
		int randomLifeTime = rand() % maxLifeTime + 1;
		time_t czasxd;
		struct tm *timeinfo;
		time(&czasxd);
		timeinfo = localtime(&czasxd);
		printf("[%d] [%d] [%s]", getpid(), randomLifeTime, asctime(timeinfo));

		signal(SIGALRM,sigExitHndler);
		alarm(randomLifeTime);
			
		int fact = 1;
		int cnt = 1;
		while(flag == 0){

			fact = fact * cnt;
			cnt ++;
		}
		union sigval sval;
		sval.sival_int = randomLifeTime;
		sigqueue(getppid(),SIGUSR1,sval);
			
		exit(0);
	}
	else
		{
		count++;
		signal(SIGALRM,sigExitHndler);
		alarm(breakProcessCreation);
		while(flag == 0)
			{	
			sleep(1);
			}
		}
		if(leave == 1)
	{
		
		while(count > 0)
		{
		}
	break;
	} 

}
    
return 0;
}
