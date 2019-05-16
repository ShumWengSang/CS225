#include <stdio.h>  /* printf */
#include <string.h> /* strstr,strlen */
#include <stdlib.h> /* atoi for C++ compiler */
#include "splitter.h"


int main(int argc, char** argv) {
    int join=0,split=0;
    char *output=NULL;
    int size=0;
    int i;
    int list_start, list_end=0, list_reading=0;
    int ret_code = E_NO_ACTION; /* default return code */

    if (argc<2) { 
        printf("Usage:\n\t%s -j -o <output file> -i <filename>\nto join\ror \
                \n\t%s -s <size in bytes> -o <output file suffix> -i <filenames>\n \
                to split\n\n",argv[0],argv[0]);
    }

    for ( i=1; i<argc; ++i ) {
        /* check if we read filenames or flags */
        if ( list_reading ) {
            if ( argv[i][0] != '-' ) {
                /*printf( "list item %s\n", argv[i] );*/
                continue;
            } else {
                list_reading = 0;
                list_end = i;
                /*printf( "end list\n" );*/
            }
        }
        if (strlen(*argv)>1) {
            switch ( argv[i][1] ) {
                case 's': if (i+1==argc) { 
                              printf("flag \"-s\" should be followed by a number - chunk size\n"); 
                              return E_NO_ACTION;
                          }
                          ++i;
                          size=atoi( argv[i] );
                          split=1; 
                          /*printf( "-s %d\n", size );*/
                          break;
                case 'j': join=1; 
                          /*printf( "-j\n" );*/
                          break;
                case 'o': if (i+1==argc) { 
                              printf("flag \"-o\" should be followed by a filename\n"); 
                              return E_NO_ACTION;
                          } 
                          ++i;
                          output=argv[i]; 
                          /*printf( "-o %s\n", output );*/
                          break;
                case 'i': list_start = i+1; 
                          list_reading=1; 
                          /*printf( "start list\n" );*/
                          break;
                default:  printf( "Unexpected non-flag entry \"%s\"\n",argv[i] );
                          return E_NO_ACTION;
            }
        }
    }

    if ( list_end == 0 ) { /* if end of the input file list was not set */
        list_end = argc;
    }

    if ( ( split && join ) || ( !split && !join ) ) { /* check operation */
        printf( "Exactly one operation \"-s\" or \"-j\" should be specified\n" );
        return ret_code;
    } 

    if ( output == NULL ) { /* check output */
        printf( "Specify combined output filename with \"-o\" " );
        return ret_code;
    } 

    if ( list_end-list_start == 0 ) {
        printf( "Specify input file/list with \"-i\" " );
        return ret_code;
    }

    if ( list_end-list_start > 1 && split ) {
        printf( "When splitting there should be only 1 input file with \"-i\"\n" );
        return ret_code;
    }

    if (split) {
        int i;
        printf( "Split " );
        for ( i=0; i<list_end-list_start; ++i ) {
            printf( "\"%s\" ", argv[list_start+i] );
        }
        printf( " into %d-byte chunks named \"%s\"\n", size, output );
        ret_code = SplitFile(argv[list_start],output,size);
    } else {
        if (join) {
            int i;
            printf( "Join " );
            for ( i=0; i<list_end-list_start; ++i ) {
                printf( "\"%s\" ", argv[list_start+i] );
            }
            printf( " into \"%s\"\n", output );
            ret_code = JoinFiles( argv+list_start, list_end-list_start, output);
        }
    }
    return ret_code;
}
