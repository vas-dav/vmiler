//
// Created by tylen on 28.12.2023.
//

#ifndef VMILER_VMISOURCEDATA_H
#define VMILER_VMISOURCEDATA_H

#include <vector>
#include <string>
#include <fstream>
#include <utility>

#include "Logger.h"

namespace vmiler {
    class VmiSourceData {
    public:
        struct VmiSourceLine {
        public:
            VmiSourceLine();
            explicit VmiSourceLine(std::string line, std::size_t count, const std::string& sourceFilePath);
            void throwExpectationNotMet(const std::string& expected, const std::string& after);
            std::string getFullLine() const;
            std::size_t position;
            bool isEnd;
        private:
            std::string getFilePositionStr();
            std::string m_line;
            std::size_t m_line_count;
            std::string m_srcFilePath;
        };

        explicit VmiSourceData(const std::string &sourceFilePath);
        ~VmiSourceData() = default;
        VmiSourceLine getNextLine();


    private:
        std::ifstream m_srcFile;
        std::string m_srcFilePath;
        std::vector<VmiSourceLine> m_lines;
    };
}

#endif //VMILER_VMISOURCEDATA_H