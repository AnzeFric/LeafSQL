1. Create a new database:
    CREATE DATABASE <name>;

Parameters:
    <name> - string

Example:
CREATE DATABASE LeafDB;

2. Use a database:
   USE <name>;

Parameters:
    <name> - string

Example:
USE LeafDB;

3. Create a table:
   CREATE TABLE <name> (
        <column> <attributes>,
        <column> <attributes>
   );

Parameters:
    <name> - string
    <column> - string
    <attributes> - string array

<attributes> - Whitespace separated string values:
Basic types: INT, TEXT, BOOLEAN
Complex types: TIMESTAMP
Setting a primary key(only 1 per table): PRIMARY
Setting value to auto increment(has to be INT type): AUTO
Value has to be unique in the table: UNIQUE
Value has to be nullable(by default values are not nullable): NULL
Setting a default value: DEFAULT <value>

Example:
CREATE TABLE users (
    id INT PRIMARY, 
    username TEXT UNIQUE, 
    email TEXT UNIQUE, 
    age NULL INT, 
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, 
    is_active BOOLEAN DEFAULT TRUE
);