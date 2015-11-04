#include "builtins.h"

// called when to handle cd builtin command
void cd_command(const char ** const argv)
{
    int return_value = -1;
    //handles the cd and the cd ~ commands by passing the value of the $HOME environment variable to the chdir() system call
    if (argv[1] == NULL || strcmp(argv[1], "~" ) == 0 )//match for ~ or nothing in the cd argument
    {
        return_value = chdir(getenv("HOME"));
    }
    //handles the cd - command by passing the value of the $OLDPWD environment variable to the chdir() system call
    else if (strcmp(argv[1], "-" ) == 0)//match for - in the cd argument
    {
        return_value = chdir(getenv("OLDPWD"));
    }
    //handles the cd .. command by extracting the parent directory of the $PWD and passing it to the chdir() system call
    else if (strcmp(argv[1], ".." ) == 0)// match for .. in the cd argument
    {
        char path[PATH_MAX];//maximum path length from linux/limits.h
        //copy the value of the $PWD to the path string
        strcpy(path,getenv("PWD"));
        //match the last / character in $PWD
        char * last_slash = strrchr(path, '/');
        //null terminate the path string at the last / character (i.e. parent directory)
        *last_slash = '\0';
        //pass the path string containing the parent directory to chdir() system calls
        return_value = chdir(path);    
    }
    //handles the cd command by passing the value of the $PWD environment variable to the chdir() system call
    else if (strcmp(argv[1], "." ) == 0)// match for . in the cd argument
    {
        return_value = chdir(getenv("PWD"));
    }
    //handles the cd relative path command by prepending $PWD to the path and passing the value to the chdir() system call
    else if(argv[1][0] != '/')//match for not / in the cd argument (i.e. relative path)
    {
        char path [PATH_MAX];//maximum path length from linux/limits.h
        strcpy(path,getenv("PWD"));
        strcat(path,"/");
        strcat(path,argv[1]);
        return_value = chdir(path);
    }
    else //handles all other cased by passing the value of the cd args as is to the chdir() system call
    {
        return_value = chdir(argv[1]);
    }
    
    if (return_value == -1)//print an error message if chdir() system call fails
    {
        fprintf(stderr,"cd: %s: No such file or directory\n",argv[1]);
    }
    else//update the $OLDPWD and $PWD environment variables on success of chdir() system call
    {
        char cwd[PATH_MAX];//maximum path length from linux/limits.h
        getcwd(cwd, sizeof(cwd));//get the current working directory
        setenv("OLDPWD",getenv("PWD"),1);//update $OLDPWD to the value of $PWD
        setenv("PWD",cwd,1);//update $PWD to the current directory 
    }
}

//called to handle the pwd builtin command
void pwd_command()
{
    char cwd[PATH_MAX];//maximum path length from linux/limits.h
    getcwd(cwd, sizeof(cwd));//get the current working directory
    printf("%s\n", cwd);//print the current working directory
}

//called to handle the execution of other programs
void  execute( char ** const argv, char** envp)
{
     pid_t  pid;
     
     pid = fork();//fork to create a child process
     if (pid == 0)
     {
         //child process (i.e. other programs to be executed)
         //pass the environment vector to the execvpe() system calls
          if (execvpe(argv[0],argv, envp) < 0)
          {
              
              //print an error message if the execvpe system call fails
              //the program file is not found, not executable or no permission to execute
              fprintf(stderr,"%s: command not found or Permission denied\n",argv[0]);
              exit(1);// exits abnormally
          }
     }
     else 
     {
         //parent process (i.e. the shell)
         wait();//wait for the child to exit.
     }
}

