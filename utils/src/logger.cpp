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
#include <filesystem>

namespace utils::logger
{

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

    auto now = std::chrono::floor <std::chrono::seconds> (std::chrono::system_clock::now());
    std::string str_now = std::format("{0:%F_%H-%M-%S}", now);
    auto console_sink = std::make_shared <spdlog::sinks::stderr_color_sink_mt> ();
    auto file_sink = std::make_shared <spdlog::sinks::basic_file_sink_mt> (std::format("logs/{}.txt", str_now), true);

    auto formatter = std::make_unique <spdlog::pattern_formatter> ();
    formatter->add_flag <file_ptr_flag> ('K');
    formatter->set_pattern("[%d.%m.%Y %T.%f]  %^%-8l%$  %-15K %v");

    auto logger = std::make_shared <spdlog::logger> ("main", spdlog::sinks_init_list{console_sink, file_sink});
    logger->set_formatter(std::move(formatter));

    logger->set_level(spdlog::level::info);
    spdlog::register_logger(logger);
    spdlog::cfg::load_argv_levels(argc, argv);

    console_sink->set_level(logger->level());
    file_sink->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
}

}