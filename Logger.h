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

        void debug(const std::string &log);

        void error(const std::string &log, int exitCode = 0);

        void warning(const std::string &log);

        void info(const std::string &log);

        void usage(const std::string &log="No arguments provided");

    private:
        void log_line(const std::string &log, LogSeverity severity);
        std::string getSeverity(LogSeverity severity) const;

        bool m_colored;
    };

    extern Logger logger;

}

#endif //VMILER_LOGGER_H
