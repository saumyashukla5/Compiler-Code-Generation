#include <bits/stdc++.h>
using namespace std;

bool isKeyword(string s) {
    string keywords[] = {"int","return","if","else","while","printf"};
    for (auto k : keywords)
        if (s == k) return true;
    return false;
}

bool isNumber(string s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

int main() {
    ifstream in("input.c");
    ofstream out("tokens.txt");

    string word = "";
    char ch;

    cout << "\n--- LEXICAL ANALYSIS  ---\n";

    while (in.get(ch)) {

       
        if (ch == '"') {
            string str = "\"";
            while (in.get(ch) && ch != '"') {
                str += ch;
            }
            str += "\"";

            cout << str << " : STRING\n";
            out << str << " : STRING\n";
        }

        else if (isalnum(ch)) {
            word += ch;
        }

        else {
            if (!word.empty()) {

                if (isKeyword(word)) {
                    cout << word << " : KEYWORD\n";
                    out << word << " : KEYWORD\n";
                }
                else if (isNumber(word)) {
                    cout << word << " : NUMBER\n";
                    out << word << " : NUMBER\n";
                }
                else {
                    cout << word << " : IDENTIFIER\n";
                    out << word << " : IDENTIFIER\n";
                }

                word.clear();
            }

            if (!isspace(ch)) {
                cout << ch << " : SYMBOL\n";
                out << ch << " : SYMBOL\n";
            }
        }
    }

    in.close();
    out.close();
}