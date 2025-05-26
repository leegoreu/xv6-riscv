#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//test if child inherits parent's nice value
int main() {
    printf(">>> Testing nice weight:\n");
    
    int parent = getpid();
    setnice(parent, 30); //set high nice value for parent proc

    int child = fork();
    if (child == 0) {
        //child proc
        printf("Child nice value: %d\n", getnice(getpid()));
        exit(0);
    } else {
        //parent waits for child
        wait(0);
    }
    
    exit(0);
}
