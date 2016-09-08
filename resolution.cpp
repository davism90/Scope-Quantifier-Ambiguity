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

#include "resolution.hpp"
#include "ambig_scope.hpp"

multimap<vector<string>, vector<vector<string>>> 
	final_scope(vector<vector<vector<string>>> scope){
	vector<vector<string>> pair_of_strings, temp_pair_of_strings, 
		paired;
	vector<string> one_string, one_string_temp;
	multimap <vector<string>, vector<vector<string>>> final_result;
	pair <vector<string>, vector<vector<string>>> map_pair;
	vector<string> words;
	unsigned int k=0;
	
	for (unsigned int i = 0; i < scope.size(); i++){
		pair_of_strings = scope[i];
		for (unsigned int j = 0; j < pair_of_strings.size(); j++){
			if (final_result.find(pair_of_strings[0]) == 
					final_result.end()){
					paired.push_back(pair_of_strings[0]);
					paired.push_back(pair_of_strings[1]);
				while (k < scope.size()-1){
					temp_pair_of_strings = scope[k+1];
					for (unsigned int a = 0; a < 
						pair_of_strings.size()-1; a++){
						if (pair_of_strings[0] == 
							temp_pair_of_strings[0]){
								paired.push_back(temp_pair_of_strings[1]);
						}
					}
					k++;
				}
				map_pair = make_pair(pair_of_strings[0], paired);
				final_result.insert(map_pair);
			}
		}
	}

	return final_result;	
} 

long gender_compare(map<string, vector<string>>coref, vector<string> a,
	vector <string> b){
		map <string, vector<string>>::iterator it;
		vector <string> pronouns;
		long value = 0;
		size_t found;
		
		if (a.size() >= b.size()){
			for (it = coref.begin(); it!=coref.end(); it++){
				for (unsigned int i = 0; i < a.size(); i++){
					found = a[i].find(it->first);
					if (found != string::npos){
						pronouns = it->second;
						for (unsigned int j = 0; j < b.size(); j++){
							for (unsigned int k = 0; k < 
								pronouns.size(); k++){
								found = b[j].find(pronouns[k]);
								if (found != string::npos){
									value = 1;
								}
							}
						}
					}
				}
			}
		}
		
		if (a.size() < b.size()){
			for (it = coref.begin(); it!=coref.end(); it++){
				for (unsigned int i = 0; i < b.size(); i++){
					found = b[i].find(it->first);
					if (found != string::npos){
						pronouns = it->second;
						for (unsigned int j = 0; j < a.size(); j++){
							for (unsigned int k = 0; k < 
								pronouns.size(); k++){
								found = a[j].find(pronouns[k]);
								if (found != string::npos){
									value = 1;
								}
							}
						}
					}
				}
			}
		}
	
	return value;
}
 
long distance_compare(long dist_a, long dist_b){
	
	if (dist_b - dist_a == 0){
		return 2;
	}
	if (dist_b - dist_a > 0 && dist_b - dist_a < 2 ){
		return 1;
	}
	else{
		return 0;
	}
	
	return 0;
	
} 
 
long noun_compare(vector<string> noun_list_a, 
	vector<string> noun_list_b){
		
	string a, b;
	long value = 0;
	
	if (noun_list_a.size() < noun_list_b.size()){
		for (unsigned int i = 0; i < noun_list_a.size(); i++){
			a = noun_list_a[i];
			for (unsigned int j = 0; j< noun_list_b.size(); j++){
				size_t found = noun_list_a[i].find(noun_list_b[j]);
				if (found != string::npos){
					value += 2;
				}
				size_t found_2 = noun_list_b[j].find(noun_list_a[i]);
					if (found_2 != string::npos){
					value += 2;
				}
			}
		}
	}
	
	if (noun_list_b.size() <= noun_list_a.size()){
		for (unsigned int i = 0; i < noun_list_b.size(); i++){
			b = noun_list_b[i];
			for (unsigned int j = 0; j< noun_list_a.size(); j++){
				size_t found = noun_list_b[i].find(noun_list_a[j]);
				if (found != string::npos){
					value += 2;
				}
				size_t found_2 = noun_list_a[i].find(noun_list_b[j]);
					if (found_2 != string::npos){
					value += 2;
				}
			}
		}
	}
	
	return value;
	
} 
 
long type_compare (vector<string> quantifier){
	string scope_a, scope_b;
	
	long value = 0;
	
	for (unsigned int i = 0; i < quantifier.size(); i++){
		
		if (quantifier.size() > 1){
			scope_a = quantifier[i].substr(0, quantifier[i].size()-1);
			scope_b = quantifier[i+1].substr(0, 
				quantifier[i+1].size()-1);
		}

		if (scope_a == "semi_univ"){
			if (scope_b == "numeric"){
				value += 2;
			}
			if (scope_b == "universal"){
				value += 2;
			}
		}
		if (scope_a == "existential"){
			if (scope_b == "existential"){
				value -= 1;
			}
			if (scope_b == "universal"){
				value += 1;
			}
			
			if (scope_b == "numeric"){
				value += 1;
			}
			
			if (scope_b == "determiner"){
				value += 1;
			}
			if (scope_b == "anaphor"){
				value += 2;
			}
		}
		
		if (scope_a == "numeric"){
			if (scope_b == "numeric"){
				value += 2;
			}
			if (scope_b == "semi_univ"){
				value += 2;
			}
			if (scope_b == "universal"){
				value += 2;
			}
		}
		
		if (scope_a == "universal"){
			if (scope_b == "universal"){
				value += 2;
			}
			if (scope_b == "anaphor"){
				value += 1;
			}
			if (scope_b == "numeric"){
				value += 2;
			}
			if (scope_b == "semi_univ"){
				value += 2;
			}
			if (scope_b == "determiner"){
				value += 2;
			}
		}
		
		i++;
	}
	return value;
}
 
multimap<vector<string>, vector<vector<string>>> 
	compare(map<vector<string>, string> scope_map, map<string,
	vector<string>> gender){
	
	vector <string> quantifiers, x_q, y_q, new_quantifier;
	vector < vector <string> > comparer, new_comparer, x_c, y_c;
	long loop_count = 0, type_value = 0, x_value = 0, y_value = 0, 
		count_distance = 0, distance, first_check = 0;
	vector<vector<vector<string>>> scope, ambig_scope;
	string distance_1, distance_2;
	
	//first -> sentences, second-> type
	for(map< vector<string>, string>::iterator it = scope_map.begin();
		it != scope_map.end(); it++){	 
		if (loop_count < 2){
			comparer.push_back(it->first);
			quantifiers.push_back(it->second);
			count_distance += 1;
		}
		
		if (loop_count == 2){
			first_check = 0;
			loop_count = 0;
			//two scopes to compare
			type_value += type_compare(quantifiers);
			
			while (type_value >= 1){
				long scope_dist_a;
				long scope_dist_b;
				string::size_type sz;
				type_value = 0;
				if (it != scope_map.end()){
					
					if(first_check < 1){
						x_q.push_back(quantifiers[0]);
						x_c.push_back(comparer[0]);
						x_q.push_back(quantifiers[1]);
						x_c.push_back(comparer[1]);						
						x_value = type_compare(x_q);
					}
					
					if (first_check > 1){

						x_q.push_back(quantifiers[0]);
						x_c.push_back(comparer[0]);
						y_q.push_back(quantifiers[1]);
						y_c.push_back(comparer[1]);
						quantifiers.clear();
						comparer.clear();
										
						quantifiers.push_back(it -> second);
						comparer.push_back(it -> first);
						
						x_q.push_back(quantifiers[0]);
						x_c.push_back(comparer[0]);
						y_q.push_back(quantifiers[0]);
						y_c.push_back(comparer[0]);
						
						x_value = type_compare(x_q);
						y_value = type_compare (y_q);
					}
					
					if (x_value > y_value && x_value != 0){
						//scope are compatible but x > y
						distance_1 = x_q[0];
						distance_2 = x_q[1];
						scope_dist_a = ((static_cast<long>
							(distance_1[distance_1.size()-1]))-48);
						scope_dist_b = ((static_cast<long>
							(distance_2[distance_2.size()-1]))-48);
						distance = 
							distance_compare(scope_dist_a, scope_dist_b);
						type_value += x_value;
						type_value += noun_compare (x_c[0], x_c[1]);
						type_value += distance;
						type_value += gender_compare(gender, x_c[0],
							x_c[1]);
						
						//if type value is high enough, add to scope
						if (type_value >= 5){
							if (first_check > 1){
								comparer.push_back(x_c[1]);
								quantifiers.push_back(x_q[1]);
							}
							type_value = 0;
							type_value += type_compare(quantifiers);
							count_distance += 1;
							new_comparer.push_back(x_c[0]);
							new_comparer.push_back(x_c[1]);
							// for troubleshooting:
							/*vector<string> temp;
							for (unsigned int i = 0; i < 
							 	new_comparer.size(); i++){
								temp = new_comparer[i];
								cout<<"Vector" << i << " :"<<endl;
								for(unsigned int j = 0; j 
								 	< temp.size(); j++){
									cout<<" Stuff: " << temp[j] << " " ;
								}
								cout<<endl;
							}*/
							
							
							scope.push_back(new_comparer);
						}
						
						if (type_value >=3 && type_value < 5){
							if (first_check > 1){
								comparer.push_back(x_c[1]);
								quantifiers.push_back(x_q[1]);
							}
							type_value = 0;
							type_value += type_compare(quantifiers);
							count_distance += 1;
							new_comparer.push_back(x_c[0]);
							new_comparer.push_back(x_c[1]);
							// for troubleshooting:
							/*vector<string> temp;
							for (unsigned int i = 0; i < 
							 	new_comparer.size(); i++){
								temp = new_comparer[i];
								cout<<"Vector" << i << " :"<<endl;
								for(unsigned int j = 0; j 
								 	< temp.size(); j++){
									cout<<" Stuff: " << temp[j] << " " ;
								}
								cout<<endl;
							}*/
							
							
							ambig_scope.push_back(new_comparer);
						}
						
						
						else{
							x_q.clear();
							x_c.clear();
							y_c.clear();
							y_q.clear();
							type_value += type_compare(quantifiers);
							loop_count = 0;
							count_distance = 0;
							//not compatible with scope
						}
						
					}
					
					if (y_value >= x_value && y_value != 0){
						//scopes are compatible but y > x
						distance_1 = y_q[0];
						distance_2 = y_q[1];
						scope_dist_a = ((static_cast<long>
							(distance_1[distance_1.size()-1]))-48);
						scope_dist_b = ((static_cast<long>
							(distance_2[distance_2.size()-1]))-48);
						type_value += y_value;
						////should be y_c[0], y_c[1]
						type_value += noun_compare (y_c[0], y_c[1]);
						type_value += distance;
						type_value += gender_compare(gender, y_c[0], 
							y_c[1]);
						
						//if type value is high enough, add to scope
						if (type_value >= 5){
							if (first_check > 1){
								comparer.push_back(y_c[1]);
								quantifiers.push_back(y_q[1]);
							}
							type_value = 0;
							type_value += type_compare(quantifiers);
							count_distance += 1;
							new_comparer.push_back(y_c[0]);
							new_comparer.push_back(y_c[1]);
							scope.push_back(new_comparer);
							
						}
						
						if (type_value >= 3 && type_value < 5){
							if (first_check > 1){
								comparer.push_back(y_c[1]);
								quantifiers.push_back(y_q[1]);
							}
							type_value = 0;
							type_value += type_compare(quantifiers);
							count_distance += 1;
							new_comparer.push_back(y_c[0]);
							new_comparer.push_back(y_c[1]);
							ambig_scope.push_back(new_comparer);
							
						}
						else{
							//not compatible with scope/ambig
							x_q.clear();
							x_c.clear();
							y_c.clear();
							y_q.clear();
							type_value += type_compare(quantifiers);
							count_distance = 0;
						}
					} 
					if (first_check > 2){
						it++;
					}
					first_check += 2;
					x_q.clear();
					x_c.clear();
					y_c.clear();
					y_q.clear();
					new_comparer.clear();
				} 
				
			}
			count_distance = 0;
			quantifiers.clear();
			comparer.clear();
		}
		loop_count += 1;
		print_ambig_scope(final_scope(ambig_scope));
	}
	return final_scope(scope);
}
