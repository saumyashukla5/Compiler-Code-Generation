#include <bits/stdc++.h>
using namespace std;

struct Instr {
    string lhs, op, arg1, arg2;
};

bool isTemp(string s) {
    return s.size() > 1 && s[0] == 't';
}

int main() {

    vector<string> code = {
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

    map<string,string> val;
    vector<string> optimized;

    for (auto &line : code) {

        string lhs, eq, a, op, b;

        stringstream ss(line);
        ss >> lhs >> eq >> a;

        if (!(ss >> op)) {
            if (val.count(a)) a = val[a];
            if (isTemp(lhs)) val[lhs] = a;
            else optimized.push_back(lhs + " = " + a);
        }
        else {
            ss >> b;

            if (val.count(a)) a = val[a];
            if (val.count(b)) b = val[b];

            string expr = a + " " + op + " " + b;

            if (isTemp(lhs)) {
                val[lhs] = expr;
            } else {
                optimized.push_back(lhs + " = " + expr);
            }
        }
    }

    cout << "\n--- OPTIMIZED (LOGIC BASED) ---\n\n";

    for (int i = 0; i < optimized.size(); i++) {
        cout << i+1 << ". " << optimized[i] << "\n";
    }

    return 0;
}