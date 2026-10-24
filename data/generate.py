
import json
import random
from datetime import date, timedelta
from pathlib import Path

OUTPUT = Path("data.json")
COUNT = 200

categories = [
    {"id": 1, "name": "Salary"},
    {"id": 2, "name": "Games"},
    {"id": 3, "name": "Food"},
    {"id": 4, "name": "Transport"},
    {"id": 5, "name": "Entertainment"},
    {"id": 6, "name": "Housing"}
]

names = {
    1: ["Salary", "Bonus", "Freelance", "Refund"],
    2: ["Dota2", "Steam games", "Game DLC", "In-game purchase"],
    3: ["Groceries", "Lunch", "Dinner", "Coffee", "Restaurant"],
    4: ["Bus tickets", "Taxi", "Fuel", "Train ticket"],
    5: ["Cinema", "Concert", "Subscription", "Bowling"],
    6: ["Rent", "Electricity", "Internet", "Water"]
}

expense_ranges = {
    2: (500, 30000),
    3: (500, 20000),
    4: (300, 15000),
    5: (1000, 40000),
    6: (10000, 150000)
}

start_date = date(2025, 1, 1)
end_date = date.today()
days = (end_date - start_date).days

transactions = []

for i in range(1, COUNT + 1):
    category_id = random.randint(2, 6)

    if random.random() < 0.15:
        category_id = 1

    if category_id == 1:
        transaction_type = "income"
        amount = random.choice([
            random.randint(300000, 600000),
            random.randint(10000, 100000)
        ])
    else:
        transaction_type = "expense"
        amount = random.randint(*expense_ranges[category_id])

    transaction_date = start_date + timedelta(days=random.randint(0, days))

    transactions.append({
        "amountMinorUnits": amount,
        "categoryId": category_id,
        "currency": "UAH",
        "date": transaction_date.isoformat(),
        "id": i,
        "name": random.choice(names[category_id]),
        "type": transaction_type
    })

OUTPUT.parent.mkdir(parents=True, exist_ok=True)

with OUTPUT.open("w", encoding="utf-8") as file:
    json.dump({
        "categories": categories,
        "transactions": transactions
    }, file, indent=4, ensure_ascii=False)

print(f"Generated {COUNT} transactions: {OUTPUT}")
