#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

vector<string> str2vec(string str);

class Library {
private:
    map<string, string> reserved_map;
public:
    Library() {
        reserved_map["True"] = "(\\T (\\F T))";
        reserved_map["False"] = "(\\T (\\F F))";
        reserved_map["Test"] = "(\\L (\\M (\\N L M N)))";
    }
    bool exist(string str) {
        if(reserved_map.count(str)) {
            return true;
        }
        return false;
    }
    
    string decompose(string str) {
        if(!exist(str)) {
            return "";
        }
        return reserved_map[str];
    }
} lib;

bool decompose_reserved_words(vector<string> &vec) {
    string new_str;
    for(int i = 0; i < (int)vec.size(); i++) {
        bool cap = false;
        string str = vec[i];
        for(int j = 0; j < (int)str.size(); j++) {
            if('A' <= str[j] && str[j] <= 'Z') {
                cap = true;
                break;
            }
        }
        if(!cap) {
            new_str += str;
            if(i != (int)vec.size()-1) new_str += " ";
            continue;
        }
        if(str[0] == '\\') {
            if(!lib.exist(str.substr(1))) {
                cout << "invalid" << endl;
                cout << "capital characters are only used for reserved words" << endl;
                return false;
            }
        } else {
            if(!lib.exist(str)) {
                cout << "invalid" << endl;
                cout << "capital characters are only used for reserved words" << endl;
                return false;
            }
        }
        new_str += lib.decompose(str);
        if(i != (int)vec.size()-1) new_str += " ";
    }
    vec = str2vec(new_str);
    return true;
}

