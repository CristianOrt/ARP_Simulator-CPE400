#ifndef ROUTER_H
#define ROUTER_H
#include <vector>
#include <string>
#include "LAN.h"

class Router{
public:
Router(std::string name);
~Router(){};
bool insertLAN(LAN temp);
bool insertDevice(std::string LANId, std::string deviceId, bool MITM = false);

void GenerateGraphviz(const std::string& file_name) const;

void Display();


private:
std::string id;
std::vector<LAN> children;


};
#endif
