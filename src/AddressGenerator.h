#ifndef ADDRESS_GENERATOR_H
#define ADDRESS_GENERATOR_H

#include <string>

class AddressGenerator {
public:
  AddressGenerator();
  AddressGenerator(std::string pre);
  void setPrefix(std::string pre);
  std::string GenerateTicket();

private:
  std::string prefix;
  int count;
};

#endif // ADDRESS_GENERATOR_H