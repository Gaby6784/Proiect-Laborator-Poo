#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Step.h" 
#include <ctime>
using namespace std;

class Flow {
private:
    vector<Step*> steps;

    void addStep(Step* step) {
        steps.push_back(step);
    }
    string name;
    time_t creationTime;
        int startCount = 0;
        int completionCount = 0;

    public:
        Flow() {
            time(&creationTime);
            cout<<creationTime<<endl;
        }

        string getName() const {
            return name;
        }

        void setName(const string& newName) {
            name = newName;
        }

        time_t getCreationTime() const {
            return creationTime;
        }

        vector<Step*> getSteps() const {
            return steps;
        }

    void constructor() {
        int ok = 1;
        string name;
        cout<<"Introduceti numele flow-ului: "<<endl;
        cin.get();
        getline(cin, name);
        setName(name);
        while (ok == 1) {
            int option;
            cout<<"Alegeti o optiune: "<<endl; 
            cout << "1. Title" << endl;
            cout << "2. Text" << endl;
            cout << "3. Text input" << endl;
            cout << "4. Number input" << endl;
            cout << "5. Calculus" << endl;
            cout << "6. Display" << endl;
            cout << "7. Text file" << endl;
            cout << "8. CSV file" << endl;
            cout << "9. Output" << endl;
            cout << "10. Exit" << endl;
            cin >> option;
            
            switch (option) {
                case 1: {
                    Step* title = new titleStep();
                    title->execute();
                    addStep(title);
                } break;
                case 2: {
                    Step* text = new textStep();
                    text->execute();
                    addStep(text);
                } break;
                case 3: {
                    Step* textInput = new textInputStep();
                    textInput->execute();
                    addStep(textInput);
                } break;
                case 4: {
                    Step* numberInput = new numberInputStep();
                    numberInput->execute();
                    addStep(numberInput);
                } break;
                case 5: {
                    cout<<"Introduceti indexul pasilor pe care vreti sa ii folositi: "<<endl;
                    int pas1, pas2;
                    cin>>pas1>>pas2;
                    numberInputStep* pasul1 = dynamic_cast<numberInputStep*>(steps[pas1]);
                    numberInputStep* pasul2 = dynamic_cast<numberInputStep*>(steps[pas2]);
                    Step* calculus = new calculusStep(pasul1, pasul2);
                    calculus->execute();
                    addStep(calculus);
                } break;
                case 6: {
                    cout<<"Ce pas vreti sa se afiseze?"<<endl;
                    int pas;
                    cin>>pas;
                    Step* pasul = steps[pas];
                    Step* display = new displayStep(pasul); 
                    display->execute();
                    addStep(display);
                } break;
                case 7: {
                    Step* textFileStep = new textFile();
                    textFileStep->execute();
                    addStep(textFileStep);
                } break;
                case 8: {
                    Step* csvFileStep = new csvFile();
                    csvFileStep->execute();
                    addStep(csvFileStep);
                } break;
                case 9: {
                    Step* output = new outputStep(nullptr); 
                    output->execute();
                    addStep(output);
                } break;
                case 10: {
                    ok = 0;
                } break;
                default:
                    cout << "Invalid option. Please enter a valid option." << endl;
                    break;
            }
        }
    }

    void run() {
        ++startCount;
        for (int i = 0; i < steps.size(); i++) {
            try{
            steps[i]->run();
            } catch (string s) {
                cout<<s<<endl;
            }
        }
        ++completionCount;
    }

    int getStartCount() const {
        return startCount;
    }

    int getCompletionCount() const {
        return completionCount;
    }

};

