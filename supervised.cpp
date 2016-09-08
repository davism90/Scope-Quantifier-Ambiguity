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
#include <utility>
using std::pair; using std::make_pair;

#include "supervised.h"



map<string, vector<string>> open_file(){
	
	string filename = "supervised_text.txt";
	string sentence, word, pronoun;
	vector<string> pronouns;
	long word_count = 0;
	ifstream file (filename.c_str());
	
	map<string, vector<string>>words_and_pronouns;
	
	
	while (!file.eof()){
		getline(file, sentence);
		for (unsigned int i = 0; i < sentence.size(); i++){
			if (word_count == 0 && sentence[i] != ' '){
				word += sentence[i];
			}
			if (word_count == 0 && sentence[i]  == ' '){
				word_count = 1;
			}
			
			if (word_count > 0 && sentence[i] != ' '){
				pronoun += sentence[i];
			}
			if (word_count > 0 && (sentence[i] == ' ' || i == 
				sentence.size()-1)){
				if (pronoun != ""){
					pronouns.push_back(pronoun);
					pronoun = "";
				}		
			}
		}
		
		pair<string, vector<string>> map_pair;
		map_pair = make_pair(word, pronouns);
		words_and_pronouns.insert(map_pair);

		pronouns.clear();
		word="";
		word_count = 0;
	}
	
	return words_and_pronouns;
}
