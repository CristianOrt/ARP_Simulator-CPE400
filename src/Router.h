#ifndef ROUTER_H
#define ROUTER_H
#include <vector>
#include <string>
#include "LAN.h"

class Router{
public:
Router(){};
~Router(){};
void setName(std::string name){id = name;};
bool insertLAN(LAN temp);
bool insertDevice(std::string LANId, std::string deviceId, bool MITM = false);
LAN* find(std::string lanId, bool& valid);
Device* findDevice(std::string devId, bool &valid);
LAN* findLAN(std::string devId, bool& valid);

void GenerateGraphviz(const std::string& file_name) const;

void Display();
std::vector<LAN> children;

private:
std::string id;



};
#endif
