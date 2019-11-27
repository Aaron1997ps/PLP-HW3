#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
using namespace std;

class variableStorage {
private:
    vector<tuple<string, string, string>> variables;

public:
    void setVariable(const string& variable, const string& type, const string& value);
    string getType(const string& variable);
    string getValue(const string& variable);
    void appendPost(const string& appendTo, const string& type, const string& value);
    void appendPre(const string& appendTo, const string& type, const string& value);
};

void variableStorage::setVariable(const string& variable, const string& type, const string& value){
    variables.emplace_back(variable, type, value);
};
string variableStorage::getType(const string& variable){
    for (auto & i : variables){
        if (get<0>(i) == variable){
            return get<1>(i);
        }
    }
    return "Not Found";
}
string variableStorage::getValue(const string& variable){
    for (auto & i : variables){
        if (get<0>(i) == variable){
            return get<1>(i);
        }
    }
    return "Not Found";
}
void variableStorage::appendPost(const string& appendTo, const string& type, const string& value) {
    string appendToType = getType(appendTo);
    if (appendToType != "list"){
        cout << "Tried to append " << value << " of type " << type << " to a " << appendToType << ", appendTo" << endl;
    }

    string newValue = value;
    if (type == "variable"){
        newValue = getValue(value);
    }

    string appendToValue = getValue(appendTo);
    if (appendToValue.empty()){
        setVariable(appendTo, "list", newValue);
        return;
    }
    setVariable(appendTo, "list", getValue(appendToValue)+","+newValue);
}
void variableStorage::appendPre(const string& appendTo, const string& type, const string& value) {
    string appendToType = getType(appendTo);
    if (appendToType != "list"){
        cout << "Tried to append " << value << " of type " << type << " to a " << appendToType << ", appendTo" << endl;
    }

    string newValue = value;
    if (type == "variable"){
        newValue = getValue(value);
    }

    string appendToValue = getValue(appendTo);
    if (appendToValue.empty()){
        setVariable(appendTo, "list", newValue);
        return;
    }
    setVariable(appendTo, "list", newValue+","+getValue(appendToValue));
}


int main(int argc, char** argv) {

    if (argc <= 1) {
        cout << "Error: Argument is required.\nExample: listexpression file=program1.py\n";
        return -1;
    }else if (argc > 2){
        cout << "Non-Fatal Error: Only one argument can be read\nExample: listexpression file=program1.py\n";
    }

    string input = argv[1];
    if (input.length() <= 5){
        cout << R"(Error: Must input file using formal "file=program1.py" where "program1.py" is your python file.)";
        return -2;
    }

    string inputFilepath = input.substr(5);
    cout << "Input File: " << inputFilepath << endl;
    ifstream inputFile(inputFilepath);

    string outputFilepath = inputFilepath.substr(0, inputFilepath.find('.')) + ".out";
    cout << "Output File: " << outputFilepath << endl;
    ofstream outputFile;  //Removes the file extension and replaces it with .out
    outputFile.open(outputFilepath);

    if (!inputFile.is_open()){
        cout << "Error: Input file failed to open" << endl;
        return -3;
    }

    if (!outputFile.is_open()){
        cout << "Error: Output file failed to open" << endl;
        return -4;
    }








    inputFile.close();
    outputFile.close();
    return 0;
}