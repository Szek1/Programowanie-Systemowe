// PS IS1 322 LAB02
// Michał Sprysak
// sm49406@zut.edu.pl

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{

int vflag = 0;
int ret;
int tvalue = 1;

while ((ret = getopt (argc, argv, "vt:")) != -1)
	switch (ret){
		case 'v': vflag = 1; break;
		case 't':
			if(tvalue ==0)
			{
				tvalue = 1;
			}
				tvalue = atoi(optarg);
				break;
		case '?':
				fprintf(stderr, "Nieznana opcja '-%c' \n", optopt);
		default: abort();
} 

char *file = argv[optind];

char **tabArgs = argv + optind;

int j=0;


int childPid;
struct rusage usage;


printf("Tvalue = %d\n",tvalue);

for (int i=0; i<tvalue; i++){
	
	childPid = fork();

	if(childPid == 0)
	{

		if(vflag == 0)
		{
			close(1);
			close(2);
			int h = open("/dev/null", O_WRONLY);
			dup2(h,1);
			dup2(h,2);
		}
		printf("[%s]\n",file);
		execvp(file,tabArgs);
		exit(1);
	}
	
	struct timespec t1, t2;
	
	clock_gettime(CLOCK_REALTIME, &t1);
	wait4(childPid, NULL,0, &usage);
	clock_gettime(CLOCK_REALTIME, &t2);
	
	double realTime = (t2.tv_sec * 1e9 + t2.tv_nsec) - (t1.tv_sec * 1e9 + t1.tv_nsec);
	realTime = realTime / 1e9;  

	double userTime = 1e6 * usage.ru_utime.tv_sec  + usage.ru_utime.tv_usec;

	double sys_time1 = 1e6 * usage.ru_stime.tv_sec + usage.ru_stime.tv_usec;

	printf("Time[%d]: rTime: %fs\tuTime: %f\tsysTime:%f\n",i+1, realTime, userTime/1e6, sys_time1/1e6);

}

return 0;
}	
