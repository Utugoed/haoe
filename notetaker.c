#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "hacking.h"


void usage(char* program_name, char* filename){
    printf("Usage: %s <data to be added to %s>\n", program_name, filename);
    exit(0);    
}

int main(int argc, char* argv[]){
    long long user_id, fd;
    char *buffer, *datafile;

    buffer = (char*) ec_malloc(100);
    datafile = (char*) ec_malloc(20);

    strcpy(datafile, "/var/notes");

    if (argc < 2)
        usage(argv[0], datafile);
    
    strcpy(buffer, argv[1]);

    printf("[DEBUG] Datafile contains: %s\n at the address %p\n", datafile, datafile);
    printf("[DEBUG] Buffer contains: %s\n at the address %p\n", buffer, buffer);
    
    fd = open(datafile, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd == -1)
        fatal("In main() during the file opening");
    printf("[DEBUG] File descriptor: %p", fd);

    user_id = getuid();
    if (user_id == -1)
        fatal("In main() during the getting user ID");
    
    if (write(fd, &user_id, 4) == -1)
        fatal("In main() during the wrting to a file");
    write(fd, "\n", 1);

    if (write(fd, buffer, strlen(buffer)) == -1)
        fatal("In main() during the wrting to a file");
    write(fd, "\n", 1);

    if (close(fd) == -1)
        fatal("In main() during the closing a file");

    free(buffer);
    free(datafile);
    return 0;
}
