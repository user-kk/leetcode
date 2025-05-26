#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int setup_log() {
    // 设置日志格式，包含函数名、文件名和行号
    auto logger = spdlog::stdout_color_mt("console");

    logger->set_pattern("%^[%l] [%t] %v (%s:%#)%$");
#ifdef NDEBUG
    // 在其他模式下设置为 info 级别
    logger->set_level(spdlog::level::info);
#else
    // 在Debug模式下设置为 debug 级别
    logger->set_level(spdlog::level::debug);
#endif
    spdlog::set_default_logger(logger);

    SPDLOG_INFO("log config success");
    return 0;
}

int setup_all() noexcept {
    setup_log();
    return 0;
}

int global_config = setup_all();