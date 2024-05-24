#include "calculator.h"
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

const int OPEN_BRACKET = 0;
const int CLOSED_BRACKET = 1;
const int PLUS_OR_MINUS = 2;
const int MULT_OR_DIV = 3;
const int DEGREE = 4;
const int UNARY_MINUS = 5;

void getPostfixNotation(const std::string& expression, std::stack<std::string>* postfixNotation);
void reverseStack(std::stack<std::string> postfixNotation, std::stack<std::string>* reversePostfixNotation);
double calculatePostfixNotation(std::stack<std::string> postfixNotation);
bool isOperator(char symbol);
int getPriorityOperators(char symbol);
double getExpressionValue(double firstNumber, double secondNumber, std::string operators);

double calculate(const std::string& expr) {
    std::stack<std::string> stackPostfixNotation;
    std::stack <std::string> reverseStackPostfixNotation;

    getPostfixNotation(expr, &stackPostfixNotation);

    reverseStack(stackPostfixNotation, &reverseStackPostfixNotation);

    double result = calculatePostfixNotation(reverseStackPostfixNotation);

    return result;
}

void getPostfixNotation(const std::string& expression, std::stack<std::string>* postfixNotation)
{
    // Helper stack for storing operator's
    std::stack<char> operators;
    int index = 0, openBracketsCounter = 0;


    for (char symbol : expression) {
        if (isspace(symbol)) {
            index++;
            continue;
        }

        if (isdigit(symbol) || symbol == '.') {
            std::string digit = "";
            while (index < expression.size() && (isdigit(expression[index]) || expression[index] == '.')) {
                digit += expression[index++];
            }
            index--;
            postfixNotation->push(digit);
        }
        else if (symbol == '(') {
            operators.push(symbol);
            openBracketsCounter++;
        }
        else if (symbol == ')') {

            while (operators.top() != '(') {
                postfixNotation->push(std::string(1, operators.top()));
                operators.pop();
            }
            openBracketsCounter--;
            operators.pop();
        }
        else if (isOperator(symbol)) {
            if (symbol == '-' && (index == 0 || expression[index - 1] == '(')) {
                operators.push('~'); // Unary Minus
            }
            else {
                while (!operators.empty() && getPriorityOperators(operators.top()) >= getPriorityOperators(symbol)) {
                    postfixNotation->push(std::string(1, operators.top()));
                    operators.pop();
                }
                operators.push(symbol);
            }
        }
        else {
            throw std::logic_error("invalid");
        }
        index++;
    }

    if (openBracketsCounter > 0) {
        throw std::logic_error("invalid");
    }

    while (!operators.empty()) {
        postfixNotation->push(std::string(1, operators.top()));
        operators.pop();
    }
}

bool isOperator(char symbol)
{
    return (symbol == '+' or symbol == '-' or symbol == '*' or symbol == '/' or symbol == '^' or symbol == '~');
}

int getPriorityOperators(char symbol)
{
    int priorityOperator = -1;
    switch (symbol)
    {
    case '(':
        priorityOperator = OPEN_BRACKET;
        break;
    case ')':
        priorityOperator = CLOSED_BRACKET;
    case '+':
    case '-':
        priorityOperator = PLUS_OR_MINUS;
        break;
    case '*':
    case '/':
        priorityOperator = MULT_OR_DIV;
        break;
    case '^':
        priorityOperator = DEGREE;
        break;
    default:
        priorityOperator = UNARY_MINUS;
        break;
    }

    return priorityOperator;
}
void reverseStack(std::stack<std::string> postfixNotation, std::stack<std::string>* reversePostfixNotation)
{
    while (!postfixNotation.empty()) {
        reversePostfixNotation->push(postfixNotation.top());
        postfixNotation.pop();
    }
}

double calculatePostfixNotation(std::stack<std::string> postfixNotation)
{
    std::stack<double> stackRPN;

    while (!postfixNotation.empty()) {

        std::string symbol = postfixNotation.top();
        postfixNotation.pop();

        while (!isalnum(symbol[0]) && !isOperator(symbol[0])) {
            symbol = postfixNotation.top();
            postfixNotation.pop();
        }

        double operand = 0.0;
        if (isdigit(symbol[0])) {
            operand = std::stod(symbol);
            stackRPN.push(operand);
        }
        else if (isOperator(symbol[0])) {
            if (symbol[0] == '~') {
                double tempValue = stackRPN.top();
                stackRPN.pop();
                tempValue = -tempValue;
                stackRPN.push(tempValue);
            }
            else {
                if (stackRPN.size() < 2) {
                    throw std::logic_error("Not enough operands for operation");
                }

                double firstNumber = stackRPN.top();
                stackRPN.pop();
                double secondNumber = stackRPN.top();
                stackRPN.pop();

                double resultOperations = getExpressionValue(secondNumber, firstNumber, symbol);

                stackRPN.push(resultOperations);
            }
        }
    }

    if (stackRPN.size() != 1) {
        throw std::invalid_argument("Invalid expression: more than one value left in stack");
    }

    return stackRPN.top();
}

double getExpressionValue(double firstNumber, double secondNumber, std::string operators)
{
    double result = 0.0;
    if (operators == "+") {
        result = firstNumber + secondNumber;
    }
    else if (operators == "-") {
        result = firstNumber - secondNumber;
    }
    else if (operators == "*") {
        result = firstNumber * secondNumber;
    }
    else if (operators == "/") {
        if (secondNumber == 0.0) {
            throw std::logic_error("Division by zero");
        }
        else {
            result = firstNumber / secondNumber;
        }
    }
    else if (operators == "^") {
        result = std::pow(firstNumber, secondNumber);
    }
    return result;
}