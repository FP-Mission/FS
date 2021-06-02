#include <ctype.h>
#include <getopt.h>
#include <stdlib.h>

#include <App/Top/Components.hpp>

void print_usage(const char* app) {
    (void)printf(
        "Usage: ./%s\n",
        app);
}

#include <signal.h>
#include <stdio.h>

#ifdef TGT_OS_TYPE_FREERTOS_SIM 
#include "FreeRTOS.h"
#include "task.h"
#endif 

volatile sig_atomic_t terminate = 0;

static void sighandler(int signum) {
    exitTasks();
    terminate = 1;
}

#ifdef TGT_OS_TYPE_FREERTOS_SIM 
// FreeRTOS main task that
// emulate a clock
void run1cycle(void*) { 
    while(1) {
        blockDrv.callIsr();
        Os::Task::delay(1000);  // 10Hz
    }
}
#else   // Linux et Darwin
void run1cycle(void) {
    // call interrupt to emulate a clock
    blockDrv.callIsr();
    Os::Task::delay(1000);  // 10Hz
}

void runcycles(NATIVE_INT_TYPE cycles) {
    if (cycles == -1) {
        while (true) {
            run1cycle();
        }
    }

    for (NATIVE_INT_TYPE cycle = 0; cycle < cycles; cycle++) {
        run1cycle();
    }
}
#endif

int main(int argc, char* argv[]) {
    I32 option;
    option = 0;
    bool dump = false;

    while ((option = getopt(argc, argv, "hdp:a:")) != -1) {
        switch (option) {
            case 'h':
                print_usage(argv[0]);
                return 0;
                break;
            case '?':
                return 1;
            case 'd':
                dump = true;
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    (void)printf("Hit Ctrl-C to quit\n");

    bool quit = constructApp(dump);
    if (quit) {
        return 0;
    }
    
    // register signal handlers to exit program
    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);

#ifdef TGT_OS_TYPE_FREERTOS_SIM 
    Os::Task* mainTask = new Os::Task();
    Fw::EightyCharString name("MainTask");
    Os::Task::TaskStatus stat = 
        mainTask->start(name, 
                        0, 100,
                        10*1024, run1cycle, 
                        NULL);
    if (stat != Os::Task::TASK_OK) {
    	printf("Couldn't start main task: %d\n",stat);
    }

    // Blocking call that start scheduler
    vTaskStartScheduler();
#else // Linux and Darwin
    while (!terminate) {
        runcycles(1);
    }

    // Give time for threads to exit
    (void)printf("Waiting for threads...\n");
    Os::Task::delay(1000);

    (void)printf("Exiting...\n");

    return 0;
#endif
}
