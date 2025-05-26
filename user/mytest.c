#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    //
    // PA1 TEST
    // 
    /*
    printf(">>>Testing getpname:\n");
    getpname(1);  //if exists

    printf(">>>Testing getnice and setnice:\n");

    printf("initial nice value: %d\n", getnice(getpid()));

    if (setnice(getpid(), 10) == 0) {
        printf("nice value after setting: %d\n", getnice(getpid()));
    } else {
        printf("failed to set nice value\n");
    }

    printf(">>>Testing ps:\n");
    ps(0);  //print all processes

    printf(">>>Testing meminfo:\n");
    printf("available memory: %lu bytes\n", meminfo());


    printf(">>> Testing waitpid:\n");

    int pid1 = fork();

    if (pid1 == 0) {  //child proc1
        sleep(2);
        printf("start1\n");
        sleep(5); //some work done
        printf("end1\n");
        exit(10);
    }

    sleep(1); //to force print order

    int pid2 = fork();

    if (pid2 == 0) {  //child proc2
        sleep(2);
        printf("start2\n");
        sleep(10); //some work done
        printf("end2\n");
        exit(10);
    }

    //parent proc waits
    int exit_status;
    printf("wait\n");
    int w1 = waitpid(pid1, (uint64)&exit_status, 0);
    printf("done1 %d %d\n", w1, exit_status);

    int w2 = waitpid(pid2, (uint64)&exit_status, 0);
    printf("done2 %d %d\n", w2, exit_status);

    exit(0);*/

    //
    // PA2 TEST
    //
    printf(">>> Testing fair scheduling:\n");

    int range = 100000;
    int a = 1;

    int pid1 = fork();

    if (pid1 > 0) {
        //parent proc
        setnice(getpid(), 0);
        for (int i = 0; i < range; i++) { //some work
            for (int j = 0; j < range; j++) {
                a = a * 10 + 1;
            }
        }

        // print all process stats
        ps(0);
        // wait for child to finish
        wait(0);
    } else if (pid1 == 0) {
        //child proc
        setnice(getpid(), 10);
        for (int i = 0; i < range; i++) { //some work
            for (int j = 0; j < range; j++) {
                a = a * 10 + 1;
            }
        }

        exit(0);
    }

    exit(0);
    
}
