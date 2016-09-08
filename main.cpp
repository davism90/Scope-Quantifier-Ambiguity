#include <iostream>
using std::cout; using std::endl; using std::ios;
#include <string>
using std::string; 
#include <fstream>
using std::ifstream; using std::ofstream; 
#include <vector>
using std::vector;
#include <map>
using std::map; using std::pair; using std::multimap;
#include <sstream>
using std::stringstream;

#include "parser.hpp"
#include "scope.hpp"
#include "ambiguity.hpp"
#include "resolution.hpp"
#include "ambig_scope.hpp"
#include "supervised.h"

int main()
{
	/* this program expects a pre annotated text such as:
	 * Noun[N] adverb[T] verb[V] preposition[P] determiner[D] noun[N]
	 * conjunction[C] noun[N] verb [V].
	 * and includes a period at the end of each sentence, each sentence 
	 * be on a new line, and a space between the margin and the first 
	 * letter of the sentence. */
	ofstream out_file;
	out_file.open("DRT.txt", ios::app);
	stringstream writer;
	
	string filename= "semantics.txt";
	vector <string> sentences = parse(filename); //all parsed
	vector <string> quantifier_parsed = scope(sentences); //per sentence
	map<string, vector<string>>genders = open_file();
	map<vector <string>, string> scope_types = 
		determine_types(quantifier_parsed);
		
	multimap<vector<string>, vector<vector<string>>> final_scope = 
		compare(scope_types, genders);
	vector<string> elements;
	
	for (multimap<vector<string>, vector<vector<string>>>::iterator iter = 
		final_scope.begin(); iter != final_scope.end(); iter++){
		//cout<<endl<<"Definite Scope Quantifier: ";
		writer << "Definite Scope Quantifier: ";
		out_file << writer.str();
		writer.str("");
			
		for (unsigned int i = 0; i < iter->first.size(); i++){
			//cout<<iter->first[i] << " ";
			writer << iter->first[i] << " ";
			out_file << writer.str();
			writer.str("");
		}
			//cout<<endl<<"Definite Scope: ";
		writer << endl << "Definite Scope: ";
		out_file << writer.str();
		writer.str("");
			
		for (unsigned int i = 0; i < iter->second.size(); i++){
			elements = iter->second[i];
			for (unsigned int j = 0; j < elements.size(); j++){
				//cout<<elements[j]<<" ";
				writer << elements[j] << " ";
				out_file<<writer.str();
				writer.str("");
			   }
			   if (i != iter->second.size()-1){
					//cout<<", ";
					writer << ", ";
					out_file << writer.str();
					writer.str("");
				}
			}
			writer << endl << endl;
			out_file << writer.str();
			writer.str("");
			//cout<<endl;
		}
	
	for (size_t i = 0; i < sentences.size(); i++){
		if (sentences[i] != ""){
			//cout << "Sentences:  " << sentences[i] << endl;
			writer << "Sentences: " << sentences[i] << endl;
			out_file << writer.str();
			writer.str("");
		}
	}
	writer << endl; 
	out_file << writer.str();
	writer.str("");
	//cout << endl;
	
	for (size_t i = 0; i < quantifier_parsed.size(); i++){
		//cout << "Parsed Scope: " << quantifier_parsed[i] << endl;
		writer << "Parsed Scope: " << quantifier_parsed[i] << endl;
		out_file << writer.str();
		writer.str("");
		
	}
	writer << endl; 
	out_file << writer.str();
	writer.str("");
	//cout << endl;
	
	for(map< vector<string>, string>::iterator it = scope_types.begin();
		it != scope_types.end(); ++it){
			//cout<< "Scope->Type: ";
			writer << "Scope -> Type: ";
			out_file << writer.str();
			writer.str("");
			
			for (unsigned int i = 0; i < it->first.size(); i++){
				//cout<<it->first[i] << " ";
				writer << it->first[i] << " ";
				out_file<<writer.str();
				writer.str("");
			}
			writer << "-> " << it->second << endl;
			out_file << writer.str();
			writer.str("");
			//cout<<"-> " << it->second;
			//cout<<endl;
	}
	return 0;
}
