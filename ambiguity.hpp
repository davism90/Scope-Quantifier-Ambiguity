#ifndef ambiguity_hpp
#define ambiguity_hpp

#include <string>
using std::string; 
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <map>
using std::map; using std::pair;

vector <string> existential();

vector <string> semi_univ_scope();

vector <string> universal_scope();

vector <string> anaphor();

vector<string> determiner_scope();

vector<string> numeric_scope();

string check_type(string, string);

map<vector<string>, string> determine_types(vector<string> &);


#endif
