//
// Created by anzef on 11. 07. 2026.
//

#include "Utils.h"

std::vector<std::vector<std::string>> Utils::getFileContentCSV(std::istream& file, const char delimiter) {
    std::vector<std::vector<std::string>> fileContent;
    std::string line;

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        };

        std::vector<std::string> fields;
        size_t start = 0;
        size_t pos;

        while ((pos = line.find(delimiter, start)) != std::string::npos) {
            fields.emplace_back(line, start, pos - start);
            start = pos + 1;
        }

        fields.emplace_back(line, start, line.size() - start); // last field

        fileContent.push_back(std::move(fields));
    }

    return fileContent;
}

void Utils::appendRowCSV(const std::string& path, const std::string& row) {
    std::ofstream file(path, std::ios::app | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + path);
    }

    file.write(row.data(), row.length());
    file.put('\n');
}