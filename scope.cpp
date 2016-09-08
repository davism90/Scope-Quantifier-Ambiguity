#include <iostream>
using std::cout; using std::endl;
#include <string>
 using std::string; 
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector; 
#include "parser.hpp"
#include "scope.hpp"

void NP_NODE (string &quantifier_nodes, string &all_nodes, string from,
string to){
		size_t find_NP = all_nodes.find(from);
		size_t find_N = all_nodes.find(to);
		size_t find_difference_bw_N_NP = 0;
		
			find_NP = all_nodes.find(from);
			find_N = all_nodes.find(to);
			find_difference_bw_N_NP = find_N-find_NP; 
			string NP_node = all_nodes.substr(find_NP, 
				find_difference_bw_N_NP+3);
			quantifier_nodes += NP_node;
			all_nodes.erase(0, find_N);
}

vector<string> list_of_quantifiers (string tree_nodes){
	
	tree_nodes = reverse_string (tree_nodes);
	string tree_node_strings, DP_node;
	vector<string> quantifiers;

	size_t find_DP = tree_nodes.find("[DP]");
	size_t find_NP = tree_nodes.find("[NP]");
	size_t find_N = tree_nodes.find("[N]");
	//size_t find_Ad = tree_nodes.find("[A]");
	
	if(tree_nodes[1] =='D'){
		while (find_DP != string::npos){
			find_DP = tree_nodes.find("[DP]");
			find_NP = tree_nodes.find("[NP]");
			find_N = tree_nodes.find("[N]");
			DP_node = tree_nodes.substr(find_DP, find_N+3);
			tree_nodes.erase(0, DP_node.size());
			
			size_t find_ADJ = DP_node.find("[A]");
			if (find_ADJ != string::npos){
				DP_node.replace(find_ADJ, 3, " ");
			}
			tree_node_strings += DP_node;
			
			//if there is a NP only in DP
			while (find_NP != string::npos){
				NP_NODE(tree_node_strings, tree_nodes, "[NP]", "[N]"); 
				find_NP = tree_nodes.find("[NP]");
				find_N = tree_nodes.find("[N]");
			}
			
			find_DP = tree_nodes.find("[DP]");
			find_NP = tree_nodes.find("[NP]");
			find_N = tree_nodes.find("[N]");
			tree_nodes.erase(0, find_DP);
		}
	}
	
	if (tree_nodes[1] == 'N'){
		while (find_NP != string::npos){
			NP_NODE(tree_node_strings, tree_nodes, "[NP]", "[N]");
			find_NP = tree_nodes.find("[NP]");
			find_N = tree_nodes.find("[N]");
		}
	}
	quantifiers.push_back(tree_node_strings);
	return quantifiers;
}

vector<string> quantifier(string outer_scope){
	
	string new_sentence, hold;
	vector<string> NP_DP_vector;
	
	new_sentence = reverse_string(outer_scope);
	if (new_sentence != ""){
		size_t find=new_sentence.find(' ');
		if (find != string::npos){
			hold = new_sentence.substr(0, find);
			new_sentence.erase(0, hold.size() + 1);
			NP_DP_vector = list_of_quantifiers(hold);
		}
	}
	
	return NP_DP_vector;
}

vector<string> scope(vector<string>& parsed_strings)
{
	vector <string> parsed_vector, return_vector; 
	
	for (size_t i = 0; i < parsed_strings.size(); i++){
		if (parsed_strings[i] != ""){
			parsed_vector = quantifier(parsed_strings[i]);
			for (size_t i = 0; i < parsed_vector.size(); i++){
				return_vector.push_back(parsed_vector[i]);
			}
		}
		else{
			continue;
		}
	}
	
	return return_vector;
}
