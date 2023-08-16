#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void fatal(char* message){
    char error_message[100];

    strcpy(error_message, "[!!] CRITICAL ERROR: ");
    strncat(error_message, message, 78);
    perror(error_message);
    exit(-1);
}

void* ec_malloc(unsigned int size){
    void* ptr;

    ptr = malloc(size);
    if (ptr == NULL){
        fatal("In function ec_malloc during memory allocation.");
    }
    return ptr;
}

void dump(const unsigned char *data_buffer, const unsigned int length){
    unsigned char byte;
    unsigned int i, j;
    
    for (i = 0; i < length; i++){
        byte = data_buffer[i];
        printf("%02x ", byte);
        
        if (((i % 16) == 15) || (i == length - 1)){
	    for (j = 0; j < 15 - (i % 16); j++)
		printf("   ");
	    
	    printf("| ");
	    for (j = (i - (i % 16)); j <= i; j++){
		byte = data_buffer[j];
		if ((byte > 31) && (byte < 127))
		    printf("%c", byte);
		else
		    printf(".");
	    }
	    printf("\n");
	}
    }
}
