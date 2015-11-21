#ifndef NETWORK_H
#define NETWORK_H

#include "Router.h"

class Network {
public:
//Constructor & Destructor
Network();
~Network();

//Display
void DisplayTutorial();
void DisplayMainMenu();

//Simulate
void SimulateARP();
void SimulateSpoofing();



private:
Router mainRouter();

};
#endif
