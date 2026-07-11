//
// Created by anzef on 11. 07. 2026.
//

#include "Utils.h"

std::vector<std::vector<std::string>> Utils::getFileSplitRows(const std::string& filePath, const char delimiter) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("getFileSplitRows - Failed to open file (on path: " + filePath + ")");
    }

    std::vector<std::vector<std::string>> fileSplitRows;
    std::string line;

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        };

        std::vector<std::string> rowFields;
        size_t start = 0;
        size_t pos;

        while ((pos = line.find(delimiter, start)) != std::string::npos) {
            rowFields.emplace_back(line, start, pos - start);
            start = pos + 1;
        }

        rowFields.emplace_back(line, start, line.size() - start); // last field

        fileSplitRows.push_back(std::move(rowFields));
    }

    return fileSplitRows;
}

std::vector<std::string> Utils::getFileRowsCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("getFileRowsCSV - Failed to open file (on path: " + filePath + ")");
    }

    std::string column;
    std::vector<std::string> columns;

    while (std::getline(file, column)) {
        if (column.empty()) {
            continue;
        };

        columns.push_back(column);
    }

    return columns;
}

void Utils::appendRowCSV(const std::string& path, const std::string& row) {
    std::ofstream file(path, std::ios::app | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + path);
    }

    file.write(row.data(), row.length());
    file.put('\n');
}