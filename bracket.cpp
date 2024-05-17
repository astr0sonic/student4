#include "bracket.h"
#include "stack"

bool checkBrackets(const std::string& s) {
    std::stack<char> stack;
    for (auto i : s) {
        if ((i == '(') or i == '<' or i == '[' or i == '{' or i == ')' or i == '>' or i == ']' or i == '}') {
            if (i == '(' or i == '<' or i == '[' or i == '{') stack.push(i);
            else {
                if (stack.empty() == true) return false;
                if ((stack.top() == '(' and i == ')') or (stack.top() == '[' and i == ']') or (stack.top() == '{' and i == '}') or (stack.top() == '<' and i == '>')) {
                    stack.pop();
                }
                else return false;
            }
        }
    }
    if (stack.empty() == false) return false;
    return true;
}