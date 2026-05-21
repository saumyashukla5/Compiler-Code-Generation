#include <bits/stdc++.h>
using namespace std;

vector<pair<string,string>> tokens;
int i = 0;

bool check(string val) {
    return i < tokens.size() && tokens[i].first == val;
}

void match(string val) {
    if (check(val)) i++;
}


void parseDeclaration() {
    cout << "    |-- DECLARATION\n";
    match("int");

    while (!check(";") && i < tokens.size()) {

        if (tokens[i].second == "IDENTIFIER") {
            cout << "        |-- VAR: " << tokens[i].first << "\n";
            i++;

            if (check("=")) {
                match("=");
                cout << "           |-- INIT VALUE\n";

                while (!check(",") && !check(";")) {
                    cout << "              |-- " << tokens[i].first << "\n";
                    i++;
                }
            }
        }

        if (check(",")) match(",");
    }

    match(";");
}

void parseAssignment() {
    cout << "    |-- ASSIGNMENT\n";

    cout << "        |-- LHS: " << tokens[i].first << "\n";
    i++;

    match("=");

    cout << "        |-- RHS EXPRESSION\n";

    while (!check(";")) {
        cout << "            |-- " << tokens[i].first << "\n";
        i++;
    }

    match(";");
}

void parseWhile() {
    cout << "    |-- WHILE LOOP\n";
    match("while");

    cout << "        |-- CONDITION\n";

    while (!check(")")) {
        cout << "            |-- " << tokens[i].first << "\n";
        i++;
    }
    match(")");

    match("{");

    cout << "        |-- BODY\n";

    while (!check("}")) {
        if (tokens[i].second == "IDENTIFIER" && tokens[i+1].first == "=")
            parseAssignment();
        else
            i++;
    }

    match("}");
}


void parseIf() {
    cout << "    |-- IF STATEMENT\n";
    match("if");

    cout << "        |-- CONDITION\n";

    while (!check(")")) {
        cout << "            |-- " << tokens[i].first << "\n";
        i++;
    }
    match(")");

    cout << "        |-- THEN BLOCK\n";

    while (!check("else"))
        i++;

    match("else");

    cout << "        |-- ELSE BLOCK\n";
}

void parseMain() {
    cout << "  |-- FUNCTION: main\n";

    match("int");
    match("main");
    match("(");
    match(")");
    match("{");

    cout << "    |-- BODY\n";

    while (!check("}")) {

        if (check("int"))
            parseDeclaration();

        else if (check("while"))
            parseWhile();

        else if (check("if"))
            parseIf();

        else if (tokens[i].second == "IDENTIFIER" && tokens[i+1].first == "=")
            parseAssignment();

        else
            i++;
    }

    match("}");
}


int main() {
    ifstream in("tokens.txt");

    string token, colon, type;

    while (in >> token >> colon >> type) {
        tokens.push_back({token, type});
    }

    cout << "\n--- SYNTAX ANALYSIS  ---\n";
    cout << "PROGRAM\n";

    while (i < tokens.size()) {
        if (check("int") && tokens[i+1].first == "main") {
            parseMain();
        } else {
            i++;
        }
    }

    return 0;
}