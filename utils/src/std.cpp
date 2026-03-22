#include "utils/logger.h"
#include "utils/macro.h"
#include "utils/std.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <linux/limits.h>

#include <cstring>
#include <iostream>
#include <algorithm>
namespace utils::std
{

int check_root(int argc, char** argv)
{
    SUCCESS(!getuid(), "The process's run with root\n");

    char current_exe[PATH_MAX];
    memset(current_exe, 0, sizeof(current_exe));
    readlink("/proc/self/exe", current_exe, sizeof(current_exe));

    pid_t pid = fork();
    CRIT_ASSERT((pid != -1), "Failed to fork the proccess");

    if (pid == 0)
    {
        TRACE("Rerunning proccess with root");

        char** args = new char* [argc + 3];
        args[0] = strdup("pkexec");
        args[1] = current_exe;
        ::std::copy(argv + 1, argv + argc, args + 2);
        args[argc + 2] = NULL;

        int devnull = open("/dev/null", O_WRONLY);
        dup2(devnull, STDERR_FILENO);
        close(devnull);

        execvp("pkexec", args);
        INFO("HI THERE");
        _exit(127);
    }

    int status;
    waitpid(pid, &status, 0);
    status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;

    ASSERT(!status, "Failed to get root rights");
    _exit(0);
}

}
