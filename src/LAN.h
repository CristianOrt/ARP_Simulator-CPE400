#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include "Device.h"
#include "AddressGenerator.h"
class LAN{
public:
	//Constructors
	LAN(std::string macPrefix, std::string ipPrefix, std::string name);
	~LAN(){};

	void insertChild(std::string deviceName);
	//broadcast to every child in LAN
	void broadcastChild(Device child, packet bPacket);
	//GenerateGraphiz
	void GenerateGraphviz(const std::string& file_name) const;

	void Display(){
		std::cout << "LAN: " << id <<  " ip: " << ip << std::endl;
		for(auto child : children){
			std::cout << "Device: " << child.getId() << " mac: " << child.getMacAddr();
			std::cout << " ip: " << child.getIpAddr(); 
			std::cout << std::endl;
		}

	};
	
private:
std::string ip;
std::string id;
static AddressGenerator macGen;
static AddressGenerator ipGen;
std::vector<Device> children;

};
