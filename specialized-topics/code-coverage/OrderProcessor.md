## Order Processing System depends on Order, Customer, and OrderItem classes.  Review and verify that these classes are written accurately and adhere to PEP 8 guidelines.

``` python
class Order:
    def __init__(self, customer=None, items=None):
        self.customer = customer
        self.items = items if items is not None else []


class Customer:
    def __init__(self, name):
        self.name = name


class OrderItem:
    def __init__(self, product_id, quantity, price):
        self.product_id = product_id
        self.quantity = quantity
        self.price = price

```

## I need to ensure that the OrderProcessor class is structured in a way that makes it easier to maintain, enhance, and test all possible branches and exceptions. Help me refactor the code to achieve this objective.

``` python

class OrderProcessor:
    def process_order(self, order):
        if order is None:
            raise ValueError("order cannot be None")

        if order.items is None or len(order.items) == 0:
            raise ValueError("Order must have at least one item.")

        for item in order.items:
            if item.quantity <= 0:
                raise ValueError("Item quantity must be greater than zero.")

            # Complex logic with multiple nested conditions
            if item.product_id == 0:
                if item.price > 100:
                    # Some complex business logic
                    print("High value item with no product ID.")
                else:
                    # Another complex business logic
                    print("Low value item with no product ID.")
            else:
                if item.price > 100:
                    # Some complex business logic
                    print("High value item with product ID.")
                else:
                    # Another complex business logic
                    print("Low value item with product ID.")

        # More complex logic
        if order.customer is None:
            raise ValueError("Order must have a customer.")

        # Process payment
        self.process_payment(order)

    def process_payment(self, order):
        # Payment processing logic
        print("Processing payment for order.")

```

## Write PyDoc tests for the OrderProcessor class to cover all possible branches and exceptions.
Test cases will include:
- Valid order processing
- Order with no items
- Order with invalid item quantity
- Order with no customer
- Items with different product IDs and price
Goal:
100% code coverage for the OrderProcessor class