#include "calculator.h"

bool isOperator(char ch)
return ((ch == '+') or (ch == '-') or (ch == '*') or (ch == '/') or (ch == '^') or (ch == '~'));

int get_pri(char ch) {
    int pri_operator = -1;
    switch (ch) {
    case '(':
        pri_operator = OPEN_BRACKET;
        break;
    case ')':
        pri_operator = CLOSED_BRACKET;
    case '+':
    case '-':
        pri_operator = PLUS_OR_MINUS;
        break;
    case '*':
    case '/':
        pri_operator = MULT_OR_DIV;
        break;
    case '^':
        pri_operator = DEGREE;
        break;
    default:
        pri_operator = UNARY_MINUS;
        break;
    }
    return pri_operator;
}
void get_pfn(const std::string & text, std::stack<std::string>*pfN) {
    std::stack<char> operators;
    int i = 0;
    int count_skob = 0;

    for (char ch : text) {
        if (isspace(ch)) i++;

        if (isdigit(ch) or ch == '.') {
            std::string digit = "";
            while (i < text.size() and (isdigit(text[i]) or text[i] == '.')) digit += text[i++];
            i--;
            pfN->push(digit);
        }
        else if (ch == '(') {
            operators.push(ch);
            count_skob++;
        }
        else if (ch == ')') {
            while (operators.top() != '(') {
                pfN->push(std::string(1, operators.top()));
                operators.pop();
            }
            count_skob--;
            operators.pop();
        }
        else if (isOperator(ch)) {
            if (ch == '-' and (i == 0 or text[i - 1] == '(')) operators.push('~');
            else {
                while (!operators.empty() and get_pri(operators.top()) >= get_pri(ch)) {
                    pfN->push(std::string(1, operators.top()));
                    operators.pop();
                }
                operators.push(ch);
            }
        }
        else throw std::logic_error("invalid");
        i++;
    }
    if (count_skob > 0) throw std::logic_error("invalid");
    while (!operators.empty()) {
        pfN->push(std::string(1, operators.top()));
        operators.pop();
    }
}

void rev_stack(std::stack<std::string> pfN, std::stack<std::string>*reversePostfixNotation) {
    while (!pfN.empty()) {
        reversePostfixNotation->push(pfN.top());
        pfN.pop();
    }
}

double get_val(double firstNumber, double secondNumber, std::string operators) {
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
            throw std::logic_error("/0");
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

double calc_pfn(std::stack<std::string> pfN) {
    std::stack<double> stackRPN;

    while (!pfN.empty()) {
        std::string str = pfN.top();
        pfN.pop();
        while (!isalnum(symbol[0]) and !isOperator(str[0])) {
            str = pfN.top();
            pfN.pop();
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
                if (stackRPN.size() < 2) throw std::logic_error("не хватает");
                double first = stackRPN.top();
                stackRPN.pop();
                double sec = stackRPN.top();
                stackRPN.pop();
                double res = get_val(sec, first, str);

                stackRPN.push(res);
            }
        }
    }
    if (stackRPN.size() != 1) throw std::invalid_argument("перебор");
    return stackRPN.top();
}

double calculate(const std::string & expression) {
    std::stack<std::string> stack_pfN;
    std::stack <std::string> rev_stack_pfN;

    get_pfn(expression, &stack_pfN);

    rev_stack(stack_pfN, &rev_stack_pfN);

    double result = calc_pfn(rev_stack_pfN);

    return result;
}