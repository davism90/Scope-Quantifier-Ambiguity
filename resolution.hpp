#ifndef resolution_hpp
#define resolution_hpp

#include <iostream>
using std::cout; using std::endl;
#include <string>
 using std::string; 
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector; 
#include <algorithm>
using std::transform; using std::find;
#include <map>
using std::map; using std::pair; using std::multimap;

multimap<vector<string>, vector<vector<string>>> 
	final_scope(vector<vector<vector<string>>>);
	
long gender_compare(map<string, vector<string>>, vector<string>, 
	vector<string>);

long distance_compare(long, long);

long noun_compare(vector<string>, vector<string>);

long type_compare (vector<string>);

multimap<vector<string>, vector<vector<string>>> 
	compare(map<vector<string>, string>, map<string, vector<string>>);

#endif
