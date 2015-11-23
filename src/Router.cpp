#include "Router.h"
#include <iostream>

using namespace std;

bool Router::insertLAN(LAN temp)
{
	//search if LAN already exists
	for( auto child : children)
	{
		if(child.getId() == temp.getId()){return false;}
	}
	children.push_back(temp);
	return true;

}

bool Router::insertDevice(std::string LANId, std::string deviceId, bool MITM)
{
	//search for LAN
	for (int i = 0; i < children.size(); i++){
		if(children.at(i).getId() == LANId)
		{
			children.at(i).insertChild(deviceId, MITM);
			return true;
		}
	}
	//Lan not found
	return false;
}

void Router::GenerateGraphviz(const std::string& file_name) const
{
  // Create file stream.
  string dot_name(file_name);
  dot_name.append(".dot");
  ofstream fout(dot_name);

  // Create a digraph.
  fout << "digraph Network {" << endl;
  fout << "\t\t" << id << "[shape=none, margin=0, label=<" << endl;
  fout << "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\">" << endl;
  fout << "\t<TR><TD COLSPAN=\"3\">" << id << "</TD></TR>" << endl;
  fout << "</TABLE>>];" << endl;

  for( auto child : children){
  	child.GenerateGraphviz(fout);
  	fout << id << " ->";
  	fout << child.getId() << endl;
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

void Router::Display(){
		std::cout << "Router: " << id << std::endl;
		for(std::vector<LAN>::iterator child = children.begin(); child != children.end(); ++child){
      child->Display();
			std::cout << std::endl;
		}
}

LAN* Router::find(std::string lanId, bool& valid){
	LAN* child = NULL;
	for( int i=0; i < children.size(); i++)
	{
		if(lanId == children[i].getId())
		{
			valid = true;
			child = &children[i];
			return child;
		}
	}
	valid = false;
	return child;
}

Device* Router::findDevice(std::string devId, bool &valid)
{
	//traverse each LAN
	Device* childDev = NULL;
	LAN* childLAN = NULL;

	for( int i=0; i < children.size(); i++)
	{
		childLAN = &children[i];
		childDev = childLAN->find(devId, valid);
		if(valid)
		{
			return childDev;
		}
	}
	return childDev;
}