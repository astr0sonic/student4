#include "calculator.h"
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

using namespace std;

// ��������� ��� �������� ���������� � �� �����������
struct Operator {
    char symbol;
    int priority;
};

// �������� ������������ ��������������� ���������
bool is_valid_expression(const string& expression) {
    // �������� ������� ������������ ��������
    for (char c : expression) {
        if (!isdigit(c) && !ispunct(c) && !isspace(c) && c != ',') {
            return false;
        }
    }

    // �������� ������� ������
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

// �������������� ��������� � �������� �������� ������� (RPN)
string infix_to_rpn(const string& expression) {
    stack<Operator> operators;
    stringstream rpn;

    // ����������� ����������� ����������
    map<char, int> operator_priorities = {
        {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}
    };

    for (char c : expression) {
        // ���������� �������
        if (isspace(c)) {
            continue;
        }

        // ���� ������ - ����� ��� �����, ��������� ��� � RPN
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
            operators.pop(); // ������� '('
        }
        else { // ���� ������ - ��������
            // ��������� � RPN ���������� ��������� � ����������� �� ������
            while (!operators.empty() && operator_priorities[c] <= operators.top().priority) {
                rpn << " " << operators.top().symbol;
                operators.pop();
            }
            operators.push({ c, operator_priorities[c] });
            rpn << " ";
        }
    }

    // ��������� � RPN ���������� ���������
    while (!operators.empty()) {
        rpn << " " << operators.top().symbol;
        operators.pop();
    }

    return rpn.str();
}

// ���������� ��������� � RPN
double calculate_rpn(const string& rpn) {
    stack<double> operands;

    stringstream ss(rpn);
    string token;
    while (getline(ss, token, ' ')) {
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            // ��������� ��� �������� �� �����
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();

            // ��������� ��������
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
                    throw runtime_error("������� �� ����!");
                }
                operands.push(operand1 / operand2);
            }
            else if (token == "^") {
                operands.push(pow(operand1, operand2));
            }
        }
        else {
            // �������������� ������ � �����
            double operand = stod(token);
            operands.push(operand);
        }
    }

    // ��������� ����������
    return operands.top();
}

// ������� calculate ��� ���������� ���������
double calculate(const string& expr) {
    if (!is_valid_expression(expr)) {
        throw runtime_error("������������ ���������!");
    }

    string rpn = infix_to_rpn(expr);
    return calculate_rpn(rpn);
}