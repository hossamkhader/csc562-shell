################################################################################
Hossam Khader for CSC 562 Shell Project 01
E-mail: hkkhader@uncg.edu
################################################################################
Built and tested on RHEL6 (i.e. prdile.uncg.edu)
To build: make CONF=Release
The executable binary will be in dist/Release/GNU-Linux-x86/
################################################################################
The shell implements the following built-in commands:
cd
cd .
cd ..
cd -
cd ~
cd absolute path
cd relative path
exit
pwd
################################################################################
Below is a brief summary of the code:
The getenv() and the setenv() functions are called by the cd_command() function to retrieve or update the value of the $PWD and $OLDPWD environment variables.
The execute() function uses the fork(), exec(), and wait() system calls to run other programs. The execvpe() variant is used, and the environment variables vector is passed to it.