#include "utils/logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/cfg/argv.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/pattern_formatter-inl.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <fcntl.h>
#include <unistd.h>

#include <memory>
#include <chrono>
#include <format>
#include <filesystem>
#include <string_view>

const char* logger_name = "main";

namespace utils::logger
{

static std::string _filename = "";

class file_ptr_flag : public spdlog::custom_flag_formatter
{
    public:
        void format(const spdlog::details::log_msg &msg, const std::tm &, spdlog::memory_buf_t &dest) override
        {
            std::string filename = std::filesystem::path(msg.source.filename).filename().string();
            std::string new_flag = fmt::format("{}:{}", filename, msg.source.line);
            spdlog::details::scoped_padder p(new_flag.size(), padinfo_, dest);
            dest.append(new_flag.data(), new_flag.data() + new_flag.size());
        }

        std::unique_ptr<custom_flag_formatter> clone() const override
        {
            return spdlog::details::make_unique<file_ptr_flag>();
        }
};

void init(int argc, char** argv)
{
    int fd = open("/dev/tty", O_WRONLY);
    if (fd != -1)
    {
        dup2(fd, STDERR_FILENO);
        close(fd);
    }

    std::string log_filename;
    for (int i = 1; i < argc; ++i)
    {
        std::string_view arg(argv[i]);
        if (arg.find("--log_file=") == 0)
        {
            log_filename = std::string(arg.substr(11));
            logger::_filename = log_filename;
            break;
        }
    }

    if (log_filename.empty())
    {
        char current_exe[PATH_MAX];
        memset(current_exe, 0, sizeof(current_exe));
        readlink("/proc/self/exe", current_exe, sizeof(current_exe));

        auto now = std::chrono::floor <std::chrono::seconds> (std::chrono::system_clock::now());
        std::string str_now = std::format("{0:%F_%H-%M-%S}", now);

        log_filename = std::format("{}/logs/{}.txt", ::std::filesystem::path(current_exe).parent_path().string(), str_now);
        std::filesystem::create_directories(std::filesystem::path(log_filename).parent_path());
        logger::_filename = log_filename;
    }

    auto console_sink = std::make_shared <spdlog::sinks::stderr_color_sink_mt> ();
    auto file_sink = std::make_shared <spdlog::sinks::basic_file_sink_mt> (log_filename, false);

    auto formatter = std::make_unique <spdlog::pattern_formatter> ();
    formatter->add_flag <file_ptr_flag> ('K');
    formatter->set_pattern("[%d.%m.%Y %T.%f]  %^%-8l%$  %-15K %v");

    auto logger = std::make_shared <spdlog::logger> (logger_name, spdlog::sinks_init_list{console_sink, file_sink});
    logger->set_formatter(std::move(formatter));
    logger->set_level(spdlog::level::debug);

    spdlog::register_logger(logger);
    spdlog::cfg::load_argv_levels(argc, argv);

    console_sink->set_level(logger->level());
    file_sink->set_level(logger->level());

    spdlog::flush_on(spdlog::level::trace);
    spdlog::set_default_logger(logger);
}

const std::string& filename()
{
    return utils::logger::_filename;
}

}