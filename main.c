#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<linux/limits.h>
#include"cmdLn.h"
#include"builtins.h"

//buffer size set to 256
#define BSZ 256

int main(int argc, char** argv, char** envp) 
{
    char buffer[BSZ];
    struct cmln cls;
    char **tmp;
    int k = 0;
    //print prompt
    fprintf( stdout, ">>");
    //loop for input from the user
    while(fgets( buffer, BSZ, stdin )) 
    {
        //tokenize the command entered by the user
        tokenizeCmdLn( buffer, &cls );
        //if valid input
        if(cls.tokc != 0)
        {
            //call the cd_command to handle the cd builtin command entered by the user
            if( strcmp( cls.tokv[0], "cd" ) == 0 ) 
            { 
                cd_command((const char ** const)cls.tokv);
            }
            //call the pwd_command to handle the pwd builtin command entered by the user
            else if( strcmp( cls.tokv[0], "pwd" ) == 0 ) 
            { 
                pwd_command();
            }
            //handle the exit builtin command entered by the user
            else if( strcmp( cls.tokv[0], "exit" ) == 0 ) 
            { 
                //exit successfully
                exit(0);
            }
            else
            { 
                //handle any other command enter by the uses
                execute(cls.tokv,envp);
            } 
        }
        //print prompt
        fprintf( stdout, ">>");         
    }
    return (EXIT_SUCCESS);
}