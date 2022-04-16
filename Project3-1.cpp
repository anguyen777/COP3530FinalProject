//============================================================================
// Name        : DSAProject3.cpp
// Author      : Ai-Linh
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>
#include <string>


using namespace std;

class AdjacencyList {

struct actor {
	string name;
	string movie;
	int weight;
};


private:

	// map of actors/actresses name that maps to the names that it points to, weights are movie names
	map<string, vector<pair<string,string> > > graph;

	map<string, vector<actor> > graph2;


public:

	AdjacencyList(); //constructor
	~AdjacencyList(); //destructor


	void insert(string actor_1_name, string actor_2_name, string actor_3_name, string movie); 

	void insert2(string actor_1_name, string actor_2_name, string actor_3_name, string movie); 

	
	void display();
	void display2();


};


AdjacencyList::AdjacencyList(){}
AdjacencyList::~AdjacencyList(){}

void AdjacencyList::insert(string actor_1_name, string actor_2_name, string actor_3_name, string movie){


		if(graph.find(actor_1_name) == graph.end()){ //if the current actor is not found in the map
			vector<pair<string,string> > temp;
			temp.push_back(make_pair(actor_2_name,movie));
			temp.push_back(make_pair(actor_3_name,movie));
			graph[actor_1_name] = temp;
		
		}
		else{
			graph[actor_1_name].push_back(make_pair(actor_2_name,movie));
			graph[actor_1_name].push_back(make_pair(actor_3_name,movie));

		}

		if(graph.find(actor_2_name) == graph.end()){ //if the current actor is not found in the map
			vector<pair<string,string> > temp;
			temp.push_back(make_pair(actor_1_name,movie));
			temp.push_back(make_pair(actor_3_name,movie));
			graph[actor_2_name] = temp;
		}
		else{
			graph[actor_2_name].push_back(make_pair(actor_1_name,movie));
			graph[actor_2_name].push_back(make_pair(actor_3_name,movie));

		}

		if(graph.find(actor_3_name) == graph.end()){ //if the current actor is not found in the map
			vector<pair<string,string> > temp;
			temp.push_back(make_pair(actor_1_name,movie));
			temp.push_back(make_pair(actor_2_name,movie));
			graph[actor_3_name] = temp;
		}
			else{
			graph[actor_3_name].push_back(make_pair(actor_1_name,movie));
			graph[actor_3_name].push_back(make_pair(actor_2_name,movie));

		}



}	



void AdjacencyList::insert2(string actor_1_name, string actor_2_name, string actor_3_name, string movie){

		actor actor1;
		actor1.name = actor_1_name;
		actor1.movie = movie;
		actor1.weight = 1;

		actor actor2;
		actor2.name = actor_2_name;
		actor2.movie = movie;
		actor2.weight = 2;

		actor actor3;
		actor3.name = actor_3_name;
		actor3.movie = movie;
		actor3.weight = 3;



		if(graph2.find(actor_1_name) == graph2.end()){ //if the current actor is not found in the map
			vector<actor> temp;
			temp.push_back(actor2);
			temp.push_back(actor3);
			graph2[actor_1_name] = temp;
		
		}
		else{
			graph2[actor_1_name].push_back(actor2);
			graph2[actor_1_name].push_back(actor3);

		}


		if(graph2.find(actor_2_name) == graph2.end()){ //if the current actor is not found in the map
			vector<actor> temp;
			temp.push_back(actor1);
			temp.push_back(actor3);
			graph2[actor_2_name] = temp;
		
		}
		else{
			graph2[actor_2_name].push_back(actor1);
			graph2[actor_2_name].push_back(actor3);

		}

		if(graph2.find(actor_3_name) == graph2.end()){ //if the current actor is not found in the map
			vector<actor> temp;
			temp.push_back(actor1);
			temp.push_back(actor2);
			graph2[actor_3_name] = temp;
		
		}
		else{
			graph2[actor_3_name].push_back(actor1);
			graph2[actor_3_name].push_back(actor2);

		}


}	



void AdjacencyList::display(){

	for(const auto& elem: graph){

		cout << elem.first << " ";

		vector<pair<string, string> > inner = elem.second;


		cout << "edges:" ;
		for(int i = 0; i < inner.size(); i++){

			cout  << inner.at(i).first<< " " << inner.at(i).second 
			<< endl;

		}
	}

		

//	cout << "graph size" << graph.size()<<endl; debugging



}


void AdjacencyList::display2(){

	for(const auto& elem: graph2){

		cout << "node: " << elem.first << " ";

		vector<actor> inner = elem.second;

		cout << "edges: " ;
		for(int i = 0; i < inner.size(); i++){
			cout  << inner.at(i).name << " " << inner.at(i).weight << " " << inner.at(i).movie  << endl;

		}
		
	}

		

//	cout << "graph size" << graph.size()<<endl; debugging


	// cout << graph2["tom hanks"].at(0).name;


	// cout << "graph size: " << graph2.size() << endl;







}


int main() {


	AdjacencyList graph;
	AdjacencyList graph2;

	vector<vector<string> > content;
	vector<string> row;
	string line, word;


	// file pointer
	ifstream file;

	// opens an existing csv file or creates a new file.
	file.open("Movies.csv", ios::in);

	//int count = 0;
	if(file.is_open())
	{

	
		while(getline(file, line))
		{
			row.clear();
			stringstream str(line);

			while(getline(str, word, ',')){

				row.push_back(word);
			

			}
		
				content.push_back(row);
		
				//lowercasing the input for consistency
				transform(row[0].begin(), row[0].end(), row[0].begin(), ::tolower);
				transform(row[1].begin(), row[1].end(), row[1].begin(), ::tolower);
				transform(row[2].begin(), row[2].end(), row[2].begin(), ::tolower);
				transform(row[3].begin(), row[3].end(), row[3].begin(), ::tolower);


				//graph.insert(row[0],row[1],row[2],row[3]);
				
				graph2.insert2(row[0],row[1],row[2],row[3]);

		}
			
		
		file.close();
	}


	else{
		cout<<"Could not open the file\n";
	}





	// debugging
	// for(int i=0;i<content.size();i++)
	// {
	// 	for(int j=0;j<content[i].size();j++)
	// 	{
	// 		cout<< " " << content[i][j];
	// 	}
	// 	cout<<"\n";
	// }




	//graph.display();
	graph2.display2();



	return 0;

}












