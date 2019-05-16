#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"

void encode_decode( char const * plaintext )
{
    int buff_size = strlen(plaintext);
    char* encryptedtext = (char*)malloc( buff_size ); /* more then needed, so some space will be waisted */
    char* decodedtext = (char*)malloc( buff_size +1 );
    int num_bits_used; /*not used, but the actual number of bytes needed for encodedtext is num_bits_used/8 + (num_bits_used%8)?1:0*/

    encode( plaintext, encryptedtext, &num_bits_used );

    print_bits( encryptedtext, 0, num_bits_used );

    decode( encryptedtext, buff_size, decodedtext );
    printf( "%s\n", decodedtext );

    free( decodedtext );
    free( encryptedtext );
}

void test0() { encode_decode( "a" ); }
void test1() { encode_decode( "ab" ); }
void test2() { encode_decode( "cccc" ); }
void test3() { encode_decode( "xaxa" ); }
void test4() { encode_decode( "abcdefghijklmnopqrstuvwxyz" ); }
void test5() { encode_decode( "kdjasfhkdslfhksdjhfkldsfhlskdfjh" ); }
void test6() { encode_decode( "aardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvarkaardvark" ); }

#include <time.h>
#include <stdlib.h>
void test7() {
    int buff_size = 100000, i;
    char* plaintext     = (char*)malloc( buff_size+1 );
    char* encryptedtext = (char*)malloc( buff_size+1 );
    char* decodedtext = (char*)malloc( buff_size+1 );
    int num_bits_used; /*not used, but the actual number of bytes needed for encodedtext is num_bits_used/8 + (num_bits_used%8)?1:0*/

    /* randomly generate plaintext */
    srand(time(NULL));
    for ( i=0; i<buff_size; ++i ) {
        plaintext[i] = 'a' + rand()%26;
    }
    plaintext[buff_size] = 0;

    encode( plaintext, encryptedtext, &num_bits_used );
    decode( encryptedtext, buff_size, decodedtext );

    if ( strcmp( plaintext, decodedtext ) == 0 ) {
        printf( "All good\n" );
    }
    
    free( decodedtext );
    free( encryptedtext );
    free( plaintext );
}

void (*pTests[])() = { 
    test0,test1,test2,test3,test4,test5,test6,
    test7
};

int main (int argc, char ** argv) {
	if (argc >1) {
		int test = 0;
		sscanf(argv[1],"%i",&test);
        pTests[test]();
	}
	return 0;
}
