#ifndef CMDLN_H
#define	CMDLN_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif



#include<stdio.h>
#include<string.h>
#include<stdlib.h>

    /* holds representation of a command line */
struct cmln {
    char *original; // copy of command line minus \n
    char **tokv;    // command line converted argv style
    int tokc;   // to tokv as argc to argv
};

    /*
     * a bit overbuilt and at the same time a bit underbuilt
     * ignores > < | ; ' ` " & for now
     *
     * line is the command line to be tokenized (brokedn into words)
     *
     * The cls struct should be empty when its address is passed
     *
     * On RETURN:
     * the cls struct holds a clean copy of the line (original)
     * with any \n replaced by a null terminator and
     * tokc and tokv which work like argc and argv for the line
     *
     * line is undamaged: const char* line --> cannot change contents pointed to
     * while char *const line --> cannot change pointer
     * so const pointer to const data
     */
void tokenizeCmdLn( const char *const line, struct cmln *cls );



#endif	/* CMDLN_H */

