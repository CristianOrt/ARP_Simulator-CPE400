#include "LAN.h"
#include <iostream>

using namespace std;

AddressGenerator LAN::macGen;
AddressGenerator LAN::ipGen;

LAN::LAN(std::string macPrefix, std::string ipPrefix, std::string name)
{
id = name;
ip = ipPrefix + "00";
ipGen.setPrefix(ipPrefix);
macGen.setPrefix(macPrefix);
}

void LAN::insertChild(std::string deviceName)
{
 Device child(deviceName, macGen.GenerateTicket() , ipGen.GenerateTicket());
 children.push_back(child);
}

void LAN::broadcastChild(Device child, packet bPacket)
{

}

void LAN::GenerateGraphviz(const std::string& file_name) const
{
 // Create file stream.
  string dot_name(file_name);
  dot_name.append(".dot");
  ofstream fout(dot_name);


  // Create a digraph.
  std::string LAN_lbl = "IP: " + ip;
  fout << "digraph Network {" << endl;
  fout << "\t\tmain [shape=none, margin=0, label=<" << endl;
  fout << "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\">" << endl;
  fout << "\t<TR><TD COLSPAN=\"3\">" << id << "</TD></TR>" << endl;
  fout << "\t<TR><TD COLSPAN=\"3\">" << LAN_lbl << "</TD></TR>" << endl;
  fout << "</TABLE>>];" << endl;

  //generate the graphviz of each child.

  for(auto child : children) {
  	fout << "\t\t" << child.getId() <<"[shape=none, margin=0, label=<" << endl;
   	fout << "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"3\">" << endl;
   	fout << "\t<TR><TD COLSPAN=\"3\">" << child.getId() << "</TD></TR>" << endl;
   	std::string temp = "IP: " + child.getIpAddr();
  	fout << "\t<TR><TD COLSPAN=\"3\">" << temp <<"</TD></TR>" << endl;
  	temp = "MAC: " + child.getMacAddr();
  	fout << "\t<TR><TD COLSPAN=\"3\">" << temp << "</TD></TR>" << endl;
  	fout << "</TABLE>>];" << endl;

    fout << "main" << " -> "; 
    fout << child.getId()<< endl;
  }

  // Finish digraph.
  fout << "}";

  // Close the file.
  fout.close();

  // Create the png of the AST.
  string sys_call("dot -Tpng ");
  sys_call.append(dot_name);
  sys_call.append(" -o ");
  sys_call.append(file_name);
  sys_call.append(".png");
  system(sys_call.c_str());
}