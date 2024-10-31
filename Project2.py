from datetime import date


class Transaction:
    def __init__(self, amount = 0, category = "", curDate = date.today(), description = ""):
        self.amount = amount
        self.category = category
        self.date = curDate
        self.description = description
    
    def get_transaction_info(self):
        print("1. Income:{}".format(self.amount))
    

class Expense:
    def __init__(self, amount, category, description, payment_method = ""):
        super().__init__(amount, category, date, description)
        self.payment_method = payment_method

    def get_expense_info(self):
        return self.amount, self.category, self.date, self.description, self.payment_method
    

class Income(Transaction):
    def __init__(self, source = ""):
        self.source = source

    def get_income_info(self):
        return self.amount, self.category, self.date, self.description, self.source
    

class Budget:
    def __init__(self, category, limit):
        self.category = category
        self.limit = limit
    
    def is_within_budget(self, amount):
        return amount <= self.limit
    
    def get_budget_info(self):
        return self.category, self.limit
    

class FinanceTracker:
    def __init__(self, transactions, budgets):
        self.transactions = transactions
        self.budgets = budgets

    def add_transaction(self, transaction):
        self.transactions.append(transaction)

    def add_budget(self, budget):
        self.budgets.append(budget)

    def get_total_expenses(self):
        total_expenses = 0
        for transaction in self.transactions:
            if isinstance(transaction, Expense):
                total_expenses += transaction.amount
        return total_expenses



def appRunning(newTracker):
    prompt = ("""
Please choose an option:
1. Add Income
2. Add Expense
3. Set Budget
4. View Transactions
5. View Financial Summary
6. Exit
> """)
    userInput = input(prompt)
    
    while userInput != 6:
        if userInput == "1":
            incomeAmount = input("Enter income amount: ")
            incomeSource = input("Enter income source: ")
            incomeDescription = input("Enter description: ")
            newIncome = Income(incomeAmount, description = incomeDescription, source = incomeSource)
            newTracker.add_transaction(newIncome)
            print("Income added successfully!")
        elif userInput == "2":
            expenseAmount = input("Enter expense amount: ")
            expenseCategory = input("Enter expense category: ")
            expensePayMethod = input("Enter payment method: ")
            expenseDescription = input("Enter description: ")
            newTracker.add_transaction(Expense(expenseAmount, expenseCategory, description = expenseDescription, payment_method = expensePayMethod))
        elif userInput == "3":
            pass
        elif userInput == "4":
            pass
        elif userInput == "5":
            pass
        else:
            print("Goodbye!")
            break
    
        userInput = input(prompt)

    return newTracker


def main():
    print("Welcome to the Personal Finance Tracker!")
    newTracker = FinanceTracker([], [])
    appRunning(newTracker)

if __name__ == "__main__":
    main()