#include <iostream>
#include "QueryParser/QueryParser.h"

int main() {
    const std::string selectQuery = "SELECT * FROM table;";
    const std::string createDBQuery = "CREATE DATABASE LeafDB;";
    const std::string useDBQuery = "USE LeafDB;";
    const std::string createTableQuery = "CREATE TABLE users (id INT PRIMARY KEY, username TEXT NOT NULL UNIQUE, email TEXT NOT NULL UNIQUE, age INT32, created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, is_active BOOLEAN DEFAULT TRUE);";

    QueryParser queryParser = QueryParser(useDBQuery);
    queryParser.parseQuery();

    queryParser.setQuery(createTableQuery);
    queryParser.parseQuery();

    return 0;
}
