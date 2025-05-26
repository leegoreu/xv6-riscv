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

//test vruntime with staggered exec
int main() {
    printf(">>> Testing vruntime:\n");

    int child = fork();

    if (child == 0) { //child1 proc
        for (int i = 0; i < 10; i++) { //run for 10secs
            work();
            //print stats every sec
            ps(0);
        }
        exit(0);
    }

    child = fork();

    if (child == 0) { //child2 proc
        for (int i = 0; i < 5; i++) {
            work(); //run for 5secs
        }
        exit(0);
    }

    //parent proc
    printf("parent sleeping...\n");
    //wait for child1
    wait(0);
    printf("child1 exited\n");

    for (int i = 0; i < 3; i++) { //parent does 3secs work
        work();
    }

    //print stats after parent resumes
    ps(0);

    //wait for child2
    wait(0);
    printf("child2 exited\n");

    //print final proc stats
    ps(0);

    exit(0);
}