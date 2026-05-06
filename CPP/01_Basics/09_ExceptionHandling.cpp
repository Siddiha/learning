// ─────────────────────────────────────────
//  EXCEPTION HANDLING
// ─────────────────────────────────────────

#include <iostream>
#include <stdexcept>   // standard exceptions
#include <string>
using namespace std;

// ── Custom exception ──────────────────────
class InsufficientFundsException : public runtime_error {
    double amount_;
    double balance_;
public:
    InsufficientFundsException(double amount, double balance)
        : runtime_error("Insufficient funds"),
          amount_(amount), balance_(balance) {}

    double amount()  const { return amount_; }
    double balance() const { return balance_; }

    const char* what() const noexcept override {
        static string msg;
        msg = "Cannot withdraw " + to_string(amount_) +
              ". Balance is only " + to_string(balance_);
        return msg.c_str();
    }
};

class ValidationException : public invalid_argument {
public:
    explicit ValidationException(const string& msg)
        : invalid_argument(msg) {}
};

double withdraw(double balance, double amount) {
    if (amount <= 0)
        throw ValidationException("Amount must be positive");
    if (amount > balance)
        throw InsufficientFundsException(amount, balance);
    return balance - amount;
}

int main() {

    // ── Basic try/catch ───────────────────────
    try {
        int result = 10 / 0;   // undefined behavior in C++ (not an exception!)
        cout << result << endl;
    } catch (...) {
        cout << "Caught something" << endl;
    }
    // Note: integer division by zero is UB in C++, not always caught!
    // Floating-point division by zero gives infinity (not an exception)
    cout << 1.0 / 0.0 << endl;   // inf

    // Throw and catch an int (can throw anything)
    try {
        throw 42;
    } catch (int e) {
        cout << "Caught int: " << e << endl;
    }

    // Throw a string
    try {
        throw string("something went wrong");
    } catch (const string& e) {
        cout << "Caught string: " << e << endl;
    }

    // ── Standard exceptions ───────────────────
    try {
        throw runtime_error("Runtime error occurred");
    } catch (const runtime_error& e) {
        cout << "runtime_error: " << e.what() << endl;
    }

    try {
        vector<int> v = {1, 2, 3};
        cout << v.at(10) << endl;   // throws std::out_of_range
    } catch (const out_of_range& e) {
        cout << "out_of_range: " << e.what() << endl;
    }

    // ── Catch hierarchy ───────────────────────
    // Derived exceptions first, base exceptions last
    try {
        throw out_of_range("Index too large");
    } catch (const out_of_range& e) {    // more specific — catch first
        cout << "out_of_range: " << e.what() << endl;
    } catch (const runtime_error& e) {   // more general
        cout << "runtime_error: " << e.what() << endl;
    } catch (const exception& e) {       // catch-all for std exceptions
        cout << "exception: " << e.what() << endl;
    } catch (...) {                       // catch absolutely everything
        cout << "Unknown exception" << endl;
    }

    // ── Custom exception ──────────────────────
    try {
        withdraw(100.0, 150.0);
    } catch (const InsufficientFundsException& e) {
        cout << e.what() << endl;
        cout << "Tried: " << e.amount() << ", Had: " << e.balance() << endl;
    }

    try {
        withdraw(100.0, -50.0);
    } catch (const ValidationException& e) {
        cout << "Validation: " << e.what() << endl;
    } catch (const InsufficientFundsException& e) {
        cout << "Funds: " << e.what() << endl;
    }

    // ── Re-throw ──────────────────────────────
    auto risky = []() {
        try {
            throw runtime_error("Original error");
        } catch (const runtime_error& e) {
            cout << "Logging: " << e.what() << endl;
            throw;   // re-throws the same exception
        }
    };

    try {
        risky();
    } catch (const runtime_error& e) {
        cout << "Re-caught: " << e.what() << endl;
    }

    // ── noexcept ──────────────────────────────
    // Marks a function as not throwing — optimizer hint + contract
    auto safeAdd = [](int a, int b) noexcept -> int {
        return a + b;
    };
    cout << safeAdd(3, 4) << endl;

    // ── Standard exception hierarchy ──────────
    // exception
    // ├── logic_error
    // │   ├── invalid_argument   — bad argument value
    // │   ├── domain_error       — math domain error
    // │   ├── length_error       — exceeds max size
    // │   └── out_of_range       — value out of range
    // └── runtime_error
    //     ├── range_error        — result out of range
    //     ├── overflow_error     — arithmetic overflow
    //     └── underflow_error    — arithmetic underflow
    // bad_alloc    — new failed (out of memory)
    // bad_cast     — dynamic_cast failed
    // bad_typeid   — typeid on null pointer

    // ── RAII — Resource Acquisition Is Initialization ─
    // C++ idiom: acquire resources in constructor, release in destructor
    // Ensures cleanup even if exceptions occur (no need for finally)
    class Resource {
        string name_;
    public:
        Resource(string name) : name_(name) {
            cout << "Acquired: " << name_ << endl;
        }
        ~Resource() {
            cout << "Released: " << name_ << endl;  // called on scope exit
        }
    };

    try {
        Resource r("database connection");
        throw runtime_error("Something failed");
        // r's destructor is called automatically even here!
    } catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    // Output: Acquired → Released → Caught

    return 0;
}
