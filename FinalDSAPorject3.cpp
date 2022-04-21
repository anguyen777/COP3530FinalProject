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
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include <chrono>
#include <stdio.h>
using namespace std;
using namespace std::chrono;

class AdjacencyList {

struct actor {
	string name = "";
	string movie = "";
	int weight;
	actor(){}
	actor(string name, string movie, int weight) : 
	name(name), movie(movie), weight(weight) {}

};


private:
	// map of actors/actresses name that maps to the names that it points to, weights are movie names
	map<string, vector<actor> > graph;
	

public:
	AdjacencyList(); //constructor
	~AdjacencyList(); //destructor
	void insert(string actor_1_name, string actor_2_name, string actor_3_name, string movie); 
	void bfs(string src, string target);
	// shows breadth-first algorithm with movies included
	void betterbfs(string src, string dest);
    void dfs(string src, string dest);
    void getAdjacentActors(string src);
    void getActorMovies(string src);
    void getAdjActormovie(string src);
	int GetEdgeWeight(string src, string dest);
    void dijkstra(string src, string dest);
    void betterDij(string src, string dest);
	bool inGraph(string actor1, string actor2);

	struct comp{
		bool operator()(const pair<string, int>& lhs, const pair<string, int>& rhs) const {
			if(lhs.second == rhs.second) return lhs.first > rhs.first;
			else return lhs.second > rhs.second;
		}
	};


};


AdjacencyList::AdjacencyList(){}
AdjacencyList::~AdjacencyList(){}

bool AdjacencyList::inGraph(string actor1, string actor2){ //checks if both user-queried actors are in the graph

	if(graph.find(actor1)==graph.end()||graph.find(actor2)==graph.end()){ 
		return false;
	}
	else{
		return true;
	}

}


void AdjacencyList::insert(string actor_1_name, string actor_2_name, string actor_3_name, string movie){ 
	//inserts the tuple into the graph

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

		if(graph.find(actor_1_name) == graph.end()){ //if the current actor is not found in the map
			vector<actor> temp;
			temp.push_back(actor2);
			temp.push_back(actor3);
			graph[actor_1_name] = temp;
		
		
		}
		else{
			graph[actor_1_name].push_back(actor2);
			graph[actor_1_name].push_back(actor3);

		}

		if(graph.find(actor_2_name) == graph.end()){ //if the current actor is not found in the map
			vector<actor> temp;
			temp.push_back(actor1);
			temp.push_back(actor3);
			graph[actor_2_name] = temp;
			
		
		}
		else{
			graph[actor_2_name].push_back(actor1);
			graph[actor_2_name].push_back(actor3);

		}

		if(graph.find(actor_3_name) == graph.end()){ //if the current actor is not found in the map
			vector<actor> temp;
			temp.push_back(actor1);
			temp.push_back(actor2);
			graph[actor_3_name] = temp;
			
		}
		else{
			graph[actor_3_name].push_back(actor1);
			graph[actor_3_name].push_back(actor2);

		}


}	

void AdjacencyList::bfs(string src, string dest){
	queue<string> q;
	q.push(src);
	map<string, bool> visited;
	map<string, actor> parents;
	bool destReached = false;

	actor srcActor, destActor;
	srcActor.name = src;
	destActor.name = dest;

	// while the q isn't empty and
	// destination wasn't found, run loop
	// and add adjacent nodes of front node
	// of queue

	while(!q.empty() && !destReached){
		string topActor = q.front();
		q.pop();

		for(auto currAdj : graph[topActor]){
			if(!visited[currAdj.name] &&
			currAdj.name != src){
				q.push(currAdj.name);
				visited[currAdj.name] = true;
				parents[currAdj.name].name = topActor;
				parents[currAdj.name].movie = currAdj.movie;

				if(currAdj.name == dest){
					destActor = currAdj;
					destReached = true;
					break;
				}
			}
		}
	}

	// if the destination was never reached,
	// then that means there is no path
	// between src and dest
	if(!destReached){
		cout << "Could not find path between ";
		cout << src << " and " << dest << endl;
		return;
	}

	stack<actor> s;
	string currVal = dest;
	actor currActor = destActor;

	// this loop helps us trace back
	// the path from dest to src
	// and plugs it into a stack
	while(parents[currVal].name != ""){
		auto pred = parents[currVal];
		currActor.movie = pred.movie;
		s.push(currActor);
		currActor = pred;
		currVal = pred.name;
		//currActor = parents[currVal];

	}

	// print out the traced path
	cout << src;
	while(!s.empty()){
		auto curr = s.top();
		// cout << " -> " << curr.name;
		// cout << " (" << curr.movie << ")";
		transform(curr.movie.begin(), curr.movie.end(),curr.movie.begin(), ::toupper);
		cout << " -> " << "(" << curr.movie << ")";
		cout << " -> " << curr.name;

		s.pop();
	}
	cout << endl;

}

void AdjacencyList::dfs(string src, string dest) {
    stack <string> sta;
    sta.push(src);
    map<string, bool> visited;
    map<string, actor> parents;
    bool found = false;

    actor srcActor, destActor;
    srcActor.name = src;
    destActor.name = dest;

    while(!sta.empty() && !found){
        string firstactor = sta.top();
        sta.pop();

        for(auto currAdj : graph[firstactor])
        {
            if(!visited[currAdj.name] && currAdj.name != src)
            {
            sta.push(currAdj.name);
            visited[currAdj.name] = true;
            parents[currAdj.name].name = firstactor;
			parents[currAdj.name].movie = currAdj.movie;

				if(currAdj.name == dest){
					destActor = currAdj;
					found = true;
					break;
				}
            }
        }
    }

    if(!found){
		cout << "Could not find path between ";
		cout << src << " and " << dest << endl;
		return;
	}

    stack<actor> s;
	string currVal = dest;
	actor currActor = destActor;

	while(parents[currVal].name != ""){
		currActor.movie = parents[currVal].movie;
		s.push(currActor);
		currActor = parents[currVal];
		currVal = parents[currVal].name;
		//currActor = parents[currVal];

	}

	cout << src;
	while(!s.empty()){
		auto curr = s.top();
	
		transform(curr.movie.begin(), curr.movie.end(),curr.movie.begin(), ::toupper);
		cout << "->"  <<   "(" << curr.movie << ")" << std::flush;
		cout << "->"  << curr.name << std::flush;

		s.pop();
	}
	cout << endl;
}


int AdjacencyList::GetEdgeWeight(string src, string dest){
  vector<actor> adjActors = graph[src];
  for(actor curr : adjActors){
    if(curr.name == dest) return curr.weight;
  }
  return -1;
}




void AdjacencyList::dijkstra(string src, string dest){
	priority_queue<pair<string, int>, vector<pair<string, int> >, comp> pq;

	pq.push(make_pair(src,0));

	unordered_map<string, int> dist;
	unordered_map<string, pair<string, string> > prev;
	unordered_map<string, bool> done;

	for(const auto& elem : graph){
		
		auto adjActors = elem.second;
		for(auto curr : adjActors){
			int initialDist = curr.name == src ? 0 : INT_MAX;
			dist[curr.name] = initialDist;
		}
	}


	bool found = false;

	while(!pq.empty()){

		auto top = pq.top();
		pq.pop();

		for(auto adjActor : graph[top.first]){

			int weight = adjActor.weight;
			int topDist = dist[top.first];

			if(!done[adjActor.name] && ((topDist + weight) < dist[adjActor.name])){

				dist[adjActor.name] = topDist + weight;
				//prev[adjActor.name] = {top.first, adjActor.movie};
				prev[adjActor.name] = make_pair(top.first, adjActor.movie);
				//pq.push({adjActor.name, topDist + weight});
				if(adjActor.name == dest) found = true;
				pq.push(make_pair(adjActor.name, topDist + weight));
			}
		}
		done[top.first] = true;
	}

	if(!found){
		cout << "Could not find path between ";
		cout << src << " and " << dest << endl;
		return;
	}

	string val = dest;
	stack<actor> s;
	while(val != src){
		auto currPrev = prev[val];
		s.push(actor(val, currPrev.second, dist[val]));
		val = currPrev.first;
	}

	int cost = 0;
	cout << src;
	while(!s.empty()){
		auto top = s.top();
		s.pop();
		if(top.name == dest) cost = top.weight;
		transform(top.movie.begin(), top.movie.end(),top.movie.begin(), ::toupper);
		cout << " -> (" << top.movie << ") -> " << top.name;
	}
	cout << " | Total Cost: " << cost << endl;

}



void RemoveMarks(string& word){

	bool wasPrevMark = false;
    for(int i = 0; i < word.length(); i++){
        char curr = word.at(i);
        
        if(curr == '"' && !wasPrevMark){
            word.erase(word.begin() + i);
            wasPrevMark = true;
            //cout << "Removed at " << i << endl;
            i--;
        }
        else wasPrevMark = false;
    }
}



int main() {

	AdjacencyList graph;
	vector<vector<string> > content;
	vector<string> row;
	string line, word;

	// file pointer
	ifstream file;

	// opens an existing csv file or creates a new file.
	file.open("formattedMovieData.csv", ios::in);

	int count = 0;
	int i = 0;
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
			stringstream str(line);


			while(getline(str, word, '|')){

				if(word.find("\"") != string::npos){
			

					RemoveMarks(word); 
				}

				if(row.size() < 3 && word.find(",") != string::npos)
					while(word.find(",") != string::npos)
						word.erase(word.begin() + word.find(","));
					

				row.push_back(word);
			

			}
		
				content.push_back(row);
	
				//lowercasing the input for consistency
				transform(row[0].begin(), row[0].end(), row[0].begin(), ::tolower);
				transform(row[1].begin(), row[1].end(), row[1].begin(), ::tolower);
				transform(row[2].begin(), row[2].end(), row[2].begin(), ::tolower);
				transform(row[3].begin(), row[3].end(), row[3].begin(), ::tolower);

				graph.insert(row[0],row[1],row[2],row[3]);
				count++;

		}
		
		file.close();
	}

	else{
		cout<<"Could not open the file\n";
		return -1;
	}


	cout << endl << endl;

	bool run =  true;

	cout << "WELCOME TO ACTOR SEARCH" << endl;
	cout<< "Please input when prompted and press enter to submit your input." << endl << endl; 


	// command line interface


	while(run){
	

	cout << "Input actor 1:" << endl;
	string actor_1;
	getline(cin, actor_1);

	transform(actor_1.begin(), actor_1.end(), actor_1.begin(), ::tolower); //lowercasing input for consistency
	
	cout << "Input actor 2:" << endl;
	string actor_2;

	getline(cin, actor_2);

	transform(actor_1.begin(), actor_1.end(), actor_1.begin(), ::tolower); //lowercasing input for consistency

	bool exist = graph.inGraph(actor_1, actor_2);

	if(!exist){

	cout << "One of these actors are not in our database or there is a spelling error. Please provide different input." << endl;

	cout << "Input actor 1:" << endl;

	getline(cin, actor_1);

	transform(actor_1.begin(), actor_1.end(), actor_1.begin(), ::tolower); //lowercasing input for consistency
	
	cout << "Input actor 2:" << endl;

	getline(cin, actor_2);

	transform(actor_1.begin(), actor_1.end(), actor_1.begin(), ::tolower); //lowercasing input for consistency

	exist = graph.inGraph(actor_1, actor_2);

	}


	cout << "Actors inputted: " << actor_1 << " and " << actor_2 << endl << endl; 


	cout << "1: Perform a Breadth-first Search between the actors" << endl;
	cout << "2: Perform a Depth-first Search between the actors" << endl;
	cout << "3: Perform a Dijkstra's Search between the actors" << endl;
	cout << "Input 1, 2, or 3 :"<< endl;

	int search;
	cin >> search;

	if(!(search == 1 | search == 2 | search == 3)){

		bool valid = false;
		while(!valid){
			cout << "Please input a search valid value: " << endl;
			cin >> search;

				if(search == 1 | search == 2 | search == 3){
					valid = true;
					
				}

		}

	}

	if(search == 1){
		cout << "Performing Breadth-first Search" << endl;
		auto start = high_resolution_clock::now();
		graph.bfs(actor_1, actor_2);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);	
		cout << "Time diff for breadth-first search: " << duration.count() <<" milliseconds" <<  endl;
	}

	if(search == 2){

		cout << "Depth-first Search" << endl;

		auto start = high_resolution_clock::now();
		graph.dfs(actor_1, actor_2);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);	
		cout << "Time diff for depth-first search: " << duration.count() << " milliseconds" << endl;
		

	}
	if(search == 3){

		cout << "Dijkstra's Search" << endl;
		auto start = high_resolution_clock::now();
		graph.dijkstra(actor_1, actor_2);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);	
		cout << "Time diff for dijkstra's search: " << duration.count() << " milliseconds" << endl;
		

	}


	cout << "Run Again? Enter 1 for yes and 0 for no: " << endl;

	int repeat;
	cin >> repeat;
 	cin.ignore(); //handle newline character if program is repeated
	if(repeat == 0){
		run = false;
	}

	if(repeat == 1){
		run = true;
	}


	} //end of while


	cout << "Program terminated. Thanks for using our Actor search program!" << endl;



	return 0;

}












