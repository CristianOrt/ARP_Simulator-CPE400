#include "LAN.h"

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

bool LAN::insertChild(std::string deviceName, bool MITM)
{
 // check if name not already taken
 for(auto child : children){
      if(child.getId() == deviceName){return false;}
    }

 Device child(deviceName, macGen.GenerateTicket() , ipGen.GenerateTicket(), MITM);
 children.push_back(child);
 return true;
}

void LAN::GenerateGraphviz(std::ofstream& fout) const
{
  // Create a digraph.
  std::string LAN_lbl = "IP: " + ip;
  fout << "\t\t" << id << "[shape=none, margin=0, label=<" << endl;
  fout << "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\">" << endl;
  fout << "\t<TR><TD COLSPAN=\"3\">" << id << "</TD></TR>" << endl;
  fout << "\t<TR><TD COLSPAN=\"3\">" << LAN_lbl << "</TD></TR>" << endl;
  fout << "</TABLE>>];" << endl;

  //generate the graphviz of each child.

  for(auto child : children) {
  	fout << "\t\t" << child.getId() <<"[shape=none, margin=0, label=<" << endl;
   	fout << "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"3\">" << endl;
    if(child.getIsMITM()){fout << "\t<TR><TD COLSPAN=\"3\"><FONT COLOR=\"red\">" << child.getId() << "</FONT></TD></TR>" << endl;}
    else{fout << "\t<TR><TD COLSPAN=\"3\">" << child.getId() << "</TD></TR>" << endl;}
   	std::string temp = "IP: " + child.getIpAddr();
  	fout << "\t<TR><TD COLSPAN=\"3\">" << temp <<"</TD></TR>" << endl;
  	temp = "MAC: " + child.getMacAddr();
  	fout << "\t<TR><TD COLSPAN=\"3\">" << temp << "</TD></TR>" << endl;
  	fout << "</TABLE>>];" << endl;
    
    if(child.getIsMITM()){fout << "edge [color=red];" << endl;}
    else{fout << "edge [color=black];" << endl;}
    fout << id << " -> "; 
    fout << child.getId()<< endl;
  }
}