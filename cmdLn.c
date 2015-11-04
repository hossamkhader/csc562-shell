#include"cmdLn.h"

void tokenizeCmdLn( const char *const line, struct cmln *cls ) {
        if ( cls == NULL ) { return; }

        cls->original = (char *)calloc( strlen( line ) + 1, sizeof(char) );
        strcpy( cls->original, line );
        char *tmp = strrchr( cls->original, '\n' );
        if ( tmp ) { *tmp = (char)0; }

        char *working = (char *)calloc( strlen( line ) + 1, sizeof(char) );
        strcpy( working, line );

        // for now ignore separating out > < | ` ' " ;
        // and count tokens
        cls->tokc = 0;
        char *c = working;
        while( *c ) { // until \0
                if ( !isspace( *c ) ) { // have a token
                        ++cls->tokc;
                        ++c;
                        while( !isspace( *c ) ) { ++c; }
                }
                // have a space
                ++c;
        }

        cls->tokv = (char **)calloc( cls->tokc + 1, sizeof(char*) ); // unchecked allocation

        int cur = 0;
        char *saveptr;
        c = strtok_r( working, " \t\n\r", &saveptr );
        while( c ) {
                cls->tokv[cur] = (char *)calloc( strlen( c ) + 1, sizeof(char) );
                strcpy( cls->tokv[cur], c );
                ++cur;
                c = strtok_r( NULL, " \t\n\r", &saveptr );
        }
        free( working );
}

