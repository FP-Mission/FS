#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>

#include <App/Top/Components.hpp>

void print_usage(const char* app) {
    (void) printf("Usage: ./%s",app);
}

#include <signal.h>
#include <stdio.h>

volatile sig_atomic_t terminate = 0;

static void sighandler(int signum) {
    exitTasks();
    terminate = 1;
}

void run1cycle(void) {
    // call interrupt to emulate a clock
    blockDrv.callIsr();
    Os::Task::delay(1000); //10Hz
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

int main(int argc, char* argv[]) {
    I32 option;
    option = 0;
    bool dump = false;

    while ((option = getopt(argc, argv, "hdp:a:")) != -1){
        switch(option) {
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

    (void) printf("Hit Ctrl-C to quit\n");

    bool quit = constructApp(dump);
    if (quit) {
        return 0;
    }

    // register signal handlers to exit program
    signal(SIGINT,sighandler);
    signal(SIGTERM,sighandler);

    int cycle = 0;

    while (!terminate) {
//        (void) printf("Cycle %d\n",cycle);
        runcycles(1);
        cycle++;
    }

    // Give time for threads to exit
    (void) printf("Waiting for threads...\n");
    Os::Task::delay(1000);

    (void) printf("Exiting...\n");

    return 0;
}
