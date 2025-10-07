# Inventory Management System sample prompts

## SQLite

I want to use the SQLite command-line tool.
- Provide a link to download the SQLite command-line tool.
- Provide a very brief overiew of the SQLite command-line tool using the documentation as a source.
- Show how to create a database named 'sql/inventory.db' using the SQLite script 'sql/scripts/inventory.sql as the source. 
- Show the command to display all tables and views. 
- Show the SQL command to select all records from the 'products' table.
- Show how to exit the SQLite command-line tool.

## Data Library

Help me understand how to use a modern C++ ORM (such as ODB or sqlite_orm) to create a data library based on the inventory database. I am using GNU C++.
- Show which libraries or packages I would need to install to use SQLite3 with C++.

Help me create C++ classes for the following tables in the inventory database:
- products, categories, suppliers
- The entities (Supplier, Category, Product) must be represented as C++ classes in namespace DataLibrary and each defined in a separate file.
- The schemas for the C++ classes must match the columns defined in the 'sql/scripts/inventory.sql' script of the DataLibrary project.

Help me configure the ORM context or equivalent to use SQLite based on the following requirements:
- The class that manages the database context (e.g., InventoryDbContext or equivalent) must be defined within the same namespace as the entity classes (DataLibrary).
- Use modern C++ features (e.g., smart pointers, optional types).
- All tables and properties are mapped to the columns defined in the inventory.sql script.
- Show how to register or initialize the database context for use in the application.

The library of the DataLibrary will be referenced in a web API project. How do I ensure that the 'SQLite/inventory.db' database in the DataLibrary project will be easy to locate relative to the application binary?

## Web API

Help me extend the core web API project with the following requirements:
- Supports SQLite database operations using C++.
- Provides two GET endpoints for accessing product data.
- Includes OpenAPI/Swagger or similar for API documentation and testing.
- Configures the database path dynamically for portability.
- Implements basic error handling and relationship management using the chosen C++ ORM.
- Enforces HTTPS and integrates with the C++ web server middleware pipeline.

## Testing

I want to perform integration testing for the inventory web API. I do not want to use the actual database in my tests. Please help me set up a new C++ test project following these requirements:
- An in-memory database is created and seeded during the service configuration.
- A static method seeds the in-memory database with sample data for Products, Categories, and Suppliers, ensuring the tests have data to work with.
- The integration tests use a test web server or application factory to create an HTTP client for testing the API endpoints.
- Test methods validate the API's behavior against expected outcomes.





