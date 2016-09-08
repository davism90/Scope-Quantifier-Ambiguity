#ifndef scope_hpp
#define scope_hpp

#include <string>
using std::string; 
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;

void NP_NODE (string &, string &, string, string);

vector<string> list_of_quantifiers (string);

vector<string> quantifier(string);

vector<string> scope(vector<string> &);

#endif
