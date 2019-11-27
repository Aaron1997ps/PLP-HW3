#include <iostream>
#include <fstream>
#include <array>
#include <string>
using namespace std;

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