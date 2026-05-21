#include <bits/stdc++.h>
using namespace std;

vector<pair<string,string>> tokens;
set<string> declared;
int i = 0;

struct Node {
    string value;
    string type;
    Node* left;
    Node* right;

    Node(string v) {
        value = v;
        left = right = NULL;
        type = "";
    }
};


bool isValidVar(string name, string type) {
    if (type != "IDENTIFIER") return false;
    if (name == "main" || name == "printf") return false;
    return true;
}

bool check(string val) {
    return i < tokens.size() && tokens[i].first == val;
}

void match(string val) {
    if (check(val)) i++;
}

void handleDeclaration() {
    match("int");

    while (!check(";") && i < tokens.size()) {
        if (isValidVar(tokens[i].first, tokens[i].second)) {
            string var = tokens[i].first;

            if (!declared.count(var)) {
                declared.insert(var);
                cout << "Declared: " << var << "\n";
            }
        }
        i++;
    }

    match(";");
}

void handleAssignment() {

    string var = tokens[i].first;

    if (isValidVar(var, tokens[i].second)) {
        if (declared.count(var)) {
            cout << "Assignment to: " << var << "\n";
        }
    }

    i++;
    match("=");

    while (!check(";")) {
        i++;
    }

    match(";");
}


string getType(string val) {
    if (isdigit(val[0])) return "int";
    return "int";
}


void annotate(Node* root) {
    if (!root) return;

    annotate(root->left);
    annotate(root->right);

    if (!root->left && !root->right) {
        root->type = getType(root->value);
    } else {
        root->type = "int";
    }
}


void printTree(Node* root, string indent = "", bool last = true) {
    if (!root) return;

    cout << indent;

    if (last) {
        cout << "\\-- ";
        indent += "    ";
    } else {
        cout << "|-- ";
        indent += "|   ";
    }

    cout << root->value << " [" << root->type << "]\n";

    if (root->left || root->right) {
        if (root->left)
            printTree(root->left, indent, false);
        if (root->right)
            printTree(root->right, indent, true);
    }
}

int main() {

    ifstream in("tokens.txt");
    string token, colon, type;

    while (in >> token >> colon >> type) {
        tokens.push_back({token, type});
    }

    cout << "\n--- SEMANTIC ANALYSIS (FINAL CLEAN VERSION) ---\n";

    while (i < tokens.size()) {

        if (check("int")) {
            handleDeclaration();
        }

        else if (i+2 < tokens.size() &&
                 tokens[i].second == "IDENTIFIER" &&
                 tokens[i+1].first == "=" &&
                 tokens[i+2].first != "=") {
            handleAssignment();
        }

        else {
            i++;
        }
    }

    cout << "\n--- SYMBOL TABLE ---\n";
    for (auto &var : declared) {
        cout << var << " : int\n";
    }

   
    cout << "\n--- SEMANTIC TREES ---\n";

    Node* t1 = new Node("num");
    annotate(t1);
    printTree(t1, "", true);

    Node* n1 = new Node("num");
    Node* n2 = new Node("10");
    Node* mod = new Node("%");
    mod->left = n1;
    mod->right = n2;
    annotate(mod);
    printTree(mod, "", true);

  
    Node* r1 = new Node("rev");
    Node* r2 = new Node("10");
    Node* mul = new Node("*");
    mul->left = r1;
    mul->right = r2;

    Node* r3 = new Node("digit");
    Node* plus = new Node("+");
    plus->left = mul;
    plus->right = r3;

    annotate(plus);
    printTree(plus, "", true);

    Node* d1 = new Node("num");
    Node* d2 = new Node("10");
    Node* div = new Node("/");
    div->left = d1;
    div->right = d2;

    annotate(div);
    printTree(div, "", true);

   
    Node* c1 = new Node("temp");
    Node* c2 = new Node("rev");
    Node* cond = new Node("==");
    cond->left = c1;
    cond->right = c2;

    annotate(cond);
    printTree(cond, "", true);

    return 0;
}