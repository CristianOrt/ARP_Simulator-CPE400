#ifndef Device_H
#define Device_H
#include <string>
#include <ostream>
#include <map>

struct arpEntry{
bool isStatic;
bool MITM;
std::string macAddr;
bool init = false;
};


class Device{
public:
//Constructors
Device(std::string name, std::string mac, std::string ip, bool MITM);
~Device(){};

//sets & gets
void setId(std::string name){id = name;};
void setMacAddr(std::string mac){macAddr = mac;};
void setIpAddr(std::string ip){ipAddr = ip;};
void setisMITM(bool val){isMITM = val;};
std::string getId(){return id;};
std::string getMacAddr(){return macAddr;};
std::string getIpAddr(){return ipAddr;};
bool getIsMITM(){return isMITM;};

//helper functions
//returns true if it was inserted or updated one already in there,
//false if it was a static entry and it 
bool insertToArpTable(std::string mac, std::string ip, bool isStatic, bool MITM);
bool isARPEntryMITM(arpEntry temp){return temp.MITM;};
bool searchARPTable(std::string ip, arpEntry& dest);
void clearARPTable(){arpTable.clear();};
std::map<std::string, arpEntry> arpTable;


private:
std::string id;
std::string macAddr;
std::string ipAddr;
bool isMITM;
};
#endif
