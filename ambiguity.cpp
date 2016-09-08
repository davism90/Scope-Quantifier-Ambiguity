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
using std::map; using std::pair;
#include <sstream>
using std::stringstream;

#include "ambiguity.hpp"

void lower(string &word){
	for (unsigned int count = 0; count < word.size(); count++){ 
		if (isalpha(word[count])){
			word[count] = tolower(word[count]);
		}
	}
}

vector<string> existential(){
	string uni[] = {"some", "any"};
	vector<string> existential_scope (uni, uni + 1);
	
	return existential_scope;
}

vector<string> semi_univ_scope(){
	string uni[] = {"a few", "many", "some", "several",
		"more", "most", "none", "a"};
	vector<string> semi_universal_scope (uni, uni + 7);
	
	return semi_universal_scope;
}

vector<string> universal_scope(){
	string uni[] = {"every", "all", "none"};
	vector<string> universal_scope (uni, uni + 2);
	
	return universal_scope;
}

vector<string> anaphor(){
	string uni[] = {"it", "this", "him", "her", "that", "she", "he"};
	vector<string> anaphor_scope (uni, uni + 6);
	
	return anaphor_scope;
}

vector<string> determiner_scope(){
	string broad[] = {"the", "a"};
	vector<string> determine_scope (broad, broad + 2);
	
	return determine_scope;
}

vector<string> numeric_scope(){
	string numer[] = {"one", "two", "thr", "fou", "fiv",
		"six", "sev", "eig", "nin", "ten", "ele", "twe", "thi", "fif"};
	vector<string> numeric (numer, numer + 14);

	return numeric;
}

string check_type(string determiner){
	vector <string> existential_scope_list = existential();
	vector <string> determiner_scope_list = determiner_scope();
	vector <string> numeric_scope_list = numeric_scope();
	vector <string> universal_scope_list = universal_scope();
	vector <string> semi_universal_scope_list = semi_univ_scope();
	vector <string> anaphor_scope_list = anaphor();
	long flag = 0;
	string numeric_determiner;
	//use to make a map of the words to their types
	
	if (determiner != ""){
		
		for (unsigned int i = 0; i < existential_scope_list.size(); i++){
			if (existential_scope_list[i] == determiner){
				return "existential";
			}
		}	
		for (unsigned int i = 0; i < universal_scope_list.size(); i++){
			if (universal_scope_list[i] == determiner){
				return "universal";
			}
		}	
		
		for (unsigned int i = 0; i < anaphor_scope_list.size(); i++){
			if (anaphor_scope_list[i] == determiner){
				return "anaphor";
			}
		}	
		
		for (unsigned int i = 0; i < determiner_scope_list.size(); i++){ 
			if (determiner_scope_list[i] == determiner){
				return "determiner";
			}
		}
		for (unsigned int i = 0; i < semi_universal_scope_list.size();
			i++){ 
			if (semi_universal_scope_list[i] == determiner){
				return "semi_univ";
			}
		}
		for (unsigned int i = 0; i < numeric_scope_list.size(); i++){ 
			numeric_determiner = numeric_scope_list[i];
			for (unsigned int j = 0; j < 4; j++){
				if (numeric_determiner[j] != determiner[j]){
					flag += 1;
				}
			}
			if (flag == 0){
				return "numeric";
			}
		}
	}

	return ""; 
}

map<vector<string>, string> determine_types(vector<string>& 
	quantified_scope)
{
	vector<string> ambiguous_or_not, copy_quantified_scope, N_D_vector;
	string hold, scope, determiner, noun, type, count_string;
	map <vector<string>, string> scope_and_scope_type;
	long flag = 0, sentence_count = 0;
	stringstream ss;
	
	copy_quantified_scope = quantified_scope;
	
	for (size_t i = 0; i < copy_quantified_scope.size(); i++){
		scope=copy_quantified_scope[i];;
		size_t find_first, find_D, find_second;
		if (i != copy_quantified_scope.size()){
			while (scope.size() != 0){
				find_first = scope.find("[DP]");
				find_second = scope.find("[NP]");
				if (find_first != string::npos && find_second != 
					string::npos){
					find_D = scope.find("[D]");
					determiner = scope.substr(find_first+4, find_D-4);
					scope.erase(0, find_D+3);
					find_D = scope.find("[N]");
					noun = scope.substr(0, find_D);
					scope.erase(0, find_D+3);
					lower(noun);
					lower(determiner);
					type = check_type(determiner);
					sentence_count += 1;
					ss << sentence_count;
					type += ss.str();
					ss.str("");
					N_D_vector.push_back(determiner);
					N_D_vector.push_back(noun);
					scope_and_scope_type.insert(pair<vector<string>, 
						string > (N_D_vector, type));
					N_D_vector.clear();
					flag+=1;
				}
				
				if (find_first != string::npos && find_second == 
					string::npos){
					find_D = scope.find("[D]");
					determiner = scope.substr(find_first+4, find_D-4);
					scope.erase(0, find_D+3);
					find_D = scope.find("[N]");
					noun = scope.substr(0, find_D);
					scope.erase(0, find_D+3);
					lower(noun);
					lower(determiner);
					type = check_type(determiner);
					sentence_count += 1;
					ss << sentence_count;
					type += ss.str();
					ss.str("");
					N_D_vector.push_back(determiner);
					N_D_vector.push_back(noun);
					scope_and_scope_type.insert(pair<vector<string>, 
						string > (N_D_vector, type));
					N_D_vector.clear();
					flag+=1;
				}
				
				if (find_first == string::npos && find_second != 
					string::npos){
					find_D = scope.find("[N]");
					noun = scope.substr(find_second+4, find_D-4);
					lower(noun);
					N_D_vector.push_back(noun);
					if (flag == 0){
						type = "anaphor";
						sentence_count += 1;
						ss << sentence_count;
						type += ss.str();
						ss.str("");
						scope_and_scope_type.insert(pair<vector<string>, 
							string > (N_D_vector, type));
						N_D_vector.clear();
						scope.erase(find_second, find_D+4);
					}
					
					else{
						type = check_type(noun);
						sentence_count += 1;
						ss << sentence_count;
						type += ss.str();
						ss.str("");
						scope_and_scope_type.insert(pair<vector<string>, 
							string > (N_D_vector, type));
						N_D_vector.clear();
						scope.erase(find_second, find_D+4);
						flag = 0;
					}	
				}
			}
		}
	}
	
	return scope_and_scope_type;
}
