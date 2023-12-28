//
// Created by tylen on 28.12.2023.
//

#include "VmiSourceData.h"

using namespace vmiler;

VmiSourceData::VmiSourceLine::VmiSourceLine(std::string line, std::size_t count,
                                            const std::string& sourceFilePath) : m_line(std::move(line)),
                                                                                     m_line_count(count),
                                                                                     m_srcFilePath(sourceFilePath) {
    position = 0;
    isEnd = false;
}

VmiSourceData::VmiSourceLine::VmiSourceLine() {
    position = 0;
    isEnd = true;
}

std::string VmiSourceData::VmiSourceLine::getFullLine() const {
    return m_line;
}

void VmiSourceData::VmiSourceLine::throwExpectationNotMet(const std::string& expected,
                                                          const std::string& after) {
    std::string filePosition {getFilePositionStr()};
    std::stringstream ss;
    ss << std::endl << filePosition << " expected: \"" << expected << "\" after \"";
    ss << after << "\"" << std::endl;
    ss << m_srcFilePath << ":" << m_line_count << ":" << position << " " << m_line << std::endl;
    for (int i = 0; i < position + filePosition.size(); ++i) {
        ss << " ";
    }
    ss << "^~~" << std::endl;
    logger.error(ss.str());
}

std::string VmiSourceData::VmiSourceLine::getFilePositionStr() {
    std::stringstream ss;
    ss << m_srcFilePath << ":" << m_line_count << ":" << position;
    return ss.str();
}

VmiSourceData::VmiSourceData(const std::string &sourceFilePath) : m_srcFilePath(sourceFilePath) {
    m_srcFile.open(sourceFilePath);
    if (!m_srcFile.is_open()) {
        logger.error("Unable to open file: %s", sourceFilePath.c_str());
    }
    vmiler::logger.info("File opened %s", sourceFilePath.c_str());
}

VmiSourceData::VmiSourceLine VmiSourceData::getNextLine() {
    std::string currentLineStr;
    if(std::getline(m_srcFile, currentLineStr)) {
        m_lines.emplace_back(currentLineStr, m_lines.size() + 1, m_srcFilePath);
        return m_lines.back();
    }
    return {};
}
