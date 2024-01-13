#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Step {
protected:
    string description;
    int skipCount = 0;
    int errorCount = 0;
    bool isNumberIstringstream(const string& str) {
    istringstream iss(str);
    double val;
    iss >> val;
    return iss.eof() && !iss.fail();
}

public:
    virtual void execute() = 0;
    virtual void run() = 0;
    virtual string getOutput() {
        return description;
    }

    int getSkipCount() const {
        return skipCount;
    }

    int getErrorCount() const {
        return errorCount;
    }
};

class titleStep : public Step {
public:
    void execute() override {
        cout << "Introduceti titlul: "<<endl;
        cin >> title;
        cout << "Introduceti subtitlul: "<<endl;
        cin >> subtitle;

    }
    void run() override {
        cout << title;
        cout << subtitle;
    }

private:
    string title;
    string subtitle;
};

class textStep : public Step {
public:
    void execute() override {
        cout << "Introduceti titlul: "<<endl;
        cin >> title;
        cout << "Introduceti textul: "<<endl;
        cin >> copy;
    }
    void run() override {
        cout << title;
        cout << copy;
    }

private:
    string title;
    string copy;
};

class textInputStep : public Step {
public:
    void execute() override {
        cout << "Introduceti descrierea: "<<endl;
        cin >> description;
    }
    void run() override {
        cout << description << endl;
        cout << "Introduceti textul sau introduceti tasta '1' pentru a da skip: "<<endl;
        cin >> text_input;
        if(text_input == "1")
            {
                skipCount++;
                text_input = "";
                throw string("Skip");
            }
            else if(text_input == "\n")
            {
                errorCount++;
                text_input = "0";
                throw string("Error");
            }
    }

private:
    string description;
    string text_input;
};

class numberInputStep : public Step {
public:
    string getOutput() override {
        return number_input;
    }
    void execute() override {
        cout << "Introduceti descrierea: "<< endl;
        cin >> description;
    }
    void run() override {
        cout << description << endl;
        cout << "Introduceti numarul sau introduceti tasta 's' pentru a da skip: "<<endl;
        cin >> number_input;
        if(number_input == "s")
            {
                skipCount++;
                number_input = "0";
                throw string("Skip");
            }
            else if(isNumberIstringstream(number_input) == false)
            {
                errorCount++;
                number_input = "0";
                throw string("Error");
            }

            else
            {
                number_input = stof(number_input);
            }
    }
    float getNumberInput() {
        return stof(number_input);
    }

private:
    string description;
    string number_input;
};

class calculusStep : public Step {
public:
    calculusStep(numberInputStep* inputStep1, numberInputStep* inputStep2) : inputStep1(inputStep1), inputStep2(inputStep2) {}

    void execute() override {
        cout << "Introduceti operatia: "<<endl;
        cin >> operation;
    }

    void run() override {
        float result;
        if (operation == "+") {
            result = inputStep1->getNumberInput() + inputStep2->getNumberInput();
        } else if (operation == "-") {
            result = inputStep1->getNumberInput() - inputStep2->getNumberInput();
        } else if (operation == "*") {
            result = inputStep1->getNumberInput() * inputStep2->getNumberInput();
        } else if (operation == "/") {
            if (inputStep2->getNumberInput() != 0) {
                result = inputStep1->getNumberInput() / inputStep2->getNumberInput();
            } else {
                cout << "Eroare! Nu se poate imparti la 0."<<endl;
                return;
            }
        } else {
            cout << "Eroare! Operatie invalida."<<endl;
            return;
        }
        cout << "Rezultat: " << result<<endl;
    }

private:
    string operation;
    numberInputStep* inputStep1;
    numberInputStep* inputStep2;
};

class displayStep : public Step {
public:
    displayStep(Step* step) : step(*step) {}

    void execute() override {
        cout << "Se afiseaza stepul: " << typeid(step).name() + 6 << endl;
    }

    void run() override {
        step.execute();
        step.run();
    }

private:
    Step& step;
};

class textFile : public Step {
public:
    void execute() override {
        cout << "Introduceti descrierea: "<<endl;
        cin >> description;
    }
    void run() override {
        cout << description;
        cout << "Introduceti numele fisierului: "<<endl;
        cin >> file_name;
        ofstream file;
        file.open(file_name, ios::app);
        cout << "Introduceti textul (END pentru a opri): "<<endl;
        string text;
        cin.ignore(); 
        getline(cin, text);
        file << text << endl;
        file.close();
    }

private:
    string description;
    string file_name;
};

class csvFile : public Step {
public:
    string getOutput() override {
        ifstream file(file_name);
        string output((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        return output;
    }
    void execute() override {
        cout << "Introduceti descrierea: "<<endl;
        cin >> description;
    }
    void run() override {
        cout << description;
        cout << "Introduceti numele fisierului: "<<endl;
        cin >> file_name;
        ofstream file;
        file.open(file_name, ios::app); 
        cout << "Introduceti textul (END pentru a opri): "<<endl;
        string text;
        bool first = true;
        while (cin >> text && text != "END") {
            if (!first)
                file << ",";
            file << text;
            first = false;
        }
        file << endl;
        file.close();
    }

private:
    string description;
    string file_name;
};

class outputStep : public Step {
public:
    outputStep(Step* prevStep) : prevStep(prevStep) {}

    void execute() override {
        cout << "Introduceti numele fisierului: "<<endl;
        cin >> file_name;
        cout << "Introduceti titlul fisierului: "<<endl;
        cin >> title;
        cout << "Introduceti descrierea fisierului: "<<endl;
        cin >> description;
    }

    void run() override {
        ofstream file;
        file.open(file_name, ios::app);  // Open the file in append mode
        file << title << "\n" << description << "\n";
        if (prevStep)
            file << prevStep->getOutput();
        file.close();
    }

private:
    string file_name;
    string title;
    string description;
    Step* prevStep;
};
