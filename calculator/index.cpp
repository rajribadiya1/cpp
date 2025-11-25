#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

class Calculator {
private:
    double num1, num2, result;
    char operation;

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool getNumbers() {
        cout << "Enter first number: ";
        if (!(cin >> num1)) {
            cout << "Invalid input!" << endl;
            clearInput();
            return false;
        }

        cout << "Enter second number: ";
        if (!(cin >> num2)) {
            cout << "Invalid input!" << endl;
            clearInput();
            return false;
        }

        return true;
    }

    void displayResult() {
        cout << fixed << setprecision(2);
        cout << "\nResult: " << num1 << " " << operation << " " 
             << num2 << " = " << result << endl;
    }

public:
    void run() {
        char continueCalc;

        do {
            cout << "\n=================================\n";
            cout << "         CALCULATOR MENU         \n";
            cout << "=================================\n";
            cout << "1. Addition (+)\n";
            cout << "2. Subtraction (-)\n";
            cout << "3. Multiplication (*)\n";
            cout << "4. Division (/)\n";
            cout << "5. Modulus (%)\n";
            cout << "6. Power (^)\n";
            cout << "7. Square Root (√)\n";
            cout << "8. Exit\n";
            cout << "=================================\n";
            cout << "Enter your choice (1-8): ";

            int choice;
            if (!(cin >> choice)) {
                cout << "Invalid input!" << endl;
                clearInput();
                continue;
            }

            if (choice == 8) {
                cout << "\nThank you for using the calculator!\n";
                break;
            }

            if (choice == 7) {
                // Square root only needs one number
                cout << "Enter a number: ";
                if (!(cin >> num1)) {
                    cout << "Invalid input!" << endl;
                    clearInput();
                    continue;
                }

                if (num1 < 0) {
                    cout << "Error: Cannot calculate square root of negative number!" << endl;
                } else {
                    result = sqrt(num1);
                    cout << fixed << setprecision(2);
                    cout << "\nResult: √" << num1 << " = " << result << endl;
                }
            } else {
                if (!getNumbers()) continue;

                switch (choice) {
                    case 1:
                        operation = '+';
                        result = num1 + num2;
                        displayResult();
                        break;

                    case 2:
                        operation = '-';
                        result = num1 - num2;
                        displayResult();
                        break;

                    case 3:
                        operation = '*';
                        result = num1 * num2;
                        displayResult();
                        break;

                    case 4:
                        operation = '/';
                        if (num2 == 0) {
                            cout << "Error: Division by zero!" << endl;
                        } else {
                            result = num1 / num2;
                            displayResult();
                        }
                        break;

                    case 5:
                        operation = '%';
                        if (num2 == 0) {
                            cout << "Error: Modulus by zero!" << endl;
                        } else {
                            result = fmod(num1, num2);
                            displayResult();
                        }
                        break;

                    case 6:
                        operation = '^';
                        result = pow(num1, num2);
                        displayResult();
                        break;

                    default:
                        cout << "Invalid choice! Please select 1-8." << endl;
                }
            }

            cout << "\nDo you want to perform another calculation? (y/n): ";
            cin >> continueCalc;

        } while (continueCalc == 'y' || continueCalc == 'Y');

        cout << "\nGoodbye!\n";
    }
};

int main() {
    Calculator calc;
    calc.run();
    return 0;
}
