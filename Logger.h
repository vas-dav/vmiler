//
// Created by tylen on 26.12.2023.
//

#ifndef VMILER_LOGGER_H
#define VMILER_LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdarg>
#include <vector>

namespace vmiler {

    enum LogSeverity {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    const std::string severityStringColors [] {
            "\x1b[34mINFO\x1b[0m",
            "\x1b[33mWARNING\x1b[0m",
            "\x1b[31mERROR\x1b[0m",
            "\x1b[35mDEBUG\x1b[0m",
    };

    const std::string severityString [] {
            "INFO",
            "WARNING",
            "ERROR",
            "DEBUG",
    };

    class Logger {
    public:
        explicit Logger(bool colored = true);

        ~Logger() = default;

        void debug(const char* fmt, ...);
        void error(const char* fmt, ...);
        void warning(const char* fmt, ...);
        void info(const char* fmt, ...);
        void usage(const char* fmt, ...);
        void debug(const std::string& log);
        void error(const std::string& log);
        void warning(const std::string& log);
        void info(const std::string& log);
        void usage(const std::string& log);

    private:
        void log_line(const std::string &log, LogSeverity severity);
        std::string getSeverity(LogSeverity severity) const;
        static std::string expandArgs(const char* fmt, std::va_list args) ;

        bool m_colored;
    };

    extern Logger logger;

}

#define WIP() vmiler::logger.error("%s:%s:%lu is work in progress. Do not use it.", __FILE__, __func__, __LINE__)

#endif //VMILER_LOGGER_H
