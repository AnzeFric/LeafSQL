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

**Limits:**
 - Name cannot contain whitespace - use underscores
 - The name has to be between 1 and 63 chars.
 - Name has to be unique. A database with the same name cannot be created.

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

**Attributes:**
- `PRIMARY` - Mark as primary key (1 per table)
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
**Limits:**
- Name cannot contain whitespace - use underscores
- The name has to be between 1 and 63 chars.
- Name has to be unique. A database with the same name cannot be created.
- PRIMARY(Primary key) attribute has to be set on one field of type INT.