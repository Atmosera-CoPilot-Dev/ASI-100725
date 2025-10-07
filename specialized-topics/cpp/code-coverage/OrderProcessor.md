
## Order Processing System depends on Order, Customer, and OrderItem classes. Review and verify that these classes are written accurately and adhere to modern C++ best practices and style guidelines.

```cpp
#include <string>
#include <vector>
#include <memory>

class Customer {
public:
	explicit Customer(const std::string& name) : name(name) {}
	std::string name;
};

class OrderItem {
public:
	OrderItem(int product_id, int quantity, double price)
		: product_id(product_id), quantity(quantity), price(price) {}
	int product_id;
	int quantity;
	double price;
};

class Order {
public:
	Order(std::shared_ptr<Customer> customer = nullptr, std::vector<OrderItem> items = {})
		: customer(customer), items(std::move(items)) {}
	std::shared_ptr<Customer> customer;
	std::vector<OrderItem> items;
};
```

## I need to ensure that the OrderProcessor class is structured in a way that makes it easier to maintain, enhance, and test all possible branches and exceptions. Help me refactor the code to achieve this objective.

```cpp

class OrderProcessor {
public:
	void processOrder(Order* order) {
		if (order == nullptr) {
			throw std::invalid_argument("order cannot be nullptr");
		}
		if (order->items.size() == 0) {
			throw std::invalid_argument("Order must have at least one item.");
		}
		for (size_t i = 0; i < order->items.size(); ++i) {
			if (order->items[i].quantity <= 0) {
				throw std::invalid_argument("Item quantity must be greater than zero.");
			}
			if (order->items[i].product_id == 0) {
				if (order->items[i].price > 100) {
					std::cout << "High value item with no product ID." << std::endl;
				} else {
					std::cout << "Low value item with no product ID." << std::endl;
				}
			} else {
				if (order->items[i].price > 100) {
					std::cout << "High value item with product ID." << std::endl;
				} else {
					std::cout << "Low value item with product ID." << std::endl;
				}
			}
		}
		if (order->customer == nullptr) {
			throw std::invalid_argument("Order must have a customer.");
		}
		processPayment(order);
	}

	void processPayment(Order* order) {
		std::cout << "Processing payment for order." << std::endl;
	}
};
```

## (optional)Write unit tests for the OrderProcessor class to cover all possible branches and exceptions.
Test cases will include:
- Valid order processing
- Order with no items
- Order with invalid item quantity
- Order with no customer
- Items with different product IDs and price
Goal:
100% code coverage for the OrderProcessor class