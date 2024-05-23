#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

bool isOperator(char ch)
{
    return (ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '^' or ch == '~');
}

int get_pri(char ch)
{
    int priorityOperator = -1;
    switch (ch)
    {
    case '(':
        priorityOperator = 0;
        break;
    case ')':
        priorityOperator = 1;
    case '+':
    case '-':
        priorityOperator = 2;
        break;
    case '*':
    case '/':
        priorityOperator = 3;
        break;
    case '^':
        priorityOperator = 4;
        break;
    default:
        priorityOperator = 5;
        break;
    }
    return priorityOperator;
}

double get_val(double f, double s, std::string operators){
    double c = 0.0;
    if (operators == "+") return (f + s);
    if (operators == "-") return (f - s);
    if (operators == "*") return (f * s);
    else if (operators == "/") {
        if (s == 0.0) {
            throw std::logic_error("/0");
        }
        else return (f / s);
    }
    if (operators == "^") return std::pow(f, s);
}

void reverseStack(std::stack<std::string> postfixNotation, std::stack<std::string>* reversePostfixNotation)
{
    while (!postfixNotation.empty()) {
        reversePostfixNotation->push(postfixNotation.top());
        postfixNotation.pop();
    }
}

double calc_pfn(std::stack<std::string> postfixNotation)
{
    std::stack<double> stackRPN;

    while (!postfixNotation.empty()) {
        std::string str = postfixNotation.top();
        postfixNotation.pop();
        while (!isalnum(str[0]) && !isOperator(str[0])) {
            str = postfixNotation.top();
            postfixNotation.pop();
        }
        double operand = 0.0;
        if (isdigit(str[0])) {
            operand = std::stod(str);
            stackRPN.push(operand);
        }
        else if (isOperator(str[0])) {
            if (str[0] == '~') {
                double tempValue = stackRPN.top();
                stackRPN.pop();
                tempValue = -tempValue;
                stackRPN.push(tempValue);
            }
            else {
                if (stackRPN.size() < 2) {
                    throw std::logic_error("Not enough");
                }

                double firstNumber = stackRPN.top();
                stackRPN.pop();
                double secondNumber = stackRPN.top();
                stackRPN.pop();
                double resultOperations = get_val(secondNumber, firstNumber, str);
                stackRPN.push(resultOperations);
            }
        }
    }
    if (stackRPN.size() != 1) {
        throw std::invalid_argument("too mach in the stack");
    }
    return stackRPN.top();
}

void get_post(const std::string& expression, std::stack<std::string>* postfixNotation){
    std::stack<char> operators;
    int i = 0;
    int skob = 0;
    for (char ch : expression) {
        if (isspace(ch)) i++;
        if (isdigit(ch) or ch == '.') {
            std::string digit = "";
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                digit += expression[i++];
            }
            i--;
            postfixNotation->push(digit);
        }
        else if (ch == '(') {
            operators.push(ch);
            skob++;
        }
        else if (ch == ')') {

            while (operators.top() != '(') {
                postfixNotation->push(std::string(1, operators.top()));
                operators.pop();
            }
            skob--;
            operators.pop();
        }
        else if (isOperator(ch)) {
            if (ch == '-' and (i == 0 or expression[i - 1] == '(')) operators.push('~'); // Unary Minus
            else {
                while (!operators.empty() && get_pri(operators.top()) >= get_pri(ch)) {
                    postfixNotation->push(std::string(1, operators.top()));
                    operators.pop();
                }
                operators.push(ch);
            }
        }
        else {
            throw std::logic_error("invalid");
        }
        i++;
    }
    if (skob > 0) {
        throw std::logic_error("invalid");
    }
    while (!operators.empty()) {
        postfixNotation->push(std::string(1, operators.top()));
        operators.pop();
    }
}

double calculate(const std::string& expr) {
    std::stack<std::string> stack;
    std::stack <std::string> revers;
    get_post(expr, &stack);
    reverseStack(stack, &revers);
    return calc_pfn(revers);
}