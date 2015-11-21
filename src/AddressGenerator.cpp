#include "AddressGenerator.h"

#include <cstdlib>
#include <string>

using namespace std;
AddressGenerator::AddressGenerator()
{
	count =1;
}
AddressGenerator::AddressGenerator(string pre) : prefix(pre), count(1) {}
void AddressGenerator::setPrefix(std::string pre)
{
	prefix = pre;
}
string AddressGenerator::GenerateTicket() {
  char buffer[prefix.size() + 2];
  sprintf(buffer, "%s%02d", prefix.c_str(), count++);
  return string(buffer);
}