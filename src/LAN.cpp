#include "LAN.h"

using namespace std;


LAN::LAN(std::string macNum, std::string ipNum, std::string name)
{
id = name;
ip = ipNum + "00";
ipPrefix = ipNum;
macPrefix = macNum;
ipCount = macCount = 1;
}

bool LAN::insertChild(std::string deviceName, bool MITM)
{
 // check if name not already taken
 for(auto child : children){
      if(child.getId() == deviceName){return false;}
    }

 Device child(deviceName, macGen() , ipGen(), MITM);
 //push to front of vector
 if(MITM)
 {
 	std::vector<Device>::iterator it;
 	it = children.begin();
 	children.insert(it,child);
 }
 else{
 children.push_back(child);
}
 return true;
}

std::string LAN::macGen()
{
  char buffer[macPrefix.size() + 2];
  sprintf(buffer, "%s%02d", macPrefix.c_str(), macCount++);
  return string(buffer);
}

std::string LAN::ipGen()
{
  char buffer[ipPrefix.size() + 2];
  sprintf(buffer, "%s%02d", ipPrefix.c_str(), ipCount++);
  return string(buffer);
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
    fout << "edge [color=black];" << endl;
    fout << id << " -> "; 
    fout << child.getId()<< endl;
  }
}
Device* LAN::find(std::string devId, bool& valid)
{
	Device* child = NULL;
	for( int i=0; i < children.size(); i++)
	{
		if(devId == children[i].getId())
		{
			valid = true;
			child = &children[i];
			return child;
		}
	}
	valid = false;
	return child;
}