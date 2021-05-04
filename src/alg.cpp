// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include <stack>
std::string infx2pstfx(std::string inf) {
    std::map<char, int> priorities;
    priorities = { {'(', 0}, {')', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3} };
    std::string resString, temp;
    std::stack<char> stack;
    for (auto& current : inf) {
        if (current >= '0' && current <= '9') {
            temp += current;
        } else if (current == '(' || current == '+' ||
            current == '-' || current == '*' || current == '/') {
            if (temp.length()) {
                resString += temp;
                resString += ' ';
                temp = "";
            }
            if (!stack.empty()) {
                if (current == '(') {
                    stack.push(current);
                } else if (priorities[current] > priorities[stack.top()]) {
                    stack.push(current);
                } else {
                    resString += stack.top();
                    stack.pop();
                    stack.push(current);
                    resString += ' ';
                }
            } else {
                stack.push(current);
            }
        } else if (current == ')') {
            if (temp.length()) {
                resString += temp;
                resString += ' ';
                temp = "";
            }
            if (!stack.empty()) {
                while (stack.top() != '(') {
                    resString += stack.top();
                    stack.pop();
                    resString += ' ';
                }
                stack.pop();
            }
        }
    }
    if (temp.length()) {
        resString += temp;
        resString += ' ';
   }
    for (unsigned int i = stack.size(); i > 0; i--) {
        resString += stack.top();
        resString += ' ';
        stack.pop();
    }
    resString.erase(resString.end() - 1, resString.end());
    return resString;
}

int eval(std::string pst) {
    unsigned int x = 0, y = 0;
    std::stack<unsigned int> stack;
    unsigned int temp = 0;
    for (unsigned int i = 0; i < pst.length() + 1; i++) {
        if (pst[i] >= '0' && pst[i] <= '9') {
            temp *= 10;
            temp += pst[i] - '0';
        } else if (pst[i] == ' ') {
            stack.push(temp);
            temp = 0;
        } else {
            x = stack.top();
            stack.pop();
            y = stack.top();
            stack.pop();
            switch (pst[i]) {
                case ('+'):
                    stack.push(y + x);
                    break;
                case ('-'):
                    stack.push(y - x);
                    break;
                case ('*'):
                    stack.push(y * x);
                    break;
                case ('/'):
                    stack.push(y / x);
                    break;
                default:
                    break;
            }
            i++;
        }
    }
    return stack.top();
}
