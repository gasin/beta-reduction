#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
using namespace std;

string add_bracket(string str) {
    while(true) {
        string nxt = "";
        bool end = true;
        for(int i = 0; i < (int)str.size(); i++) {
            if(str[i] == '\\' && str[i-1] != '(') {
                int cnt = 0;
                int en = str.size();
                for(int j = i+1; j < (int)str.size(); j++) {
                    if(str[j] == '(') {
                        cnt++;
                    } else if(str[j] == ')') {
                        cnt--;
                    }
                    if(cnt == -1) {
                        en = j;
                        break;
                    }
                }
                nxt = str.substr(0, i) + '(' + str.substr(i, en-i) + ')' + str.substr(en, str.size()-en);
                end = false;
            }
        }
        if(end) {
            break;
        }
        str = nxt;
    }
    return str;
}

vector<string> str2vec(string str) {
    vector<string> ret;
    for(int i = 0; i < (int)str.size(); i++) {
        if(str[i] == ' ') continue;
        string tmp;
        tmp.push_back(str[i]);
        
        if(str[i] == '(' || str[i] == ')') {
            ret.push_back(tmp);
            continue;
        } 
        
        while(i+1 < (int)str.size() && str[i+1] != ' ' && str[i+1] != '(' && str[i+1] != ')') {
            tmp.push_back(str[++i]);
        }
        ret.push_back(tmp);
    }
    return ret;
}

vector<int> de_bruijn(vector<string> vec) {
    
    const int undefined = -100;
    vector<int> ret((int)vec.size(), undefined);
    // lambda..-1, left_bracket..-2, right_bracket..-3
    
    for(int i = 0; i < (int)vec.size(); i++) {
        if(ret[i] != undefined) {
            continue;
        }
        string str = vec[i];
        if(str == "(") {
            ret[i] = -2;
            continue;
        }
        if(str == ")") {
            ret[i] = -3;
            continue;
        }
        if(str[0] == '\\') {
            ret[i] = -1;
            int cnt = 0;
            int dead = -1;
            stack<bool> blacket_type;
            for(int j = i+1; j < (int)vec.size(); j++) {
                string s = vec[j];
                if(s == "(") {
                    if(vec[j+1][0] == '\\') {
                        blacket_type.push(true);
                        cnt++;
                    } else {
                        blacket_type.push(false);
                    }
                    continue;
                } else if(s == ")"){
                    if(blacket_type.empty()) {
                        break;
                    }
                    if(blacket_type.top() == true) {
                        cnt--;
                    }
                    blacket_type.pop();
                    if(cnt == dead-1) {
                        dead = -1;
                    }
                    continue;
                }
                if(dead == -1 && s == str.substr(1)) {
                    ret[j] = cnt;
                    continue;
                }
                if(s == str) {
                    dead = cnt;
                }
            }
        }
    }
    map<string, int> name;
    for(int i = (int)vec.size()-1; i >= 0; i--) {
        if(ret[i] != undefined) continue;
        name[vec[i]] = (int)name.size()-1;
    }
    
    {
        int cnt = 0;
        stack<bool> blacket_type;
        for(int i = 0; i < (int)vec.size(); i++) {
            if(vec[i] == "(") {
                if(vec[i+1][0] == '\\') {
                    cnt++;
                    blacket_type.push(true);
                } else {
                    blacket_type.push(false);
                }
            }
            if(vec[i] == ")") {
                if(blacket_type.top() == true) {
                    cnt--;
                }
                blacket_type.pop();
            }
            if(ret[i] == undefined) {
                ret[i] = name[vec[i]]+cnt;
            }
        }
    }
    return ret;
}

vector<int> reduct(vector<int> pre) {
    vector<int> nxt;
    while(true) {
        bool end = true;
        nxt.clear();
        for(int i = 0; i < (int)pre.size(); i++) {
            if(pre[i] != -1) continue;
            int cnt = 0;
            int en = (int)pre.size()-1;
            for(int j = i+1; j < (int)pre.size(); j++) {
                if(pre[j] == -2) {
                    cnt++;
                } else if(pre[j] == -3){
                    cnt--;
                    if(cnt == -1) {
                        en = j;
                        break;
                    }
                }
            }
            if(en == (int)pre.size()-1) continue;
            
            vector<int> item;
            if(pre[en+1] >= 0) {
                item.push_back(pre[en+1]);
            } else if(pre[en+1] == -2) {
                cnt = 0;
                item.push_back(pre[en+1]);
                for(int j = en+2; j < (int)pre.size(); j++) {
                    if(pre[j] == -2) {
                        cnt++;
                    } else if(pre[j] == -3) {
                        cnt--;
                    }
                    item.push_back(pre[j]);
                    if(cnt == -1) break;
                }
            }
            if(item.size() == 0) continue;
            
            for(int j = 0; j < i-1; j++) {
                nxt.push_back(pre[j]);
            }
            
            stack<bool> bracket_type;
            cnt = 0;
            
            for(int j = i+1; j < en; j++) {
                if(pre[j] == -2) {
                    if(pre[j+1] == -1) {
                        bracket_type.push(true);
                        cnt++;
                    } else {
                        bracket_type.push(false);
                    }
                }
                if(pre[j] == -3) {
                    if(bracket_type.top() == true) {
                        cnt--;
                    }
                    bracket_type.pop();
                }
                if(pre[j] < 0) {
                    nxt.push_back(pre[j]);
                } else if(pre[j] < cnt) {
                    nxt.push_back(pre[j]);
                } else if(pre[j] > cnt) {
                    nxt.push_back(pre[j]-1);
                } else {
                    for(int k = 0; k < (int)item.size(); k++) {
                        if(item[k] >= 0) {
                            nxt.push_back(item[k]+cnt);
                        } else {
                            nxt.push_back(item[k]);
                        }
                    }
                }
            }
            for(int j = en+item.size()+1; j < (int)pre.size(); j++) {
                nxt.push_back(pre[j]);
            }
            end = false;
            break;
        }
        if(end) break;
        pre = nxt;
    }
    return pre;
}

string beta_reduction(string input) {
    input = add_bracket(input);
    cout << "add_bracket : " << input << endl;
    
    vector<string> formula = str2vec(input);
    cout << "str2vec : ";
    for(int i = 0; i < (int)formula.size(); i++) {
        cout << "\"" << formula[i] << "\" ";
    }
    cout << endl;
    
    vector<int> bruijn_formula = de_bruijn(formula);
    cout << "bruijn_formula : ";
    for(int i = 0; i < (int)bruijn_formula.size(); i++) {
        cout << bruijn_formula[i] << " ";
    }
    cout << endl;
    
    vector<int> reducted_formula = reduct(bruijn_formula);
    cout << "reducted_formula : ";
    for(int i = 0; i < (int)reducted_formula.size(); i++) {
        cout << reducted_formula[i] << " ";
    }
    cout << endl;
    
    return "";
}
