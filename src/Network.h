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
Network(std::string );
~Network(){};

//Display
void DisplayInit();
void DisplayMainMenu();

//Simulate
void SimulateARP();
void SimulateSpoofing();

//helpers
void broadcast();

//options
void insertStaticEntry();
void insertDeviceDisplay();
void insertLANDisplay();
void sendMessage(Device src, Device dest);



private:
Router mainRouter;

};
#endif
