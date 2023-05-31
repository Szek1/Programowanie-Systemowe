// PS IS1 322 LAB02
// Michał Sprysak
// sm49406@zut.edu.pl

#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

void groupList(char* users){

struct passwd *pw;
struct group *gr;
int ngroups;

ngroups = sysconf(_SC_NGROUPS_MAX);
gid_t *groups = malloc(sizeof(*groups) *ngroups);

if(groups == NULL){
	perror("malloc");
	exit(EXIT_FAILURE);
}

pw = getpwnam(users);
getgrouplist(users, pw->pw_gid, groups, &ngroups);
for (int i = 0; i < ngroups; i++){
	gr = getgrgid(groups[i]);
	if (gr != NULL)	
		printf("[%s]",gr->gr_name);

	}
free(groups);
}
