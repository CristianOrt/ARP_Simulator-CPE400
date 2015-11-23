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
				sendMessage();

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
void Network::sendMessage()
{
	//find both devices
	bool valid;
	char buf;
	std::string devOne, devTwo, message;
	Device* src;
	Device* dest;
	LAN* lanOne;
	LAN* lanTwo;
	LAN* lanTemp;

	//find one
	std::cout << "Source Device Name: ";
	std::cin >> devOne;
	src = mainRouter.findDevice(devOne, valid);
	if(!valid)
	{
		std::cout << devOne << "not found";
		return;
	}

	//find two
	std::cout << "Destination Device Name: ";
	std::cin >> devTwo;
	dest = mainRouter.findDevice(devTwo, valid);
	if(!valid)
	{
		std::cout << devTwo << "not found" << std::endl;
		return;
	}

	//find both LANs
	lanOne = mainRouter.findLAN(devOne, valid);
	lanTwo = mainRouter.findLAN(devTwo, valid);

	std::cout << "Message(no spaces): " << std::endl;
	std::cin >> message;

	//Same LAN's
	if(lanOne->getId() == lanTwo->getId())
	{
		//normal ArP simulate
		std::cout << "ARP Simulate press any letter to continue" << std::endl;
		std::cin >> buf;

		//check if src arp table has dest's mac by using its ip
		if(!src->arpTable[dest->getIpAddr()].init)
		{

			std::cout << "broadcasting" << std::endl;
			std::cout << "Source ID: " << src->getId() << std::endl;
			std::cout << "Source MAC: " << src->getMacAddr() << std::endl;
			std::cout << "Destination MAC: FF-FF-FF-FF-FF-FF " << std::endl;
			std::cout << "Message: Are you Ip: " << dest->getIpAddr() << std::endl;
			std::cout << "press any letter to continue" << std::endl;
			std::cin >> buf;

			//first child is always the MITM
			if(lanOne->children[0].getIsMITM() && (lanOne->children[0].getId() != src->getId()))
			{
				arpEntry temp;
				temp.isStatic = false;
 				temp.MITM = true;
				temp.macAddr = lanOne->children[0].getMacAddr();
				temp.init = true;

				std::cout << "Spoofing packet" << std::endl;
				std::cout << "Source ID: " << lanOne->children[0].getId() << std::endl;
				std::cout << "Source MAC: " << lanOne->children[0].getMacAddr() << std::endl;
				std::cout << "Destination MAC: " << src->getMacAddr() <<std::endl;
				std::cout << "Yea that's me!!" << std::endl << std::endl;
				std::cout << "press any letter to continue" << std::endl;
				std::cin >> buf;
				std::cout << "Updates arpTable with new entry found" << std::endl;
				src->arpTable[dest->getIpAddr()] = temp;
				std::cout << "press any letter to continue" << std::endl;
				std::cin >> buf;
			}
			else
			{
				arpEntry temp;
				temp.isStatic = false;
 				temp.MITM = false;
				temp.macAddr = dest->getMacAddr();
				temp.init = true;
				std::cout << "Packet" << std::endl;
				std::cout << "Source ID: " << dest->getId() << std::endl;
				std::cout << "Source MAC: " << dest->getMacAddr() << std::endl;
				std::cout << "Destination MAC: " << src->getMacAddr() <<std::endl;
				std::cout << "Yea that's me!!" << std::endl << std::endl;
				std::cout << "press any letter to continue" << std::endl;
				std::cin >> buf;
				std::cout << "Updates arpTable with new entry found" << std::endl;
				src->arpTable[dest->getIpAddr()] = temp;
				std::cout << "press any letter to continue" << std::endl;
				std::cin >> buf;
			}

		}
			//does so construct packet and simulate ARP
		arpEntry destInfo = src->arpTable[dest->getIpAddr()];

		std::cout << "Packet Info" << std::endl;
		std::cout << "Source ID: " << src-> getId() << std::endl;
		std::cout << "Source MAC: " << src->getMacAddr() << std::endl;
		std::cout << "Destination MAC: " << destInfo.macAddr << std::endl;
		std::cout << "Message: " << message << std::endl;
		std::cout << "packet delivered" << std::endl;
		std::cout << "press any letter to continue" << std::endl;
		std::cin >> buf;
	}
	else
	{
	//Different LANs
		//Arp proxy
		std::cout << "ARP Proxy Simulate press any letter to continue" << std::endl;
		std::cin >> buf;
		//check if src arp table has dest's mac by using dest's ip
		if(!src->arpTable[dest->getIpAddr()].init)
		{
			std::cout << "broadcasting" << std::endl;
			std::cout << "Source ID: " << src->getId() << std::endl;
			std::cout << "Source MAC: " << src->getMacAddr() << std::endl;
			std::cout << "Destination MAC: FF-FF-FF-FF-FF-FF " << std::endl;
			std::cout << "Message: Are you Ip: " << dest->getIpAddr() << std::endl;
			std::cout << "press any letter to continue" << std::endl;
			std::cin >> buf;

			//traverse all the lan's
			for( int i=0; i < mainRouter.children.size(); i++)
			{
				LAN* lanTemp = &mainRouter.children[i];
				if(lanTemp->children[0].getIsMITM() && (lanTemp->getId() != lanOne->getId()))
				{
				arpEntry temp;
				temp.isStatic = false;
 				temp.MITM = false;
				temp.macAddr = lanTemp->children[0].getMacAddr();
				temp.init = true;

				std::cout << "Spoofing packet" << std::endl;
				std::cout << "Source ID: " << lanTemp->children[0].getId() << std::endl;
				std::cout << "Source MAC: " << lanTemp->children[0].getMacAddr() << std::endl;
				std::cout << "Source Ip: " << dest->getIpAddr() << std::endl;
				std::cout << "Destination Ip: " << lanTemp->getIp() << std::endl;
				std::cout << "Destination MAC: " << src->getMacAddr() <<std::endl;
				std::cout << "Message: Yea that's me!!" << std::endl << std::endl;
				std::cout << "press any letter to continue" << std::endl;
				std::cout << "sending message to router." << std::endl;
				std::cin >> buf;
				std::cout << "packet gets incapuslated in an ip datagram" << std::endl;
				std::cout << "then the router changes the ip and to the next arpCache" << std:: endl;
				std::cout << "with the address of the real destination" << std::endl;
				std::cout << "press any letter to continue" << std::endl;
				std::cin >> buf;
				std::cout << "Spoofing packet" << std::endl;
				std::cout << "Source ID: " << lanTemp->children[0].getId() << std::endl;
				std::cout << "Source MAC: " << lanTemp->children[0].getMacAddr() << std::endl;
				std::cout << "Source Ip: " << lanOne->getIp() << std::endl;
				std::cout << "Destination Ip: " << src->getIpAddr() << std::endl;
				std::cout << "Destination MAC: " << src->getMacAddr() <<std::endl;		
				std::cout << "Message: Yea that's me!!" << std::endl << std::endl;
				std::cout << "press any letter to continue" << std::endl;
				

				std::cout << "Updates arpTable with new entry found" << std::endl;
				src->arpTable[dest->getIpAddr()] = temp;
				std::cout << "press any letter to continue" << std::endl;
				std::cin >> buf;
				}
				else
				{
					//traverse all the children
					for(int j=0; j < lanTemp->children.size();j++)
					{
						if(lanTemp->children[j].getMacAddr() == dest->getMacAddr())
						{
						arpEntry temp;
						temp.isStatic = false;
		 				temp.MITM = true;
						temp.macAddr = dest->getMacAddr();
						temp.init = true;

						std::cout << "Packet Info" << std::endl;
						std::cout << "Source ID: " << lanTemp->children[j].getId() << std::endl;
						std::cout << "Source MAC: " << lanTemp->children[j].getMacAddr() << std::endl;
						std::cout << "Source Ip: " << dest->getIpAddr() << std::endl;
						std::cout << "Destination Ip: " << lanTemp->getIp() << std::endl;
						std::cout << "Destination MAC: " << src->getMacAddr() <<std::endl;
						std::cout << "Message: Yea that's me!!" << std::endl << std::endl;
						std::cout << "press any letter to continue" << std::endl;
						std::cout << "sending message to router." << std::endl;
						std::cin >> buf;
						std::cout << "packet gets incapuslated in an ip datagram" << std::endl;
						std::cout << "then the router changes the ip and to the next arpCache" << std:: endl;
						std::cout << "with the address of the real destination" << std::endl;
						std::cout << "press any letter to continue" << std::endl;
						std::cin >> buf;
						std::cout << "Packet Info" << std::endl;
						std::cout << "Source ID: " << lanTemp->children[j].getId() << std::endl;
						std::cout << "Source MAC: " << lanTemp->children[j].getMacAddr() << std::endl;
						std::cout << "Source Ip: " << lanOne->getIp() << std::endl;
						std::cout << "Destination Ip: " << src->getIpAddr() << std::endl;
						std::cout << "Destination MAC: " << src->getMacAddr() <<std::endl;
						std::cout << "Message: Yea that's me!!" << std::endl << std::endl;
						std::cout << "press any letter to continue" << std::endl;

						std::cout << "Updates arpTable with new entry found" << std::endl;
						src->arpTable[dest->getIpAddr()] = temp;
						std::cout << "press any letter to continue" << std::endl;
						std::cin >> buf;
						}
					}
				}
			}
		}
		arpEntry destInfo = src->arpTable[dest->getIpAddr()];

		std::cout << "Packet Info" << std::endl;
		std::cout << "Source MAC: " << src->getMacAddr() << std::endl;
		std::cout << "Source Ip: " << src->getIpAddr() << std::endl;
		std::cout << "Destination Ip: " << lanOne->getIp() << std::endl;
		std::cout << "Destination MAC: " << destInfo.macAddr << std::endl;
		std::cout << "Message: " << message << std::endl;
		std::cout << "press any letter to continue" << std::endl;
		std::cin >> buf;
		std::cout << "packet gets incapuslated in an ip datagram" << std::endl;
		std::cout << "then the router changes the ip and to the next arpCache" << std:: endl;
		std::cout << "with the address of the real destination" << std::endl;
		std::cout << "press any letter to continue" << std::endl;
		std::cin >> buf;
		std::cout << "Packet Info" << std::endl;
		std::cout << "Source MAC: " << src->getMacAddr() << std::endl;
		std::cout << "Source Ip: " << lanOne->getIp() << std::endl;
		std::cout << "Destination Ip: " << lanTwo->getIp() << std::endl;
		std::cout << "Destination MAC: " << destInfo.macAddr << std::endl;
		std::cout << "Message: " << message << std::endl;
		std::cout << "press any letter to continue" << std::endl;
		std::cout << "Packet was delivered succesfully" << std::endl;
		//does so construct packets
			//from src to srclan transfer to new message and destlan to dest





	}

}