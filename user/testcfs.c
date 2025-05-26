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

//test fairness when all procs have same nice
int main() {
    printf(">>> Testing nice weight:\n");

    int child = fork();
    if (child == 0) { //child1 proc
        for (int i = 0; i < 10; i++) { //run for 10 secs
            work();  
        }
        exit(0);
    }

    child = fork();
    if (child == 0) { //child2 proc
        for (int i = 0; i < 10; i++) { //run for 10 secs
            work(); 
        }
        exit(0);
    }

    //parent proc
    for (int i = 0; i < 10; i++) { //run for 10 secs
        work(); 
        ps(0);  //print all proc stats
    }

    //wait for both child
    wait(0);
    wait(0);

    exit(0);
}
