#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

void find(char* path, char* target_file);

int main(int argc, char* argv[]) {
    if (argc > 3) {
        {
            fprintf(2, "ERROR: You need pass in only 2 arguements\n");
            exit(1);
        }
    }
    char* target_path = argv[1];
    char* target_file = argv[2];
    find(target_path, target_file);
    exit(0);
}

void find(char* path, char* target_file) {
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512], *p;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "ERROR: Can't open %s \n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "ERROR: Can't stat %s \n", path);
        return;
    }

    // read the name of each file/folder under the folder specified by fd
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        if (de.inum == 0) {
            continue;
        }
        memmove(p, de.name, DIRSIZ);

        if (stat(buf, &st) < 0) {
            fprintf(2, "ERROR: Can't stat %s \n", buf);
        }

        switch (st.type) {
            case T_FILE:
                if (strcmp(target_file, de.name) == 0) {
                    printf("%s \n", buf);
                }
                break;
            case T_DIR:
                if (strcmp(".", de.name) != 0 && strcmp("..", de.name) != 0) {
                    find(buf, target_file);
                }
            default:
                break;
        }
    }
    close(fd);
    return;
}