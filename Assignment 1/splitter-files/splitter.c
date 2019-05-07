#include <stdio.h>     /* printf, sprintf */
#include "splitter.h"  /* SplitFile, JoinFiles */
int SplitFile(char const *  filename,  char const * output, size_t size) {
    char current_file_name[256];
    int file_count=1,i=0;
	
	/* Open source file. */
	
    printf("split %s into chunks of %d named\n",filename,size);
	
	/* Allocate a buffer as big as size */
	
	/* Do */
		/* Open destination file */
	
		/* Read as many as I can. Store the amount read. */
	
		/* Take the contents and paste it into buffer. */
		
		/* Put as many as you read into outstream. */
		
		/* Close destination file */
	/* While the amount read is the same as the size. */	
		
	/* Deallocate dynamically allocated buffer */
	
    for (;i<5;++i) 
	{
        /* print in to a string. The format is string(%s) 
         * and a 4-digit integer padded with 0's on the left, i.e.
         * 1 is printed as 0001, 123 as 0123, note that 12345 is printed as 12345 */
        sprintf(current_file_name,"%s%04lu\n",output,file_count++);
        /* What if we use this line below?
         * sprintf(current_file_name,"%s%04lu\n",output,++file_count); */
        printf("%s",current_file_name);
    }
    printf("...\n");
	
	/* Close source file */
    return 0;
}

int JoinFiles(char** filenames, int num_files, char const * output) {
    printf("join\n");
	/* Open desination file. */
	
    while (*filenames) {
		/* Open source file */
		
		
		/* While c = read != EOF */
			/* putchar c into destination */
		
		/* Close source file */
        printf("%s\n",*filenames++);
    }
	
	/* Close desitnation file */
    printf("into %s\n",output);
    return 0;
}
