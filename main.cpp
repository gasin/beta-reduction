#include <iostream>
#include <string>
using namespace std;

string beta_reduction(string formula);

int main() {
    cout << "type 'q' to exit" << endl;
    while(true) {
        cout << ">";
        string input;
        getline(cin, input);
        
        if(input == "q") {
            break;
        }
        
        string output = beta_reduction(input);
        //cout << output << endl;
    }
}
