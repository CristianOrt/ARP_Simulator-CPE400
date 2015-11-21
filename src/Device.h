#ifndef Device_H
#define Device_H
#include <string>
#include <ostream>
#include <map>

struct arpEntry{
bool isStatic;
std::string macAddr;
bool init = false;
};

struct packet{
std::string srcMac;
std::string destMac;
std::string message;
};

class Device{
public:
//Constructors
Device(std::string name, std::string mac, std::string ip);
~Device(){};

//sets & gets
void setId(std::string name){id = name;};
void setMacAddr(std::string mac){macAddr = mac;};
void setIpAddr(std::string ip){ipAddr = ip;};
std::string getId(){return id;};
std::string getMacAddr(){return macAddr;};
std::string getIpAddr(){return ipAddr;};

//helper functions
//returns true if it was inserted or updated one already in there,
//false if it was a static entry and it 
bool insertToArpTable(std::string mac, std::string ip, bool isStatic);
packet sendMessage(std::string destMac, std::string message);



private:
std::string id;
std::string macAddr;
std::string ipAddr;
std::map<std::string, arpEntry> arpTable;
};
#endif
