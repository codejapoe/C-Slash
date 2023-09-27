#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <cctype>
#include <stdexcept>

using namespace std;

struct Variable {
    string name;
    string value;
    string type;
    struct Variable *address;
};

string find(Variable* node, string var_name) {
    while (node != NULL) {
        if (node->name == var_name) {
            return node->value;
        }
        node = node->address;
    }
    return "null";
}

string find_type(Variable* node, string var_name) {
    while (node != NULL) {
        if (node->name == var_name) {
            return node->type;
        }
        node = node->address;
    }
    return "null";
}

void create(Variable **node, string var_name, string value, string type){
    Variable *newNode = new Variable;
    Variable *ref = *node;

    newNode->name = var_name;
    newNode->value = value;
    newNode->type = type;
    newNode->address = NULL;

    if (*node == NULL) {
        *node = newNode;
        return;
    }

    while(ref->address != NULL){
        ref = ref->address;

        if (ref->name == var_name) {
            ref->value = value;
            ref->type = type;
            return ;
        }
    }

    ref->address = newNode;
    return ;
}

string removeSpace(string text) {
    string temp_text = "";
    for (int i=0; i < text.size(); i++) {
        if (int(text[i]) != 32) {
            temp_text += text[i];
        }
    }
    return temp_text;
}

vector<string> splitString(const string& input, char delimiter) {
    vector<string> tokens;
    istringstream tokenStream(input);
    string token;

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

string trimString(const string& input) {
    size_t firstNonSpace = input.find_first_not_of(' ');
    if (firstNonSpace == string::npos) {
        return "";
    }

    size_t lastNonSpace = input.find_last_not_of(' ');
    return input.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
}

bool isInteger(const string& input) {
    istringstream iss(input);
    int intValue;
    char remaining;

    if (iss >> intValue && !(iss >> remaining)) {
        return true;
    }

    return false;
}

double evaluateExpression(const string& expression) {
    istringstream input(expression);

    double result;
    if (!(input >> result)) {
        throw runtime_error("Invalid expression");
    }

    char op;
    while (input >> op) {
        double operand;
        if (!(input >> operand)) {
            throw runtime_error("Invalid expression");
        }

        switch (op) {
            case '+':
                result += operand;
                break;
            case '-':
                result -= operand;
                break;
            case '*':
                result *= operand;
                break;
            case '/':
                if (operand == 0) {
                    throw runtime_error("Division by zero");
                }
                result /= operand;
                break;
            default:
                throw runtime_error("Invalid operator");
        }
    }

    return result;
}

void interpret(string code, Variable **node) {
    if (int(code[0]) == 47) {
        return ;
    } else if (code.substr(0, 7) == "output(") {
        int i = 8;
        Variable *ref = *node;

        while (int(code[i]) != 34) {
            if (int(code[i]) == 92) {
                cout << code[i+1];
                i += 2;
                continue;
            }
            if (int(code[i]) == 36) {
                string var_name = "";
                int j = 0;
                
                for (j = i + 2; int(code[j]) != 125; j++) {
                    var_name += code[j];
                }
                
                if (var_name.find("+") != string::npos || var_name.find("-") != string::npos || var_name.find("*") != string::npos || var_name.find("/") != string::npos) {
                    var_name = removeSpace(var_name);
                    string tmp_str;
                    int k = 0;

                    while (k < var_name.size()) {
                        string temp_var = "";

                        while (int(var_name[k]) != 43 && int(var_name[k]) != 45 && int(var_name[k]) != 42 && int(var_name[k]) != 47 && k < var_name.size()) {
                            temp_var += var_name[k];
                            k += 1;
                        }

                        if (isInteger(temp_var)) {
                            tmp_str += temp_var;
                        } else {
                            tmp_str += find(ref, temp_var);
                        }

                        tmp_str += var_name[k];
                        k += 1;
                    }

                    try {
                        string temp;

                        for (char c: tmp_str) {
                            if (c != '\x00') {
                                temp += c;
                            }
                        }

                        double result = evaluateExpression(temp);
                        string var_value = to_string(result);
                        size_t dotPosition = var_value.find('.');
                        
                        if (dotPosition != string::npos) {
                            var_value.erase(var_value.find_last_not_of('0') + 1);
                            if (var_value.back() == '.') {
                                var_value.pop_back();
                            }
                        }

                        cout << var_value;
                    } catch (const exception& e) {
                        cout << "undefined";
                    }
                } else if (var_name.find("type(") != string::npos) {
                    string var_name2 = "";
                    int k = 5;
                    
                    while (int(var_name[k]) != 41) {
                        var_name2 += var_name[k];
                        k++;
                    }
                    cout << find_type(ref, var_name2);
                } else {
                    cout << find(ref, var_name);
                }
                
                i = j + 1;
                continue;
            }
            cout << code[i];
            i += 1;
        }
        cout << endl;
    } else if (code.substr(0, 6) == "input(") {
        Variable *ref = *node;
        string var_name = "";
        string var_value;
        string var_type = "";
        int i = 6;
        int j = 0;

        while (int(code[i]) != 44) {
            var_name += code[i];
            i += 1;
        }
        
        i += 1;
        while (int(code[i]) != 41) {
            if (int(code[i]) != 32) {
                var_type += code[i];
            }
            i += 1;
        }

        if (var_type == "int") {
            getline(cin, var_value);
            create(&ref, var_name, var_value, var_type);
        } else if (var_type == "float") {
            getline(cin, var_value);
            create(&ref, var_name, var_value, var_type);
        } else if (var_type == "str") {
            getline(cin, var_value);
            create(&ref, var_name, var_value, var_type);
        } else {
            cout << "Syntax Error: Please put the input type.";
            exit(EXIT_FAILURE);
        }

    } else if (code.substr(0, 4) == "var ") {
        Variable *ref = *node;
        string var_name = "";
        string var_value = "";
        string var_type = "";
        code = removeSpace(code);
        int i;

        for (i=3; !(int(code[i]) == 61); i++) {
            var_name += code[i];
        }

        var_value = code.substr(i+1);

        if (int(var_value[0]) == 34) {
            var_value = var_value.substr(1, var_value.size()-2);
            var_type = "str";
        } else if (var_value.find(".") != string::npos) {
            var_type = "float";
        } else if (var_value == "true" || var_value == "false") {
            var_type = "bool";
        } else if (isInteger(var_value)) {
            var_type = "int";
        } else if (var_value.find("+") != string::npos || var_value.find("-") != string::npos || var_value.find("*") != string::npos || var_value.find("/") != string::npos) {
            string tmp_str = "";
            code = var_value;
            i = 0;

            while (i < code.size() || int(code[i]) == 59) {
                string temp_var = "";

                while (int(code[i]) != 43 && int(code[i]) != 45 && int(code[i]) != 42 && int(code[i]) != 47 && int(code[i]) != 40 && int(code[i]) != 41 && i < code.size()) {
                    temp_var += code[i];
                    i += 1;
                }

                if (isInteger(temp_var)) {
                    tmp_str += temp_var;
                } else {
                    tmp_str += find(ref, temp_var);
                }
                tmp_str += code[i];
                i += 1;
            }
            
            try {
                string temp;

                for (char c: tmp_str) {
                    if (c != '\x00') {
                        temp += c;
                    }
                }

                double result = evaluateExpression(temp);
                var_value = to_string(result);
                size_t dotPosition = var_value.find('.');
                
                if (dotPosition != string::npos) {
                    var_value.erase(var_value.find_last_not_of('0') + 1);
                    if (var_value.back() == '.') {
                        var_value.pop_back();
                    }
                }

                if (var_value.find(".") != string::npos) {
                    var_type = "float";
                } else {
                    var_type = "int";
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
                var_value = "undefined";
                var_type = "undefined";
            }
        } else {
            string temp_var = "";
            code = var_value;
            i = 0;

            while (i < code.size() || int(code[i]) == 59) {
                temp_var += code[i];
                i += 1;
            }

            var_value = find(ref, temp_var);
            var_type = find_type(ref, temp_var);
        }

        create(&ref, var_name, var_value, var_type);
    }

    return ;
}

int main(int argc, char const *filename[]) {
    try {
        Variable *variable_list = new Variable;
        variable_list->name = "c-slash.info";
        variable_list->value = " Version: 0.1 (Beta)\nDeveloper: Codejapoe\nDeveloped on: 25/09/2023";
        variable_list->type = "str";

        if (strcmp(filename[1], "--info") == 0) {
            cout << variable_list->value.substr(1) << endl;
            exit(EXIT_SUCCESS);
        }

        ifstream file;
        file.open(filename[1]);

        if (!file.is_open()) {
            cout << "Error 404: File not found." << endl;
            exit(EXIT_FAILURE);
        } else {
            string code;

            while (getline(file, code)) {
                vector<string> tokens = splitString(code, ';');

                for (const string& token : tokens) {
                    interpret(trimString(token), &variable_list);
                }
            }

            file.close();
        }
        return 0;
    } catch (const exception& e) {
        cout << "Syntax Error: Please check your code." << endl;
        return 1;
    }
}