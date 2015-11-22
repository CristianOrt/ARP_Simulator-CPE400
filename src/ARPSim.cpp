#include "Network.h"
#include "Router.h"
#include "LAN.h"
#include "Device.h"
#include <iostream>

using namespace std;

int main()
{
LAN A("1A.78.6D.", "192.16.12.", "LAN_A");
A.insertChild("Device_A");
A.insertChild("Device_B");
A.insertChild("Device_C");
A.Display();
A.GenerateGraphviz("Network_Architecture");

return 0;
}
	