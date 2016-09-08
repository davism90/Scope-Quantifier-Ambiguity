#ifndef supervised_h
#define supervised_h

#include <iostream>
using std::cout; using std::endl;
#include <string>
 using std::string; using std::stol;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector; 
#include <algorithm>
using std::transform; using std::find;
#include <map>
using std::map; using std::pair; using std::multimap;

map <string, vector<string>> open_file();

#endif
