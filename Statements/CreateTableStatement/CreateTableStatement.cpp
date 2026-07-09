//
// Created by anzef on 1. 01. 2026.
//

#include "CreateTableStatement.h"

CreateTableStatement::CreateTableStatement(std::string _name, std::vector<std::string> _columns, std::vector<std::vector<std::string>> _attributes):
                                        name(std::move(_name)), columns(std::move(_columns)), attributes(std::move(_attributes)) {};

void CreateTableStatement::setName(std::string _name) {
        this->name = std::move(_name);
};

void CreateTableStatement::setColumns(std::vector<std::string> _columns) {
        this->columns = std::move(_columns);
};

void CreateTableStatement::addColumn(std::string column) {
        this->columns.push_back(std::move(column));
};

void CreateTableStatement::addAttribute(std::vector<std::string> attribute) {
        this->attributes.push_back(std::move(attribute));
};

void CreateTableStatement::setAttributes(std::vector<std::vector<std::string>> _attributes) {
        this->attributes = std::move(_attributes);
};

std::string CreateTableStatement::getName() const {
        return this->name;
}

std::vector<std::string> CreateTableStatement::getColumns() const {
        return this->columns;
};

std::vector<std::vector<std::string>> CreateTableStatement::getAttributes() const {
        return this->attributes;
};