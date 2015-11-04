#ifndef BUILTINS_H
#define	BUILTINS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#include<unistd.h>
#include<stdio.h>
#include<linux/limits.h>
#include"cmdLn.h"

extern int execvpe(const char *path, char *const argv[],char * const envp[]);// the execvpe system call

void cd_command(const char ** const argv);// called when to handle cd builtin command
void pwd_command();// called to handle the pwd builtin command
void execute(char ** const argv, char** envp);//called to handle the execution of other programs


#endif

