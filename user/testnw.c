#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int work() { //some work
    int a, b;
    int start_time = uptime();

    a = 0;
    b = 20;

    while ((uptime() - start_time) < 100) { //run for ~1sec
        for (int i = 0; i < 1000000; i++) {
            for (int j = 0; j < 10000; j++) {
                a += b * 89;
            }
        }
    }

    return a;
}

//test scheduling with different nice values
int main() {
    printf(">>> Testing nice weight (different priorities):\n");
    
    int parent = getpid();
    setnice(parent, 5); //set parent to higher priority

    int child = fork();
    if (child == 0) { //child proc with lower priority
        setnice(getpid(), 20);

        for (int i = 0; i < 10; i++) { //run for 10 secs
            work();
        }

        exit(0);
    }

    //parent proc
    for (int i = 0; i < 10; i++) { //run for 10 secs
        work();
        ps(0); //print all proc stats
    }

    //wait for child
    wait(0);

    exit(0);
}
