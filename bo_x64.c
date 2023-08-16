#include <stdio.h>
#include <unistd.h>


int func() {
    char buf[80];
    int r;
    r = read(0, buf, 400);
    printf("\nRead %d bytes. buf is %s\n", r, buf);
    puts("No shell for you :(");
    return 0;
}

int main(int argc, char* argv[]) {
    printf("Try to exec /bin/sh");
    func();
    return 0;
}
