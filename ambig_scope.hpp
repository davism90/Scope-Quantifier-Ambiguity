#ifndef ambig_scope_hpp
#define ambig_scope_hpp

#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string; 
#include <fstream>
using std::ifstream; 
#include <vector>
using std::vector;
#include <map>
using std::map; using std::pair; using std::multimap;

void print_ambig_scope(multimap<vector<string>, vector<vector<string>>>);

#endif
