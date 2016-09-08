#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
using std::string; 
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;

void VP_TP_parsing (string &, string &, string &, string &, string, 
	string);

void regular_parsing (string &, string &, string &, string &, string);

void single_parsing(string &, string &, string &, string); 

void embedded_parsing(string &, string &, string &, string &, string, 
string);

string copy_check(string &);

string reverse_string(string);

string parse_types(string);

vector <string> parse(string &);

#endif
