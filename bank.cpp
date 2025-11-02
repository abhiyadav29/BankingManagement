#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

class Account {
private:
    unsigned long long accNo;
    string name;
    double balance;

public:
    Account(unsigned long long a, string n, double b)
        : accNo(a), name(n), balance(b) {}

    unsigned long long getAccNo() const { return accNo; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    void deposit(double amt) { balance += amt; }

    bool withdraw(double amt) {
        if (amt > balance) {
            cout << " Insufficient balance!\n";
            return false;
        }
        balance -= amt;
        return true;
    }

    void showAccount() const {
        cout << "\nAccount Number : " << accNo
             << "\nName           : " << name
             << "\nBalance        : " << fixed << setprecision(2) << balance << "\n";
    }
};

vector<Account> accounts;

//  Helper to clear input safely
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//  Find account by number
Account* findAccount(unsigned long long accNo) {
    for (auto &acc : accounts) {
        if (acc.getAccNo() == accNo)
            return &acc;
    }
    return nullptr;
}

//  Create new account
void createAccount() {
    unsigned long long accNo;
    string name;
    double balance;

    cout << "Enter Account Number (12 digits): ";
    while (!(cin >> accNo) || to_string(accNo).size() != 12) {
        cout << " Invalid input. Please enter a 12-digit account number: ";
        clearInput();
    }

    if (findAccount(accNo)) {
        cout << "Account with this number already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    clearInput();
    getline(cin, name);

    cout << "Enter Initial Balance: ";
    while (!(cin >> balance) || balance < 0) {
        cout << " Invalid amount. Enter positive value: ";
        clearInput();
    }

    accounts.push_back(Account(accNo, name, balance));
    cout << " Account created successfully!\n";
}

//  Deposit
void depositAmount() {
    unsigned long long accNo;
    double amt;
    cout << "Enter Account Number: ";
    while (!(cin >> accNo)) {
        cout << " Invalid input. Try again: ";
        clearInput();
    }

    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << " Account not found!\n";
        return;
    }

    cout << "Enter Amount to Deposit: ";
    while (!(cin >> amt) || amt <= 0) {
        cout << " Invalid amount. Try again: ";
        clearInput();
    }

    acc->deposit(amt);
    cout << " Amount Deposited Successfully!\n";
}

//  Withdraw
void withdrawAmount() {
    unsigned long long accNo;
    double amt;
    cout << "Enter Account Number: ";
    while (!(cin >> accNo)) {
        cout << " Invalid input. Try again: ";
        clearInput();
    }

    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter Amount to Withdraw: ";
    while (!(cin >> amt) || amt <= 0) {
        cout << " Invalid amount. Try again: ";
        clearInput();
    }

    if (acc->withdraw(amt))
        cout << " Withdrawal Successful!\n";
}

//  Check balance by account number
void checkBalance() {
    unsigned long long accNo;
    cout << "Enter Account Number: ";
    while (!(cin >> accNo)) {
        cout << " Invalid input. Try again: ";
        clearInput();
    }

    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << " Account not found!\n";
        return;
    }

    cout << "\n Current Balance for Account [" << acc->getAccNo() << "] : ₹"
         << fixed << setprecision(2) << acc->getBalance() << "\n";
}

// Display all accounts
void displayAllAccounts() {
    if (accounts.empty()) {
        cout << "No accounts to display.\n";
        return;
    }

    cout << "\n-----------------------------------------------\n";
    cout << setw(15) << "Account No"
         << setw(20) << "Name"
         << setw(15) << "Balance\n";
    cout << "-----------------------------------------------\n";

    for (const auto &acc : accounts) {
        cout << setw(15) << acc.getAccNo()
             << setw(20) << acc.getName()
             << setw(15) << fixed << setprecision(2) << acc.getBalance() << "\n";
    }
}

//  Delete an account
void deleteAccount() {
    unsigned long long accNo;
    cout << "Enter Account Number to Delete: ";
    while (!(cin >> accNo)) {
        cout << " Invalid input. Try again: ";
        clearInput();
    }

    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccNo() == accNo) {
            accounts.erase(it);
            cout << " Account deleted successfully!\n";
            return;
        }
    }

    cout << " Account not found!\n";
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\n===============================\n";
        cout << "      BANKING SYSTEM MENU\n";
        cout << "===============================\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Amount\n";
        cout << "3. Withdraw Amount\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Delete Account\n";
        cout << "7. Exit\n";
        cout << "-------------------------------\n";
        cout << "Enter Your Choice: ";

        while (!(cin >> choice)) {
            cout << " Invalid choice. Enter again: ";
            clearInput();
        }

        cout << "\n";

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositAmount(); break;
            case 3: withdrawAmount(); break;
            case 4: checkBalance(); break;
            case 5: displayAllAccounts(); break;
            case 6: deleteAccount(); break;
            case 7: cout << " Thank you for using the Banking System!\n"; break;
            default: cout << " Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}

