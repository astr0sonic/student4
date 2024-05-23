#include "calculator.h"
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

using namespace std;

// Структура для хранения операторов и их приоритетов
struct Operator {
    char symbol;
    int priority;
};

// Проверка корректности арифметического выражения
bool is_valid_expression(const string& expression) {
    // Проверка наличия недопустимых символов
    for (char c : expression) {
        if (!isdigit(c) && !ispunct(c) && !isspace(c) && c != ',') {
            return false;
        }
    }

    // Проверка баланса скобок
    int balance = 0;
    for (char c : expression) {
        if (c == '(') {
            balance++;
        }
        else if (c == ')') {
            balance--;
            if (balance < 0) {
                return false;
            }
        }
    }

    return balance == 0;
}

// Преобразование выражения в обратную польскую нотацию (RPN)
string infix_to_rpn(const string& expression) {
    stack<Operator> operators;
    stringstream rpn;

    // Определение приоритетов операторов
    map<char, int> operator_priorities = {
        {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}
    };

    for (char c : expression) {
        // Пропускаем пробелы
        if (isspace(c)) {
            continue;
        }

        // Если символ - цифра или точка, добавляем его в RPN
        if (isdigit(c) || c == '.') {
            rpn << c;
        }
        else if (c == '(') {
            operators.push({ c, 0 });
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top().symbol != '(') {
                rpn << " " << operators.top().symbol;
                operators.pop();
            }
            operators.pop(); // Удаляем '('
        }
        else { // Если символ - оператор
            // Добавляем в RPN предыдущие операторы с приоритетом не меньше
            while (!operators.empty() && operator_priorities[c] <= operators.top().priority) {
                rpn << " " << operators.top().symbol;
                operators.pop();
            }
            operators.push({ c, operator_priorities[c] });
            rpn << " ";
        }
    }

    // Добавляем в RPN оставшиеся операторы
    while (!operators.empty()) {
        rpn << " " << operators.top().symbol;
        operators.pop();
    }

    return rpn.str();
}

// Вычисление выражения в RPN
double calculate_rpn(const string& rpn) {
    stack<double> operands;

    stringstream ss(rpn);
    string token;
    while (getline(ss, token, ' ')) {
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            // Извлекаем два операнда из стека
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();

            // Выполняем операцию
            if (token == "+") {
                operands.push(operand1 + operand2);
            }
            else if (token == "-") {
                operands.push(operand1 - operand2);
            }
            else if (token == "*") {
                operands.push(operand1 * operand2);
            }
            else if (token == "/") {
                if (operand2 == 0) {
                    throw runtime_error("Деление на ноль!");
                }
                operands.push(operand1 / operand2);
            }
            else if (token == "^") {
                operands.push(pow(operand1, operand2));
            }
        }
        else {
            // Преобразование токена в число
            double operand = stod(token);
            operands.push(operand);
        }
    }

    // Результат вычисления
    return operands.top();
}

// Функция calculate для вычисления выражения
double calculate(const string& expr) {
    if (!is_valid_expression(expr)) {
        throw runtime_error("Некорректное выражение!");
    }

    string rpn = infix_to_rpn(expr);
    return calculate_rpn(rpn);
}