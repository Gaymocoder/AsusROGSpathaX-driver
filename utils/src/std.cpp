#include "utils/logger.h"
#include "utils/std.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <linux/limits.h>

#include <vector>
#include <string>
#include <format>
#include <cstring>
#include <algorithm>

namespace utils::std
{

int check_root(int argc, char** argv)
{
    SUCCESS(!getuid(), DEBUG, true, "The process's run with root");
    WARN("The app's run without superuser priveleges, requesting root");

    char current_exe[PATH_MAX];
    memset(current_exe, 0, sizeof(current_exe));
    readlink("/proc/self/exe", current_exe, sizeof(current_exe));

    pid_t pid = fork();
    CRIT_ASSERT((pid != -1), "Failed to fork the proccess");
    SUCCESS(pid != 0, DEBUG, false, "Forked the process, child pid: {}", pid);

    if (pid == 0)
    {
        DEBUG("Child: Trying to rerun proccess with root");
        static ::std::string log_arg = ::std::format("--log_file={}", utils::logger::filepath());        
        
        ::std::vector <char*> args = {const_cast <char*> ("pkexec"), current_exe};
        args.push_back(const_cast <char*> (log_arg.c_str()));
        args.insert(args.end(), argv + 1, argv + argc);
        args.push_back(nullptr);

        int devnull = open("/dev/null", O_WRONLY);
        dup2(devnull, STDERR_FILENO);
        close(devnull);

        execvp("pkexec", args.data());
        CRITICAL("Child: Failed to launch pkexec, exiting");
        _exit(127);
    }

    int status;
    waitpid(pid, &status, 0);
    status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;

    ASSERT(!status, "Parent: Failed to get root rights");
    _exit(0);
}

}
