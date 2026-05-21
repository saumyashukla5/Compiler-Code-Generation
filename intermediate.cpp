#include <bits/stdc++.h>
using namespace std;

struct Quad {
    string op, arg1, arg2, result;
};

vector<Quad> quads;

void addQuad(string op, string a1, string a2, string res) {
    quads.push_back({op, a1, a2, res});
}

int main() {

    vector<string> tac = {
        "t1 = num % 10",
        "digit = t1",
        "t2 = rev * 10",
        "t3 = t2 + digit",
        "rev = t3",
        "t4 = num / 10",
        "num = t4",
        "t5 = temp == rev",
        "if t5 == 0 goto L3"
    };

    for (auto &line : tac) {

        if (line.find("=") != string::npos && line.find("if") == string::npos) {

            string lhs, eq, a, op, b;
            stringstream ss(line);
            ss >> lhs >> eq >> a;

            if (ss >> op) {
                ss >> b;
                addQuad(op, a, b, lhs);
            } else {
                addQuad("=", a, "-", lhs);
            }
        }

        else if (line.find("if") != string::npos) {
            string temp, eq, val, go, label;
            stringstream ss(line);
            ss >> temp >> val >> eq >> val >> go >> label;
            addQuad("if==0", temp, "-", label);
        }
    }

    cout << "\n--- QUADRUPLE (LOGIC GENERATED) ---\n\n";

    cout << left << setw(10) << "OP"
         << setw(12) << "ARG1"
         << setw(12) << "ARG2"
         << setw(12) << "RESULT" << "\n";

    cout << "---------------------------------------------\n";

    for (auto &q : quads) {
        cout << left << setw(10) << q.op
             << setw(12) << q.arg1
             << setw(12) << q.arg2
             << setw(12) << q.result << "\n";
    }

    return 0;
}