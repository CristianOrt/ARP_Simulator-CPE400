#include <string>
#include <vector>
#include "Device.h"
#include "AddressGenerator.h"
class AddressGenerator;
class LAN{
public:
	//Constructors
	LAN(std::string macPrefix, std::string ipPrefix, std::string name);
	~LAN(){};

	void insertChild(Device child);
	//broadcast to every child in LAN
	void broadcastChild(Device child, packet bPacket);
	//GenerateGraphiz
	void GenerateGraphviz(const std::string& file_name) const;
private:
std::string id;
static AddressGenerator macGen;
static AddressGenerator ipGen;
std::vector<Device> children;

};
