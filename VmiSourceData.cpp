//
// Created by tylen on 28.12.2023.
//

#include "VmiSourceData.h"

using namespace vmiler;

VmiSourceData::VmiSourceLine::VmiSourceLine(std::string line) : m_line(std::move(line)) {
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

VmiSourceData::VmiSourceData(const std::string &sourceFilePath) {
    srcFile.open(sourceFilePath);
    if (!srcFile.is_open()) {
        logger.error("Unable to open file: %s", sourceFilePath.c_str());
    }
    vmiler::logger.info("File opened %s", sourceFilePath.c_str());
}

VmiSourceData::VmiSourceLine VmiSourceData::getNextLine() {
    std::string currentLineStr;
    if(std::getline(srcFile, currentLineStr)) {
        return VmiSourceData::VmiSourceLine(currentLineStr);
    }
    return {};
}
