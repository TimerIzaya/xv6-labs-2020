#include "../kernel/types.h"
#include "../kernel/fcntl.h"
#include "../user/user.h"

#define PRIME_NUM 35

void child(int pf[]);

int main(int argc, char *argv[])
{
    char arr[512];
    printf("%d", sizeof arr);
}
