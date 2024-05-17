#include "rpn.h"
#include "stack"

double calculateRPN(const std::string& expr) {//7 8 9 / 1 - * 2 3 4 5 * + * 6 / + 1 2 + 3 4 - * -
    std::stack<double> val_stack;
    double res;
    for (auto i : expr) {
        if (i != ' ') {
            if (isdigit(i)) {
                if (i == '1') val_stack.push(1.0);
                if (i == '2') val_stack.push(2.0);
                if (i == '3') val_stack.push(3.0);
                if (i == '4') val_stack.push(4.0);
                if (i == '5') val_stack.push(5.0);
                if (i == '6') val_stack.push(6.0);
                if (i == '7') val_stack.push(7.0);
                if (i == '8') val_stack.push(8.0);
                if (i == '9') val_stack.push(9.0);
            }
            else {
                double n2 = val_stack.top();
                val_stack.pop();
                double n1 = val_stack.top();
                val_stack.pop();
                switch (i) {
                case '+': res = n1 + n2; break;
                case '-': res = n1 - n2; break;
                case '*': res = n1 * n2; break;
                case '/': res = n1 / n2; break;
                default: break;
                }
                val_stack.push(res);
            }
        }
    }
    res = val_stack.top();
    val_stack.pop();
    return res;
}