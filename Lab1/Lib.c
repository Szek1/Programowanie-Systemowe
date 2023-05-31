// PS IS1 322 LAB02
// Michał Sprysak
// sm49406@zut.edu.pl

#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>

void labki(){

struct utmp *entry;
struct passwd *getpwd;
setutent();

while((entry = getutent()) != NULL)
{
	if(entry->ut_type == USER_PROCESS){
 		getpwd = getpwnam(entry->ut_user);
		printf("\n%d (%s) %s %s \n",getpwd->pw_uid, entry->ut_user,entry->ut_line,entry->ut_host);
		}
}
endutent();
}

