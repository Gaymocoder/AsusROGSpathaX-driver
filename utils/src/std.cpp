#include "utils/std.h"

#include <spdlog/spdlog.h>

#include <unistd.h>
#include <linux/limits.h>

#include <cstring>
#include <iostream>

namespace utils::std
{

int check_root()
{
    char current_exe[PATH_MAX];
    memset(current_exe, 0, sizeof(current_exe));
    readlink("/proc/self/exe", current_exe, sizeof(current_exe));

    if (getuid() != 0)
    {
        int ret = execlp("pkexec", "pkexec", current_exe, NULL);
        if (ret == -1)
        {
            perror("execlp pkexec failed");
            return 1;
        }
    }
    return 0;
}

}