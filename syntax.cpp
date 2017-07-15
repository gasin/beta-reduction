#include <iostream>
#include <string>
using namespace std;

bool check_syntax(string str) {
    for(int i = 0; i < (int)str.size(); i++) {
        if(str[i] == '\\' && (i == (int)str.size()-1 || str[i] == ' ')) {
            cout << "invalid lambda" << endl;
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
            cout << "invalid bracket" << endl;
            return false;
        }
    }
    if(cnt != 0) {
        cout << "invalid bracket" << endl;
        return false;
    }
    return true;
}
