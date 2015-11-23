#include "Network.h"
#include "Router.h"
#include "LAN.h"
#include "Device.h"
#include <iostream>

using namespace std;

int main()
{
	
	Network mainNet("main");
	mainNet.DisplayInit();
	mainNet.DisplayMainMenu();
/*
std::string lan1, lan2, dev1,dev2;
Router router;

router.setName("main");
LAN lanA ("12-89-56-48-78-", "192.15.14.", "LAN_A");
router.insertLAN(lanA);
router.insertDevice("LAN_A", "devA", false);
router.insertDevice("LAN_A", "devB", false);
router.GenerateGraphviz("temp");
*/

//now i need to make a static entry between devA and devB
/*
bool validDev;
Device* devIt;
devIt = router.findDevice("devA", validDev );

//use lanIt and now find devices
if(validDev){cout << devIt->getId() << endl;}
else{cout << "nope" << endl;}
*/

return 0;
}
	