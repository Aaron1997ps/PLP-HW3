#include <iostream>
#include <fstream>
#include <array>
#include <string>
using namespace std;

int variableSize = 100;
int variableTotal = 0;
auto *variableType = new string[variableSize]; //Data Types
auto *variableName = new string[variableSize];

int getVariableNamePosition(const string& varName) {
    int selection = -1;
    for (int i = 0; i < variableTotal; i++) {
        if (varName == variableName[i]) {
            selection = i;
            break;
        }
    }
    return selection;
}
int updateVariableNamePosition(const string& varName) {
    int selection = getVariableNamePosition(varName);
    if (selection == -1){
        selection = variableTotal;
        variableName[selection] = varName;
        variableType[selection] = "NULL";
        variableTotal++;
    }
    return selection;
}
int countOccurrences(string *variableType, string search, int maxValue){
    int count = 0;
    for(int i = 0; i < maxValue; i++){
        if (variableType[i] == search)
            count ++;
    }
    return count;
}
string processSection(string *processingType, string *processingString, int minPos, int maxPos){
    string type = "Null";
    int totalVals = maxPos - minPos;

    if (totalVals == 1){
        if (processingType[minPos] == "VAR"){
            int temp = getVariableNamePosition(processingString[minPos]);
            if (temp == -1){
                return "ERROR";
            }
            return variableType[temp];
        }
        if (processingType[minPos] == "APPEND"){
            if (processingString[minPos].at(0) == '"')
                return "STRINGARRAY";
            else
                return "INTARRAY";
        }
        if (processingType[minPos] == "INSERT"){
            if (processingString[minPos].at(2) == '"')
                return "STRINGARRAY";
            else
                return "INTARRAY";
        }
        return processingType[minPos];
    }else {
        string returnType = "NULL";
        for (int i = minPos; i < maxPos; i++){
            if (processingType[i] == "+" || processingType[i] == "*"){
                if (processingType[i-1] == "VAR"){
                    processingType[i-1] = variableType[getVariableNamePosition(processingString[i-1])];
                }
                if (processingType[i+1] == "VAR"){
                    processingType[i+1] = variableType[getVariableNamePosition(processingString[i+1])];
                }
                if (processingType[i] == "+" && ((processingType[i-1] == "INTARRAY" && processingType[i+1] == "STRINGARRAY") || (processingType[i-1] == "STRINGARRAY" && processingType[i+1] == "INTARRAY"))){
                    return "WARNING";
                }
                if (processingType[i-1] == processingType[i+1]){
                    if (processingType[i] == "*" && processingType[i-1] == "STRING")
                        return "ERROR";
                    returnType = processingType[i-1];
                }else{
                    return "ERROR";
                }
            }else if (processingType[i] == "=" && processingType[i+1] == "="){
                if (processingType[i-1] == "VAR"){
                    processingType[i-1] = variableType[getVariableNamePosition(processingString[i-1])];
                }
                if (processingType[i+2] == "VAR"){
                    processingType[i+2] = variableType[getVariableNamePosition(processingString[i+2])];
                }
                if (processingType[i-1] == processingType[i+2]){
                    return "NULL";
                }else{
                    return "WARNING";
                }
            }
        }
        return returnType;
    }

    return type;
}
string getNumOrVar(string str){
    if (isdigit(str.at(0))) {
        return "INT";
    } else {
        return "VAR";
    }
}
int main(int argc, char** argv) {

    if (argc <= 1) {
        cout << "Error: Argument is required.\nExample: checkdatatype file=program1.py\n";
        return -1;
    }else if (argc > 2){
        cout << "Non-Fatal Error: Only one argument can be read\nExample: checkdatatype file=program1.py\n";
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

    //Needed Variables
    bool error;
    bool warning;
    string spaceCount;
    bool spaceCheck;
    int variablePos = -1;
    string scanLine, scanLineAfter, line; //scanLine is the string used to scan through the line and pull out data, After adds the char AFTER the loop (so it is -1 character)
    string tempVariableType;
    auto processingString = new string[50];
    auto processingType = new string[50]; //String, int, etc
    int pt; // Processing Total
    bool quote; //Is there a quote that trying to find the end of?
    bool parentheses, bracket;
    bool append, insert;
    int parenthesesCount;
    bool disableSLA; //Remove the Scan Line After

    //Main Loop
    while(getline(inputFile, line)){
        cout << line << endl;

        //Read and Analyze Line
        scanLine = scanLineAfter = "";
        spaceCheck = false; //These check for indents
        spaceCount = "";
        error = false;
        warning = false;
        variablePos = -1; //Variables Position in Array
        tempVariableType = "Null";
        pt = 0;
        quote = false;
        parentheses = false, bracket = false;
        insert = append = false;
        parenthesesCount = 0;

        //Character Loop
        for (char c : line) {
            disableSLA = false;

            //Handle Spaces at beginning of line
            if (c == ' ') {
                if (!spaceCheck) spaceCount += " ";
                continue;
            } else spaceCheck = true;

            //Handle Comment Lines
            if (c == '#') {
                scanLine = "";
                break;
            }

            //Ignore Colons
            if (c == ':'){
                break;
            }

            //Remove Carriage Symbol
            if (int(c) == 13) break;

            scanLine += c;

            if (quote){
                if (c == '"'){
                    quote = false;
                    processingString[pt] = scanLine;
                    processingType[pt] = "STRING";
                    pt++;
                    scanLine = scanLineAfter = "";
                }
            }else if (parentheses) {
                if (c == '(') {
                    parenthesesCount++;
                } else if (c == ')') {
                    parenthesesCount--;
                    if (parenthesesCount == 0) {
                        processingString[pt] = scanLine;
                        processingType[pt] = "PARENTHESES";
                        pt++;
                        scanLine = scanLineAfter = "";
                        parentheses = false;
                    }
                }
            }else if (bracket){
                if (c == ']'){
                    processingString[pt] = "";
                    processingType[pt] = "ARRAY";
                    pt++;
                    bracket = false;
                    scanLine = scanLineAfter = "";
                }
            }else if (append){
                if (c == ')') {
                    processingString[pt] = scanLineAfter.substr(1);
                    processingType[pt] = "APPEND";
                    pt++;
                    scanLine = scanLineAfter = "";
                    append = false;
                }
            }else if (insert){
                if (c == ')') {
                    processingString[pt] = scanLineAfter.substr(1);
                    processingType[pt] = "INSERT";
                    pt++;
                    scanLine = scanLineAfter = "";
                    insert = false;
                }
            }else if (scanLine == "if") {
                processingString[pt] = "IF";
                processingType[pt] = "IF";
                pt++;
                scanLine = scanLineAfter = "";
                disableSLA = true;
            }else if (scanLine == "else"){
                scanLine = scanLineAfter = "";
                break;
            }else{
                switch (c) {
                    case '=':
                        if (pt > 0 && processingType[pt-1] == "="){
                            processingString[pt] = "=";
                            processingType[pt] = "=";
                            pt++;
                            scanLine = scanLineAfter = "";
                            break;
                        }
                        processingString[pt] = scanLineAfter;
                        processingType[pt] = "VAR"; //Variable
                        processingString[pt + 1] = "=";
                        processingType[pt+1] = "=";
                        pt += 2;
                        scanLine = scanLineAfter = "";
                        break;
                    case '+':
                        if (scanLine.empty()){
                            processingString[pt] = "+";
                            processingType[pt] = "+";
                            pt++;
                            scanLine = scanLineAfter = "";
                        }else {
                            processingString[pt] = scanLine.substr(0, scanLine.length()-1);
                            processingType[pt] = getNumOrVar(processingString[pt]); //Variable
                            processingString[pt + 1] = "+";
                            processingType[pt + 1] = "+";
                            pt += 2;
                            scanLine = scanLineAfter = "";
                        }
                        break;
                    case '*':
                        if (scanLine.empty()){
                            processingString[pt] = "*";
                            processingType[pt] = "*";
                            pt++;
                            scanLine = scanLineAfter = "";
                        }else {
                            processingString[pt] = scanLine.substr(0, scanLine.length()-1);
                            processingType[pt] = getNumOrVar(processingString[pt]); //Variable
                            processingString[pt + 1] = "*";
                            processingType[pt + 1] = "*";
                            pt += 2;
                            scanLine = scanLineAfter = "";
                        }
                        break;
                    case '(':
                        if (scanLine == "append("){
                            append = true;
                            scanLine = scanLineAfter = "";
                        }else if (scanLine == "insert("){
                            insert = true;
                            scanLine = scanLineAfter = "";
                        }else{
                            parentheses = true;
                            parenthesesCount = 1;
                        }
                        break;
                    case '[':
                        bracket = true;
                        break;
                    case '.':
                        processingString[pt] = scanLine.substr(0, scanLine.length()-1);
                        processingType[pt] = "ARRAYVAR"; //Variable
                        processingString[pt + 1] = ".";
                        processingType[pt + 1] = ".";
                        pt += 2;
                        scanLine = scanLineAfter = "";
                        break;
                    case '"':
                        quote = true;
                        break;
                }
            }
            if (!disableSLA)
                scanLineAfter += c;
        }
        if (!scanLine.empty()){
            processingString[pt] = scanLine;
            processingType[pt] = getNumOrVar(processingString[pt]);
            pt++;
        }
        if (quote || parentheses){
            error = true;
        }

        //Debug
        for(int i = 0; i < pt; i++){
            cout << processingString[i] << ", ";
        }
        if (pt > 0) cout << endl;
        for(int i = 0; i < pt; i++){
            cout << processingType[i] << ", ";
        }
        if (pt > 0) cout << endl;

        //Process for Error
        if (countOccurrences(processingType, "=", pt) > 2){
            if (processingType[0] != "IF")
                error = true;
            else{
                string type = processSection(processingType, processingString, 1, pt);
                if (type == "ERROR") error = true;
                else if (type == "WARNING") warning = true;
            }
        }else if ((countOccurrences(processingType, "=", pt) == 1) && processingType[1] == "="){
            string type = processSection(processingType, processingString, 2, pt);
            if (type == "ERROR") error = true;
            else if (type == "WARNING") warning = true;
            else {
                variablePos = updateVariableNamePosition(processingString[0]);
                if (variableType[variablePos] != "NULL"){
                    if (variableType[variablePos] != type)
                        warning = true;
                }
                variableType[variablePos] = type;
            }
        }else if ((countOccurrences(processingType, ".", pt) == 1) && processingType[1] == ".") {
            string type = processSection(processingType, processingString, 2, pt);
            if (type == "ERROR") error = true;
            else if (type == "WARNING") warning = true;
            else {
                variablePos = updateVariableNamePosition(processingString[0]);
                if (variableType[variablePos] != "NULL" && variableType[variablePos] != "ARRAY"){
                    if (variableType[variablePos] != type)
                        warning = true;
                }
                if (variableType[variablePos] == "ARRAY")
                    variableType[variablePos] = type;
            }
        }else {
            string type = processSection(processingType, processingString, 0, pt);
            if (type == "ERROR") error = true;
            else if (type == "WARNING") warning = true;
        }
        //Output
        if (error){
            cout << "Error for \"" << line << "\"" << endl;
            outputFile << spaceCount << "#error" << endl;
        }
        else if (warning){
            cout << "Warning for \"" << line << "\"" << endl;
            outputFile << spaceCount << "#warning" << endl;
        }
        else if (variablePos != -1) { //Debugging Message. Output type of variable.
            cout << "Line: " << line << endl;
            cout << "Variable: " + variableName[variablePos] << endl;
            cout << "    Type: " << variableType[variablePos] << endl;
        }
        outputFile << line << endl;
    }



    inputFile.close();
    outputFile.close();
    return 0;
}