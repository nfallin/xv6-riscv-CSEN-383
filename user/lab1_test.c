#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_PROC 10
struct pinfo {
    int ppid;
    int syscall_count;
    int page_usage;
};

void print_sysinfo(void)
{
    int n_active_proc, n_syscalls, n_free_pages;
    n_active_proc = sysinfo(0);
    n_syscalls = sysinfo(1);
    n_free_pages = sysinfo(2);
    printf("[sysinfo] active proc: %d, syscalls: %d, free pages: %d\n",
           n_active_proc, n_syscalls, n_free_pages);
}

int main(int argc, char *argv[])
{
    int n_proc;
    // int mem, ret, proc_pid[MAX_PROC] // not used yet
    if (argc < 3) {
        printf("Usage: %s [MEM] [N_PROC]\n", argv[0]);
        exit(-1);
    }

    // mem = atoi(argv[1]); // not used yet
    n_proc = atoi(argv[2]);
    if (n_proc > MAX_PROC) {
        printf("Cannot test with more than %d processes\n", MAX_PROC);
        exit(-1);
    }

    print_sysinfo();
    // more after I implement the second syscall
    exit(0);
}