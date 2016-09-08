#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string; 
#include <fstream>
using std::ifstream; using std::ofstream;
#include <vector>
using std::vector;
#include <map>
using std::map; using std::pair; using std::multimap;
#include <sstream>
using std::stringstream;

#include "ambig_scope.hpp"

void print_ambig_scope(multimap<vector<string>, 
	vector<vector<string>>>ambig){
	ofstream out_file;
	out_file.open("DRT.txt");
	stringstream writer;
	
	vector<string> elements;
	for (multimap<vector<string>, vector<vector<string>>>::iterator iter = 
		ambig.begin(); iter != ambig.end(); iter++){
			//cout<<endl<<"Ambiguous Scope Quantifier: ";
			writer << "Ambiguous Scope Quantifier: "; 
			out_file << writer.str();
			writer.str("");
			
			for (unsigned int i = 0; i < iter->first.size(); i++){
				writer<<iter->first[i] << " ";
				out_file << writer.str();
				writer.str("");
				//cout<<iter->first[i] << " ";
				
			}
			//cout<<endl<<"Ambiguous Scope: ";
			writer << endl << "Ambiguous Scope: "; 
			out_file << writer.str();
			writer.str("");
			for (unsigned int i = 0; i < iter->second.size(); i++){
				elements = iter->second[i];
				for (unsigned int j = 0; j < elements.size(); j++){
					//cout<<elements[j]<<" ";
					writer << elements[j] << " ";
					out_file << writer.str();
					writer.str("");
			    }
			    if (i != iter->second.size()-1){
					//cout<<", ";
					writer << ", ";
					out_file << writer.str();
					writer.str("");
				}
			}
			writer << endl << endl;
			out_file << writer.str();
			writer.str("");
		}
}
