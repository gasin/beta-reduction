#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool check_syntax(string str) {
    for(int i = 0; i < (int)str.size(); i++) {
        if(str[i] == '\\' && (i == (int)str.size()-1 || str[i] == ' ')) {
            cout << "invalid" << endl;
            cout << "there should be string just after '\\'" << endl;
            return false;
        }
    }
    int cnt = 0;
    for(int i = 0; i < (int)str.size(); i++) {
        if(str[i] == '(') {
            cnt++;
        } else if(str[i] == ')') {
            cnt--;
        }
        if(cnt < 0) {
            cout << "invalid" << endl;
            cout << "brackets should be closed" << endl;
            return false;
        }
    }
    if(cnt != 0) {
        cout << "invalid bracket" << endl;
        return false;
    }
    return true;
}

bool check_lambda(vector<string> vec) {
    for(int i = 0; i < (int)vec.size(); i++) {
        if(vec[i][0] != '\\') continue;
        if(i == (int)vec.size()-1 || vec[i+1] == ")") {
            cout << "invalid" << endl;
            cout << "lambda can't exist alone" << endl;
            return false;
        }
    }
    return true;
}

