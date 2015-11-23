#ifndef LAN_H
#define LAN_H
#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include "Device.h"

class LAN{
public:
	//Constructors
	LAN(std::string macNum, std::string ipNum, std::string name);
	~LAN(){};
	std::string getId(){return id;};
	std::string getIp(){return ip;};

	bool insertChild(std::string deviceName, bool MITM = false);
	bool broadcast(std::string ipDest);
	std::string macGen();
	std::string ipGen();
	Device* find(std::string devId, bool& valid);




	//GenerateGraphiz
	void GenerateGraphviz(std::ofstream& fout) const;

	void Display(){
		std::cout << "LAN: " << id <<  " ip: " << ip << std::endl;
		for(std::vector<Device>::iterator child = children.begin(); child != children.end(); ++child){
			std::cout << "Device: " << child->getId() << " mac: " << child->getMacAddr();
			std::cout << " ip: " << child->getIpAddr(); 
			std::cout << std::endl;
		}
	};
	
std::vector<Device> children;
private:
std::string ip;
std::string id;
std::string ipPrefix;
std::string macPrefix;
int macCount;
int ipCount;

};
#endif