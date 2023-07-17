#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    printf("PID: %d\n", pid);

    pid_t ppid = getppid();
    printf("PPID: %d\n", ppid);

    uid_t uid = getuid();
    printf("UID: %d\n", uid);

    uid_t euid = geteuid();
    printf("EUID: %d\n", euid);

    gid_t gid = getgid();
    printf("GID: %d\n", gid);

    pid_t sid = getsid(pid);
    printf("SID: %d\n", sid);
}