// PS IS1 322 LAB02
// Michał Sprysak
// sm49406@zut.edu.pl

#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <dlfcn.h>

void (*groupList)(char*);

int main(int argc, char **argv)
{
void *handle = dlopen( "./49406.ps.lab03.shared.lib.so", RTLD_LAZY);
if( !handle)
	printf("Nie znaleziono biblioteki!\n");
else{
dlerror();
groupList = dlsym(handle, "groupList");
}

struct utmp* entry;
struct passwd* getpwd;
int hflag = 0;
int gflag = 0;
opterr = 0;
int ret;

while ((ret = getopt (argc, argv,"hg")) != -1)
	switch( ret){
	case 'h': hflag = 1; break;
	case 'g': gflag = 1; break;
	case '?': 
		fprintf(stderr,"Nieznana opcja '-%c' \n",optopt);
		return 1;
	default: abort();
	}

setutent();
while((entry=getutent()) != NULL){
	if(entry->ut_type == USER_PROCESS){
		printf("%s ",entry->ut_user);

		if(hflag == 1)
			printf("(%s) ",entry->ut_host);

		if(gflag == 1 && handle)
			groupList(entry->ut_user);
		
		printf("\n");
	}
}
endutent();

if(handle)
dlclose(handle);
return 0;

}

