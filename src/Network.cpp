#include "Network.h"

Network::Network(std::string routerId)
{
mainRouter.setName(routerId);
}
//Display
void Network::DisplayInit()
{
	char buf;
	//display name
	std::cout << "ARP Simulator" << std::endl;
	std::cout << "setup first LAN: " << std::endl;
	insertLANDisplay();
	std::cout << std::endl;
	std::cout << "setup first Device in LAN: " << std::endl;
	insertDeviceDisplay();
	std::cout << std::endl;
	std::cout << "This simulator can demonstrate ARP," << std::endl;
	std::cout << "ARP spoofing, ARP proxy, and prevention of ARP" << std::endl;
	std::cout << "spoofing with static entries" << std::endl;
	std::cout << "Press any letter to continue ... " << std::endl; 
	std::cin >> buf;
	std::cout << "The main menu will allow you to add more LAN networks" << std::endl;
	std::cout << "Devices, sendMessages, and create static entries." << std::endl;
	mainRouter.GenerateGraphviz("Network_Architecture");
	std::cout << "Also you may see your network in" << std::endl;
	std::cout << "../bin called 'Network_Architecture'" << std::endl;

}
void Network::DisplayMainMenu()
{
	char option = 'i';
	do{
		std::cout << "Choose an option" << std::endl;

		std::cout << "a:insert static entry" << std::endl;
		std::cout << "b:insert Device" << std::endl;
		std::cout << "c:insert LAN" << std::endl;
		std::cout << "d:send Message" << std::endl;
		std::cout << "e:generate new graph" << std::endl;
		std::cout << "f:Quit" << std::endl;
		std::cin >> option;

		switch(option){

			case 'a':
				insertStaticEntry();

				break;

			case 'b':
				insertDeviceDisplay();

				break;

			case 'c':
				insertLANDisplay();

				break;

			case 'd':
				//sendMessage();

				break;

			case 'e':
				mainRouter.GenerateGraphviz("Network_Architecture");
				std::cout << "graph genertated in bin name 'Network_Architecture'" << std::endl;

				break;

			case 'f':

				break;

			default:
				std::cout << "invalid input" << std::endl;

		}
	}while(option != 'f');
	return;

}

//Simulate
void Network::SimulateARP()
{

}
void Network::SimulateSpoofing()
{

}

//helpers
void Network::broadcast()
{

}

//options
void Network::insertStaticEntry()
{
	bool valid;
	std::string devOne, devTwo;
	Device* srcOne;
	Device* srcTwo;
	//find one
	std::cout << "Device One Name: " << std::endl;
	std::cin >> devOne;
	srcOne = mainRouter.findDevice(devOne, valid);
	if(!valid)
	{
		std::cout << devOne << "not found" << std::endl;
		return;
	}

	//find two
	std::cout << "Device Two Name: " << std::endl;
	std::cin >> devTwo;
	srcTwo = mainRouter.findDevice(devTwo, valid);
	if(!valid)
	{
		std::cout << devTwo << "not found" << std::endl;
		return;
	}

	//set both static arpEntries

	srcOne->insertToArpTable(srcTwo->getMacAddr(), srcTwo->getIpAddr(), true, srcTwo->getIsMITM());
	srcTwo->insertToArpTable(srcOne->getMacAddr(), srcOne->getIpAddr(), true, srcOne->getIsMITM());
	std:: cout << "complete" << std::endl;

}
void Network::insertDeviceDisplay()
{
	char temp;
	std::string lanId, deviceId;
	std::cout << "insert name of LAN to insert device: ";
	std::cin >> lanId;
	std::cout << "insert name of device: ";
	std::cin >> deviceId;
	std::cout << "is your device mallicious: (y/n) ";
	std::cin >> temp;
	bool mitm = false;
	if(temp == 'y'){mitm = true;}


	if(!mainRouter.insertDevice(lanId, deviceId, mitm))
	{
		std::cout << "LAN doesnt exist or device already declared" << std::endl;
	}
}
void Network::insertLANDisplay()
{
	std::string lanName, ipPre, macPre;
	std::cout << "insert LAN name (no spaces): ";
	std::cin >> lanName;
	std::cout << "insert first 3 segments of ip: " << std::endl;
	std::cout << "(example: '192.14.15.') the program will generate the last portion" << std::endl;
	std::cin >> ipPre;
	std::cout << "insert first 4 segments of mac: " << std::endl;
	std::cout << "(example: '01-23-98-ab-89-') the program will generate the last portion" << std::endl;
	std::cin >> macPre;
	LAN temp(macPre, ipPre, lanName);
	if(!mainRouter.insertLAN(temp)){std::cout << "LAN already exists" << std::endl;}
}
void Network::sendMessage(Device src, Device dest)
{

}