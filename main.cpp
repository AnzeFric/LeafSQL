#include <iostream>
#include "QueryParser/QueryParser.h"

int main() {
    const std::string selectQuery = "SELECT * FROM table;";
    const std::string createDBQuery = "CREATE DATABASE LeafDB;";
    const std::string useDBQuery = "USE LeafDB;";
    const std::string createTableQuery = "CREATE TABLE users (id INT PRIMARY KEY, username TEXT NOT NULL UNIQUE, email TEXT NOT NULL UNIQUE, age INT32, created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, is_active BOOLEAN DEFAULT TRUE);";
    const std::string insertQuery = "INSERT INTO users (id, name, email, created_at) VALUES (1, Alice, alice@example.com, NOW());";

    QueryParser queryParser = QueryParser(useDBQuery);
    queryParser.parseQuery();

    queryParser.setQuery(createTableQuery);
    queryParser.parseQuery();

    queryParser.setQuery(insertQuery);
    queryParser.parseQuery();

    return 0;
}
