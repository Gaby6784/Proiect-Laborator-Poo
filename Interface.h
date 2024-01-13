#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Step.h"
#include "Flow.h"
#include <ctime>

using namespace std;

class Interface {
private:
    vector <Flow*> flows;

public:
    Interface() {
        int ok = 1;
        while (ok == 1) {
            cout<<"Alegeti o optiune: "<<endl;
            cout << "1. Create flow" << endl;
            cout << "2. Run flow" << endl;
            cout << "3. Delete flow" << endl;
            cout << "4. Show flows" << endl;
            cout << "5. Flow analytics" << endl;
            cout << "6. Exit" << endl;
            
            int option;
            cin >> option;

            switch (option) {
                case 1: {
                    Flow* flow = new Flow();
                    flow->constructor();
                    flows.push_back(flow);
                } break;
                
                case 2: {
                    if (flows.empty()) {
                        cout << "No flows available." << endl;
                    } else {
                        cout << "Enter the flow number: ";
                        int flowNumber;
                        cin >> flowNumber;

                        if (flowNumber >= 0 && flowNumber < flows.size()) {
                            flows[flowNumber]->run();
                        } else {
                            cout << "Invalid flow number." << endl;
                        }
                    }
                } break;
                
                case 3: {
                    if (flows.empty()) {
                        cout << "No flows available." << endl;
                    } else {
                        cout << "Enter the flow number: ";
                        int flowNumber;
                        cin >> flowNumber;

                        if (flowNumber >= 0 && flowNumber < flows.size()) {
                            flows.erase(flows.begin() + flowNumber);
                        } else {
                            cout << "Invalid flow number." << endl;
                        }
                    }
                } break;

                case 4: {
                    if (flows.empty()) {
                        cout << "No flows available." << endl;
                    } else {
                        cout << "Available flows:" << endl;
                        for (const auto& flow : flows) {
                            time_t creationTime = flow->getCreationTime();
                            cout << flow->getName() << " created at " << asctime(localtime(&creationTime)) << endl;
                        }
                    }
                } break;

                case 5: {
                    if (flows.empty()) {
                        cout << "No flows available." << endl;
                    } else {
                        cout << "Enter the flow number: ";
                        int flowNumber;
                        cin >> flowNumber;

                        if (flowNumber >= 0 && flowNumber < flows.size()) {
                            Flow* flow = flows[flowNumber];
                            cout << "Start count: " << flow->getStartCount() << endl;
                            cout << "Completion count: " << flow->getCompletionCount() << endl;
                            int errors = 0;
                            for(const auto& step : flow->getSteps()) {
                                cout << "Step: " << step->getOutput() << endl;
                                cout << "Skip count: " << step->getSkipCount() << endl;
                                cout << "Error count: " << step->getErrorCount() << endl;
                                errors += step->getErrorCount();
                            }
                            if(flow->getCompletionCount() > 0)
                                cout << "Average errors per run: " << errors / flow->getCompletionCount() << endl;
                                else
                                cout << "Average errors per run: 0" << endl;
                        } else {
                            cout << "Invalid flow number." << endl;
                        }
                    }
                } break;
                
                case 6: {
                    ok = 0;
                } break;
            }
        }
    }
};



