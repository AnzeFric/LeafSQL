//
// Created by anzef on 11. 07. 2026.
//

#include "Utils.h"

#include <algorithm>
#include <unordered_set>

// TODO: Fix method not parsing id correctly, on insert. Also check other INT types
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
        size_t pos = line.find(delimiter, start) != std::string::npos;

        rowFields.emplace_back(line, start, pos - start);
        start = pos + 1;

        while ((pos = line.find(delimiter, start)) != std::string::npos) {
            start++;
            rowFields.emplace_back(line, start, pos - start);
            start = pos + 1;
        }

        start++;
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

void Utils::deleteRowCSV(const std::string& path, const int& rowIndex) {
    std::string tempFile = path + ".tmp";

    std::ifstream in(path);
    std::ofstream out(tempFile);

    std::string line;
    size_t currentIndex = 0;

    while (std::getline(in, line)) {
        if (currentIndex != rowIndex) {
            out << line << "\n";
        }
        ++currentIndex;
    }

    in.close();
    out.close();

    std::remove(path.c_str());
    std::rename(tempFile.c_str(), path.c_str());
}

void Utils::deleteRowsCSV(const std::string& path, const std::vector<int>& rowIndex) {
    std::string tempFile = path + ".tmp";

    std::ifstream in(path);
    std::ofstream out(tempFile);

    std::string line;
    size_t currentIndex = 0;

    std::unordered_set<std::size_t> rowIndexSet(rowIndex.begin(), rowIndex.end());

    while (std::getline(in, line)) {
        if (!rowIndexSet.contains(currentIndex)) {
            out << line << "\n";
        }
        ++currentIndex;
    }

    in.close();
    out.close();

    std::remove(path.c_str());
    std::rename(tempFile.c_str(), path.c_str());
}

std::string Utils::strToUpper(const std::string& str) {
    std::string upperStr;
    for (auto & c: str) {
        upperStr += static_cast<char>(toupper(c));
    }
    return upperStr;
}
