#include <iostream>
using std::cout; using std::endl;
#include <string>
 using std::string; 
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector; 
#include "parser.hpp"

void VP_TP_parsing (string &type_string, string &type_parsed_sentence,
string &new_sentence, string &hold, string minor, string major){
	size_t find;
	string substring;
	
	find = new_sentence.find(' ');
	substring = new_sentence.substr(0, find);
	hold += substring;
	new_sentence.erase(0, substring.size()+1);
	type_string += minor;
	find = new_sentence.find(' ');
	substring = new_sentence.substr(0, find);
	hold += substring;
	new_sentence.erase(0, substring.size()+1);
	hold += major;
	type_parsed_sentence+=hold;
	type_string += major;
	find = new_sentence.find(' ');
	substring = new_sentence.substr(0, find);
	hold = substring;
}


void regular_parsing (string &type_string, string &type_parsed_sentence,
string &new_sentence, string &hold, string major){
	size_t find;
	string substring;
	
	find = new_sentence.find(' ');
	substring = new_sentence.substr(0, find);
	new_sentence.erase(0, substring.size()+1);
	hold += substring;
	hold += major;
	type_parsed_sentence += hold;
	type_string += major;
}

void single_parsing(string &type_string, string &hold, 
string &type_parsed_sentence, string major){
	hold += major;
	type_parsed_sentence += hold;
	type_string += major;
}

void embedded_parsing(string &type_string, string &type_parsed_sentence,
string &new_sentence, string &hold, string minor, string major){
	size_t find;
	string substring;
	
	find = new_sentence.find(' ');
	substring = new_sentence.substr(0, find);
	hold += substring;
    new_sentence.erase(0, substring.size()+1);
	type_string += minor;
	find = new_sentence.find(' ');
	substring = new_sentence.substr(0, find);
	hold += substring;
	new_sentence.erase(0, substring.size()+1);
	hold += major;
	type_parsed_sentence += hold;
	type_string += major;
	find = new_sentence.find(' ');
	substring = new_sentence.substr(0, find);
	hold=substring;
	new_sentence.erase(0, hold.size()+1);
}

string copy_check(string &new_sentence){
	size_t find;
	string substring;
	
	string copy_sentence = new_sentence;
	find = copy_sentence.find(' ');
	substring = copy_sentence.substr(0, find);
	copy_sentence.erase(0, substring.size()+1);
	
	return copy_sentence;
}

string reverse_string(string forwards){
	string backwards;
	
	for (string::reverse_iterator rev =forwards.rbegin();
	rev!=forwards.rend(); ++rev){
		backwards += *rev;
	}
	
	return backwards;
}

string parse_types(string parsed_sentence){
	
	string new_sentence, type_parsed_sentence, hold, substring, reversed,
	type_string, copy;
	
	new_sentence = reverse_string(parsed_sentence);
	
	while (new_sentence != ""){
		if (new_sentence[0]==']'){
			size_t find=new_sentence.find(' ');
			if (find != string::npos){
				hold=new_sentence.substr(0, find);
				new_sentence.erase(0, hold.size()+1);
				if (hold[1]=='N' && new_sentence[1] != 'D' && 
				new_sentence[1] != 'A'){
					single_parsing(type_string, hold, 
						type_parsed_sentence, "]PN[");
				}
				if (hold[1] =='N' && new_sentence[1] == 'D'){
					copy = copy_check(new_sentence);
					if (copy[1] != 'P' && copy[1] != 'D'){
						regular_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "]PD[");
					}
					if (copy[1] == 'P'){
						embedded_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "]PD[", "]PP[");
					}	
					if (copy[1] == 'D'){
						embedded_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "", "]PD[");
					}
				}
				if (hold[1] == 'N' && new_sentence[1] == 'V'){
					regular_parsing(type_string, type_parsed_sentence,
						new_sentence, hold, "]PN[");
				}
				if (hold[1] == 'N' && new_sentence[1] == 'A'){
					copy = copy_check(new_sentence);
					if (copy[1] !='D'){
						regular_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "]PN[");
					}
					else{
						embedded_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "]PN[", "]PD[");
					}
				}
				if (hold[1] == 'V' && new_sentence[1] != 'T'){
					single_parsing(type_string, hold, 
						type_parsed_sentence, "]PV[");
				}
				
				if (hold[1] == 'V' && new_sentence[1] == 'T'){
					copy = copy_check(new_sentence);
					if (copy[1]!='V'){
						regular_parsing(type_string, type_parsed_sentence,
						new_sentence, hold, "]PV[");
					}
					else{
						VP_TP_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "]PT[", "]PV[");
						}	
				}
				
				if (hold[1] == 'T' && new_sentence[1] == 'V'){
					copy = copy_check(new_sentence);
					if (copy[1]!='T'){
						regular_parsing(type_string, type_parsed_sentence,
						new_sentence, hold, "]PV[");
					}
					else{
						VP_TP_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "]PV[", "]PT[");
						}	
				}
				if (hold[1] == 'A' && new_sentence[1] == 'V'){
					copy = copy_check(new_sentence);
					if (copy[1]!='A'){
						regular_parsing(type_string, type_parsed_sentence,
						new_sentence, hold, "]PV[");
					}
					else{
						VP_TP_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "]PV[", "]PA[");
						}	
				}
				if (hold[1] == 'A' && new_sentence[1] == 'T'){
					copy = copy_check(new_sentence);
					if (copy[1]!='V'){
						regular_parsing(type_string, type_parsed_sentence,
						new_sentence, hold, "]PT[");
					}
					else{
						VP_TP_parsing(type_string, type_parsed_sentence,
							new_sentence, hold, "]PT[", "]PV[");
						}	
				}
				if(hold[1] == 'P' && new_sentence[1] == 'N'){
					single_parsing(type_string, hold, 
						type_parsed_sentence, "]PP[");
					//regular_parsing(type_string, type_parsed_sentence,
						//new_sentence, hold, "]PP[");
				}
				if(hold[1] == 'P' && new_sentence[1] == 'V'){
					single_parsing(type_string, hold, 
						type_parsed_sentence, "]PP[");
					//regular_parsing(type_string, type_parsed_sentence,
						//new_sentence, hold, "]PV[");
				}
				if(hold[1] == 'C'){
					continue; //resolution.cpp flag += 1, add to 
					//map and compare later to get values I NEED COPIES
					//JFC
				}
			}
		}
		else{
			if (hold[1] == 'N' && new_sentence == ""){
				single_parsing(type_string, hold, 
					type_parsed_sentence, "]PN[");
				new_sentence = "";
				}
				if (hold[1] == 'V' && new_sentence == ""){
				single_parsing(type_string, hold, 
					type_parsed_sentence, "]PV[");
				new_sentence = "";
				}
				if (hold[1] == 'D' && new_sentence == ""){
				single_parsing(type_string, hold, 
					type_parsed_sentence, "]PD[");
				new_sentence = "";
				}
			new_sentence = "";
		}	
	}
	if (type_parsed_sentence != ""){
		type_parsed_sentence += "   ]S[";
		type_parsed_sentence += "::" + type_string;
	}
	reversed = reverse_string(type_parsed_sentence);
	return reversed;
}

vector <string> parse(string& filename)
{
	ifstream file (filename.c_str());
	string sentence, parsed;
	vector <string> sentences;
	
	while (!file.eof()){
		getline(file, sentence, '.');
		if (sentence[0] == ' '){
			sentence.erase(sentence.begin()+0);
			}
		if (sentence != ""){
			sentence=parse_types(sentence);
			sentences.push_back(sentence);
		}
	}
	return sentences;
}
