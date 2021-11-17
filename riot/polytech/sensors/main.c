#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "thread.h"
#include "timex.h"
#include "xtimer.h"
#include "shell.h"

#include "mutex.h"

/* Add lm75a related include here */

/* Add mpu9x50 related include here */

/* Declare the lm75a device variable here */

/* Declare the mpu9x50 device variable here */

/* Declare and initialize the mpu9x50 thread lock here */

/* stack memory allocated for the mpu9x50 thread */
static char mpu9x50_stack[THREAD_STACKSIZE_MAIN];

static void *mpu9x50_thread(void *arg)
{
    (void)arg;

    while (1) {
        /* Acquire the mutex here */

        /* Read the accelerometer values here */

        /* Release the mutex here */

        xtimer_usleep(500 * US_PER_MS);
    }

    return 0;
}

static void _mpu9x50_usage(char *cmd)
{
    printf("usage: %s <start|stop>\n", cmd);
}

static int mpu9x50_handler(int argc, char *argv[])
{
    if (argc < 2) {
        _mpu9x50_usage(argv[0]);
        return -1;
    }

    /* Implement the mpu9x50 start/stop subcommands here */

    return 0;
}

static void _lm75_usage(char *cmd)
{
    printf("usage: %s <temperature>\n", cmd);
}

static int lm75_handler(int argc, char *argv[])
{
    if (argc < 2) {
        _lm75_usage(argv[0]);
        return -1;
    }

    /* Implement the lm75a temperature subcommands here */

    return 0;
}

static const shell_command_t commands[] = {
    /* mpu9x50 shell command handler */

    /* Add the lm75a command description here */

    { NULL, NULL, NULL}
};

int main(void)
{
    /* Initialize the lm75a sensor here */

    /* Initialize the mpu9x50 sensor here */

    thread_create(mpu9x50_stack, sizeof(mpu9x50_stack), THREAD_PRIORITY_MAIN - 1,
                  0, mpu9x50_thread, NULL, "mpu9x50");

    /* Everything is ready, let's start the shell now */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
