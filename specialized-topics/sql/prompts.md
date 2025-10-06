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

Help me understand how to use entity framework with C# to create a data library based on the inventory database. I am using .NET 8.0.
- show which nuget packages would I need to install to use SQLite3

Help me create POCO classes for the following tables in the inventory database:
- products, categories, suppliers
- The entities (Supplier, Category, Product) must be represented as POCOs in namespace DataLibrary and each in defined in a separate file.
- The schemas for the POCO classes must match the columns defined in the 'sql/scripts/inventory.sql' script of the DataLibary project.

Help me configure the DbContext to use SQLite based on the following requirements:
- The class that inherits the DbContext class (InventoryDbContext)  must be defined within the same namespace  as the entity classes (DataLibrary)
- Nullable reference types are enabled.
- Implicit 'usings' are enabled.
- All tables and properties are mapped to the columns defined in the inventory.sql script.
- Register the DbContext for Dependency Injection.

The dll of the DataLibrary will be referenced in a web api project. How do I ensure that the 'SQLite/inventory.db' database in the DataLibrary project will be easy to locate relative to the database?

## Web Api

Help me extend the core web api project with the following requirements:
- Supports SQLite database operations.
- Provides two GET endpoints for accessing product data.
- Includes Swagger for API documentation and testing.
- Configures the database path dynamically for portability.
- Implements basic error handling and relationship management using Entity Framework Core.
- Enforces HTTPS and integrates with the ASP.NET Core middleware pipeline.


## Testing

I want perform integration testing for the inventory Web API. I do not want to use the actual database in my tests. Please help me set up a new MSTest project following these requirements:
- An in-memory database is created and seeded during the service configuration.
- A static method seeds the in-memory database with sample data for Products, Categories, and Suppliers, ensuring the tests have data to work with.
- The integration tests use a Web Application Factory to create an HTTP client for testing the API endpoints.
- Test methods validate the API's behavior against expected outcomes.





