#include "../kernel/types.h"
#include "../kernel/fcntl.h"
#include "../user/user.h"

int main(int argc, char *argv[])
{
    int f_s[2];
    int s_f[2];
    pipe(f_s);
    pipe(s_f);
    char buf[1];

    int pid = fork();
    if (pid > 0)
    {
        write(f_s[1], " ", 1);
        read(s_f[0], buf, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
    else if (pid == 0)
    {
        read(f_s[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(s_f[1], " ", 1);
        exit(0);
    }
    else
    {
        exit(1);
    }
}