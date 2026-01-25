# LeafSQL Documentation

## Database Operations

### Create a New Database

```sql
CREATE DATABASE <name>;
```

**Parameters:**
- `<name>` - Database name (string)

**Example:**
```
CREATE DATABASE LeafDB;
```


### Use a Database

```
USE <name>;
```

**Parameters:**
- `<name>` - Database name (string)

**Example:**
```sql
USE LeafDB;
```


## Table Operations

### Create a Table

```
CREATE TABLE <name> (
    <column> <attributes>,
    <column> <attributes>
);
```

**Parameters:**
- `<name>` - Table name (string)
- `<column>` - Column name (string)
- `<attributes>` - Column attributes (whitespace-separated values)

#### Available Attributes

**Data Types:**
- `INT` - Integer type
- `TEXT` - Text/string type
- `BOOLEAN` - Boolean type
- `TIMESTAMP` - Timestamp type

**Constraints:**
- `PRIMARY` - Mark as primary key (only 1 per table)
- `AUTO` - Auto-increment value (requires `INT` type)
- `UNIQUE` - Value must be unique in the table
- `NULL` - Allow null values (values are non-nullable by default)
- `DEFAULT <value>` - Set default value

**Example:**
```
CREATE TABLE users (
    id INT PRIMARY AUTO,
    username TEXT UNIQUE,
    email TEXT UNIQUE,
    age INT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    is_active BOOLEAN DEFAULT TRUE
);
```
