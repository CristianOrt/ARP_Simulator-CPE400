#include "Network.h"
#include "Router.h"
#include "LAN.h"
#include "Device.h"
#include <iostream>

using namespace std;

int main()
{

Router router("main");
LAN A("1A.78.6D.", "192.16.12.", "LAN_A");
router.insertLAN(A);
router.insertDevice("LAN_A", "Device_A",false);
LAN B("24.56.8D","192.54.46.","LAN_B");
router.insertLAN(B);
router.insertDevice("LAN_B","Device_B",true);
router.Display();
router.GenerateGraphviz("NetworkArchitecture");
return 0;
}
	