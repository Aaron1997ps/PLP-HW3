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
    string getPartialList(const string& variable, int start, int end);
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
            return get<2>(i);
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
string variableStorage::getPartialList(const string &variable, int start, int end) {
    string value = getValue(variable);
    int totalElements = count(value.begin(), value.end(), ',') + 1;

    //Remove brackets
    value = value.substr(1, value.length() -2);

    for(int i = 0; i < start; i ++){
        value = value.erase(0, value.find(',')+1);
    }

    if (start == end){
        return value.substr(0,value.find(','));
    }

    if (end != totalElements) {
        end = totalElements-end;
        for(unsigned int i = value.length()-1; i > 0 && end != 0; i--){
            if (value[i] == ','){
                value = value.substr(0, i);
                end -= 1;
            }
        }
    }

    return "[" + value + "]";
}

void throwError(){
    cout << "#error" << endl;
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


    string line, originalLine;
    string vari, data, type;
    char cdata;
    variableStorage variables;

    while(getline(inputFile, line)){
        originalLine = line;

        //Erases all the spaces in the line and everything after a #
        for(int i=0; i < line.length(); i++){
            if(line[i] == ' ') line.erase(i, 1);
            if(line[i] == '#') line.erase(i, line.length() - i);
        }

        size_t del = line.find('=');


        if(line.empty()) {
            outputFile << originalLine << endl;
        }else if(line.substr(0,5) == "print"){
            if (line.find('[') == string::npos) { //[ is Not Found in String, thus print out the value as is
                outputFile << originalLine << endl;
                outputFile << ">>>" << variables.getValue(line.substr(6, line.length() - 7)) << endl;
            }else{
                bool errorOccured = false;

                string var = line.substr(6, line.find('[') - 6); //Variable
                string val = variables.getValue(var);

                //Remove brackets
                val = val.substr(1,val.length()-2);

                if (val.empty()) {
                    throwError();
                    errorOccured = true;
                }else{
                    if (line.find(':') == string::npos){
                        int pos = stoi(line.substr(line.find('[')+1, line.find(']') - line.find('[') -1 ));
                        line = variables.getPartialList(var, pos, pos); //Line temporarily being used to transfer data to output
                    }else{
                        int pos1, pos2;
                        string temp = line.substr(line.find('[')+1, line.find(':') - line.find('[') -1 );
                        if (temp.empty())
                            pos1 = 0;
                        else
                            pos1 = stoi(temp);

                        temp = line.substr(line.find(':')+1, line.find(']') - line.find(':') -1 );
                        if (temp.empty())
                            pos2 = count(line.begin(), line.end(), ',') + 2;
                        else
                            pos2 = stoi(temp);

                        line = variables.getPartialList(var, pos1, pos2); //Line temporarily being used to transfer data to output
                    }
                }

                outputFile << originalLine << endl;
                if (!errorOccured)
                    outputFile << ">>>" << line << endl;

            }
        }else if(line.find('=')) {
            vari = line.substr(0, del);
            data = line.substr(del + 1);
            cdata = data[0];
            if (cdata == '[') {
                type = "list";
            } else if (isdigit(cdata)) {
                type = "int";
            } else if (cdata == '\"' or cdata == "\'"){
                type = "string";
            } else {
                type = variables.getType(data);
                data = variables.getValue(data);
            }

            variables.setVariable(vari, type, data);

            outputFile << originalLine << endl;
        }
    }





    inputFile.close();
    outputFile.close();
    return 0;
}