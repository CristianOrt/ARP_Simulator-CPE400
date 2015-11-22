#include "Device.h"

Device::Device(std::string name, std::string mac, std::string ip, bool MITM){
//assign id, macAddr, ipAddr
id = name;
macAddr = mac;
ipAddr = ip;
isMITM = MITM;
}
bool Device::insertToArpTable(std::string mac, std::string ip, bool isStatic, bool MITM){
//if not found then insert it and return true;
arpEntry temp;
temp.isStatic = isStatic;
temp.macAddr = mac;
temp.MITM = MITM;
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

bool Device::searchARPTable(std::string ip, arpEntry& dest)
{
//does it exist
dest = arpTable[ip];
if(dest.init == false)
{
	return false;
}
//it does
else
{
	if(dest.isStatic == true)
	{
		return true;
	}
	else
	{
		//search for mallicious entries and save that instead
		for( std::map<std::string, arpEntry>::const_iterator it = arpTable.begin(); it != arpTable.end(); ++it )
    	{
      	arpEntry temp = it->second;
      		if(temp.MITM == true)
      		{
      			dest = temp;
      			return true;
      		}
    	}
	}
}
}