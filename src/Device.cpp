#include "Device.h"

Device::Device(std::string name){
//assign id, macAddr, ipAddr
id = name;
//macAddr = genMac;
//ipAddr = genIp;
}
bool Device::insertToArpTable(std::string mac, std::string ip, bool isStatic){
//if not found then insert it and return true;
arpEntry temp;
temp.isStatic = isStatic;
temp.macAddr = mac;
if(arpTable[ip].init == false)
	{	
		temp.init = true;
		arpTable[ip] = temp;
		return true;
	}
else
	{
		if(arpTable[ip].isStatic)
			{
				return false;
			}
		else
			{
				temp.init = true;
				arpTable[ip] = temp;
				return true;
			}
	}
}

packet Device::sendMessage(std::string destMac, std::string message){
packet packetMessage;
packetMessage.srcMac = macAddr;
packetMessage.destMac = destMac;
packetMessage.message = message;
return packetMessage;
}