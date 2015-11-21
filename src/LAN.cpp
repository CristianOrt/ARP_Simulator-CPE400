#include "LAN.h"
#include <iostream>

using namespace std;

AddressGenerator LAN::macGen;
AddressGenerator LAN::ipGen;

LAN::LAN(std::string macPrefix, std::string ipPrefix, std::string name)
{
id = name;
ipGen.setPrefix(ipPrefix);
macGen.setPrefix(macPrefix);
}

void LAN::insertChild(Device child)
{

}

void LAN::broadcastChild(Device child, packet bPacket)
{
	//GenerateGraphiz
}

void LAN::GenerateGraphviz(const std::string& file_name) const
{

}