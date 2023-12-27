//
// Created by tylen on 26.12.2023.
//

#include "Logger.h"

using namespace vmiler;

Logger vmiler::logger;

Logger::Logger(bool colored) {
    m_colored = colored;
}

void Logger::debug(const char* fmt, ...) {
    std::va_list args;
    va_start(args, fmt);
    log_line(expandArgs(fmt, args), LogSeverity::DEBUG);
    va_end(args);
}

void Logger::warning(const char* fmt, ...) {
    std::va_list args;
    va_start(args, fmt);
    log_line(expandArgs(fmt, args), LogSeverity::WARNING);
    va_end(args);
}

void Logger::error(const char* fmt, ...) {
    std::va_list args;
    va_start(args, fmt);
    log_line(expandArgs(fmt, args), LogSeverity::ERROR);
    va_end(args);
    exit(1);
}

void Logger::info(const char* fmt, ...) {
    std::va_list args;
    va_start(args, fmt);
    log_line(expandArgs(fmt, args), LogSeverity::INFO);
    va_end(args);
}

void Logger::usage(const char* fmt, ...) {
    std::stringstream ss;
    std::va_list args;
    va_start(args, fmt);
    ss << expandArgs(fmt, args) << std::endl;
    va_end(args);
    ss << "Usage: vmi <source.vmi>" << std::endl;
    log_line(ss.str(), LogSeverity::ERROR);
    exit(1);
}

void Logger::debug(const std::string& log) {
    debug(log.c_str());
}

void Logger::warning(const std::string& log) {
    warning(log.c_str());
}

void Logger::error(const std::string& log) {
    error(log.c_str());
}

void Logger::info(const std::string& log) {
    info(log.c_str());
}

void Logger::usage(const std::string& log) {
    usage(log.c_str());
}

void Logger::log_line(const std::string &log, LogSeverity severity) {
    std::stringstream ss;
    ss << "VMILER [" << getSeverity(severity) << "]: " << log << std::endl;
    std::cout << ss.str();
}

std::string Logger::getSeverity(LogSeverity severity) const {
    return m_colored ?
           std::string(severityStringColors[severity]) :
           std::string(severityString[severity]);
}

std::string Logger::expandArgs(const char *fmt, std::va_list args) {

    std::va_list args2;
    va_copy(args2, args);
    std::vector<char> buf(1 + std::vsnprintf(nullptr, 0, fmt, args));
    std::vsnprintf(buf.data(), buf.size(), fmt, args2);
    va_end(args2);
    return std::string{buf.data()};
}
