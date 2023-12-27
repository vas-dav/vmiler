//
// Created by tylen on 26.12.2023.
//

#include "Logger.h"

using namespace vmiler;

Logger vmiler::logger;

Logger::Logger(bool colored) {
    m_colored = colored;
}

void Logger::debug(const std::string &log) {
    log_line(log, LogSeverity::DEBUG);
}

void Logger::warning(const std::string &log) {
    log_line(log, LogSeverity::WARNING);
}

void Logger::error(const std::string &log, const int exitCode) {
    log_line(log, LogSeverity::ERROR);
    if (exitCode) exit(exitCode);
}

void Logger::info(const std::string &log) {
    log_line(log, LogSeverity::INFO);
}

void Logger::usage(const std::string &log) {
    std::stringstream ss;
    ss << log << std::endl;
    ss << "Usage: vmi <source.vmi>" << std::endl;
    log_line(ss.str(), LogSeverity::ERROR);
    exit(1);
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
