#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> beta_reduction(string formula);
bool check_syntax(string input);

int main() {
    cout << "type 'q' to exit" << endl;
    while(true) {
        cout << ">";
        string input;
        getline(cin, input);
        
        if(input == "q") {
            break;
        }
        
        if(check_syntax(input) == false) {
            continue;
        }
        
        vector<string> output = beta_reduction(input);
        for(int i = 0; i < (int)output.size(); i++) {
            cout << " -> " << output[i] << endl;
        }
    }
}
