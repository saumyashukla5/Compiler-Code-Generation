#include <bits/stdc++.h>
using namespace std;

struct Quad {
    string op, arg1, arg2, result;
};

vector<Quad> tac;

void generateCode() {

    for (auto &q : tac) {

        if (q.op == "=") {
            cout << "MOV " << q.result << ", " << q.arg1 << "\n";
        }

        else if (q.op == "%") {
            cout << "MOV R1, " << q.arg1 << "\n";
            cout << "MOD R1, " << q.arg2 << "\n";
            cout << "MOV " << q.result << ", R1\n";
        }

        else if (q.op == "*") {
            cout << "MOV R1, " << q.arg1 << "\n";
            cout << "MUL R1, " << q.arg2 << "\n";
            cout << "MOV " << q.result << ", R1\n";
        }

        else if (q.op == "+") {
            cout << "MOV R1, " << q.arg1 << "\n";
            cout << "ADD R1, " << q.arg2 << "\n";
            cout << "MOV " << q.result << ", R1\n";
        }

        else if (q.op == "/") {
            cout << "MOV R1, " << q.arg1 << "\n";
            cout << "DIV R1, " << q.arg2 << "\n";
            cout << "MOV " << q.result << ", R1\n";
        }

        else if (q.op == "LABEL") {
            cout << q.arg1 << ":\n";
        }

        else if (q.op == "if==") {
            cout << "CMP " << q.arg1 << ", " << q.arg2 << "\n";
            cout << "JE " << q.result << "\n";
        }

        else if (q.op == "goto") {
            cout << "JMP " << q.arg1 << "\n";
        }

        else if (q.op == "==") {
            cout << "CMP " << q.arg1 << ", " << q.arg2 << "\n";
        }

        else if (q.op == "if==0") {
            cout << "JNE " << q.result << "\n";
        }

        else if (q.op == "call") {
            cout << "CALL " << q.arg1 << ", " << q.arg2 << "\n";
        }

        else if (q.op == "return") {
            cout << "RET\n";
        }
    }
}

int main() {

    tac = {

        {"=", "121", "-", "num"},
        {"=", "0", "-", "rev"},
        {"=", "num", "-", "temp"},

        {"LABEL", "L1", "-", "-"},
        {"if==", "num", "0", "L2"},

        {"%", "num", "10", "t1"},
        {"=", "t1", "-", "digit"},

        {"*", "rev", "10", "t2"},
        {"+", "t2", "digit", "t3"},
        {"=", "t3", "-", "rev"},

        {"/", "num", "10", "t4"},
        {"=", "t4", "-", "num"},

        {"goto", "L1", "-", "-"},

        {"LABEL", "L2", "-", "-"},
        {"==", "temp", "rev", "t5"},
        {"if==0", "t5", "-", "L3"},

        {"call", "printf", "\"Palindrome\\n\"", "-"},
        {"goto", "L4", "-", "-"},

        {"LABEL", "L3", "-", "-"},
        {"call", "printf", "\"Not Palindrome\\n\"", "-"},

        {"LABEL", "L4", "-", "-"},
        {"return", "0", "-", "-"}
    };

    cout << "\n--- CODE GENERATION (LOGIC BASED) ---\n\n";
    generateCode();

    return 0;
}