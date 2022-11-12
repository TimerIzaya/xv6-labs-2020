#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define PRIME_NUM 35

void child(int pf[]);

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    int pid = fork();
    if (pid > 0)
    {
        close(p[0]);
        for (int i = 2; i <= PRIME_NUM; i++)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait((int *)0);
    }
    else if (pid == 0)
    {
        child(p);
    }
    exit(0);
}

void child(int pf[])
{
    close(pf[1]); // father used to write
    int tmp;
    // try to read first number
    int read_result = read(pf[0], &tmp, sizeof(int));
    if (read_result == 0)
    {
        exit(0);
    }

    int pc[2];
    pipe(pc); // init pipe inter with children proc

    if (fork() == 0)
    {
        child(pc);
    }
    else
    {
        close(pc[0]);
        int prime = tmp;
        printf("prime %d \n", tmp);
        while (read(pf[0], &tmp, sizeof(int)) != 0)
        {
            if (tmp % prime != 0)
            {
                write(pc[1], &tmp, sizeof(int));
            }
        }
        close(pc[1]);
        wait((int *)0);
        exit(0);
    }
}