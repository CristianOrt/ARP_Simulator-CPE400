#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include "Router.h"

struct packet{
std::string srcMac;
std::string destMac;
std::string message;
};
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

//helpers
void sendMessage();
void broadcast();



private:
Router mainRouter();

};
#endif
