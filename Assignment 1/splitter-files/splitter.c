#include <stdio.h>     /* printf, sprintf */
#include <stdlib.h>    /* Malloc */
#include "splitter.h"  /* SplitFile, JoinFiles */

#define PAGESIZE 4096

int SplitFile(char const *  filename,  char const * output, size_t size)
{
    /* Buffer to hold the current file name to output. */
    char current_file_name[256];
    
    /* The current counter of the file */
    unsigned file_count = 1;
    size_t size_read = 0;
	
	/* Allocate a buffer as big as size, or if bigger, PAGESIZE*/
	size_t buffer_size = size > PAGESIZE ? PAGESIZE : size;
	char * buffer = malloc(sizeof(char) * buffer_size) ;

	/* Open source file. */
    FILE * sourceFile = fopen(filename, "rb");
    size_t leftover = 0;

    /* Check if malloc came in properly */
    if(buffer == NULL)
    {
        return E_NO_MEMORY;
    }
    /* See if file opened properly */
    if(sourceFile == NULL)
    {
        /* Error */
        return E_BAD_SOURCE;
    }

    printf("split %s into chunks of %lu named\n", filename, size);

    /* While not at end of file. */
    while(!feof(sourceFile))
    {
        char * buffer_local = buffer;
        FILE * destFile = NULL;
        size_t total_written_bytes = 0;
        size_t written_bytes = 0;

        unsigned j;
        /* Read as many as I can. Store the amount read in our PAGE */
        size_read = fread(buffer, sizeof(char), buffer_size, sourceFile);

        if(leftover != 0)
        {
            fwrite(buffer_local, sizeof(char), leftover, destFile);
            fclose(destFile);
        }

        /* Current Size */
        for(j = 0; j <= size_read; j += written_bytes)
        {
            size_t part_size;
            /* If the chunk we are reading is bigger then size.*/
            if(total_written_bytes + size > size_read)
            {
                part_size = size_read - total_written_bytes;
                /* End the loop if we keep reading 0.*/
                if(part_size == 0)
                {
                    break;
                }
            }
            else
            {
                part_size = size;
            }

            /* Determine the string of the file. */
            sprintf(current_file_name, "%s%04u", output, file_count++);
            printf("%s", current_file_name);
            /* Open destination file */
            destFile = fopen(current_file_name, "wb");
            /* Error checking */
            if (destFile == NULL) {
                return E_BAD_DESTINATION;
            }
            /* Now we write all we can in. */
            buffer_local += j;
            written_bytes = fwrite(buffer_local, sizeof(char), part_size, destFile);
            leftover = part_size - written_bytes;
            total_written_bytes += written_bytes;

            /* Close the file if we have fully written into it. */
            if(leftover == 0)
            {
                fclose(destFile);
            }
        }
    }
	/* Deallocate dynamically allocated buffer */
    free(buffer);

	/* Close source file */
    return 0;
}

int JoinFiles(char** filenames, int num_files, char const * output)
{
    char buffer[PAGESIZE];
	/* Open destination file. */
    FILE *destination = fopen(output, "wb");
    int i;

    printf("join\n");
    if(destination == NULL)
    {
        return E_BAD_DESTINATION;
    }

    for(i = 0 ; i < num_files; i++)
    {
        FILE *source = fopen(*(filenames + i), "rb");
        size_t size_read;
        if(source == NULL)
        {
            fclose(destination);
            return E_BAD_SOURCE;
        }

        do{
            /* Read the amount possible. */
            size_read = fread(&buffer, sizeof(char), PAGESIZE, source);
            /* Write the amount possible. */
            fwrite(&buffer, sizeof(char), size_read, destination);
        }while(size_read != 0);
        /* Close file */
        fclose(source);
    }
	
	/* Close destination file */
	fclose(destination);
    printf("into %s\n",output);
    return 0;
}
