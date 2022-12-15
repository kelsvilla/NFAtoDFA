#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<iterator>
#include <string>
#include <algorithm>
using namespace std;

void printNFA(vector<vector<vector<int>>> nfaTable){
	cout<<"States\t\t"; //printing column labels
	char input='a';
	for(int i=0;i<nfaTable[0].size()-1;i++){
		cout<<"|"<<input<< "\t";
		input = input + 1;
	}
	cout<<"|e"<<endl;
	cout << "----------------";
	for(int i=0;i<nfaTable[0].size();i++){
	    cout << "--------";
	}
	cout << endl;
	for(int i=0;i<nfaTable.size();i++){ // iterating through nfaTable and print the 3d vector with formatting
		cout << i << "\t";
		for(int j=0;j<nfaTable[i].size();j++){
			cout<<"\t|";
			for(int k=0;k<nfaTable[i][j].size();k++){ 
				cout<<nfaTable[i][j][k];
				if(k != nfaTable[i][j].size()-1){
				    cout << ","; 
				}
			}
		}
		cout<<endl;
	}

};

void printDFA(vector<vector<int>>states, vector<vector<vector<int>>> dfaTable){
	cout<<"States\t\t"; //printing the column labels
	char input='a';
	for(int i=0;i<dfaTable[0].size();i++){
		cout<<"|"<<input<<"\t";
		input = input + 1;
	}
	cout << "\n----------------";
	for(int i=0;i<dfaTable[0].size();i++){
	    cout << "--------";
	}
	cout << endl;
	for(int i=0;i<states.size();i++){ //if a state is empty, print -, other wise iterate through and print each vector inside vector states
		for(int j=0;j<states[i].size();j++)
			cout<<states[i][j];
		if(states[i].empty()){
			cout<<"- ";
		}
		cout << "\t";
		for(int p=0;p<dfaTable[i].size();p++){//iterating through the dfaTable and printing with format, if outcome states are empty, print -
			cout<<"\t|";
			for(int k=0;k<dfaTable[i][p].size();k++){
				cout<<dfaTable[i][p][k];
				
			}
			if(dfaTable[i][p].empty()){
				cout<<"- ";
			}
		}
		cout<<endl;
	}
};

vector<int> conversion(int x,vector<vector<vector<int> > > table){
	vector<int> dfaTable; //creation of the DFA table
	queue<int> queue;
	
	dfaTable.push_back(x); // Pushing the the table with passed value

	for(int i=0; i<table[x][table[x].size()-1].size(); i++) //for every spot in the passed table, add the value to the queue
		queue.push(dfaTable[i]);

	while(queue.size() != 0){ //While the queue is not empty, check to see if the table in the given spot is empty. If it is not, traverse the queue and find this table value in the table.
								// If it is the end of the table, push value into the table. Then push value into the queue
		int z = queue.front();
		queue.pop(); // remove the front of the queue for the next cycle

			if(table[z][table[z].size()-1].size() != 0){ 
				for(int i=0; i<table[z][table[z].size()-1].size(); i++){
					if(find(dfaTable.begin(), dfaTable.end(), table[z][table[z].size()-1][i])==dfaTable.end()){
						dfaTable.push_back(table[z][table[z].size()-1][i]);
						queue.push(table[z][table[z].size()-1][i]);
					}
				}
			}
	}

	return dfaTable; //return conversion
}

int main() {

	int statesN, alphabetN; //number of states, number of members in alphabet
	cout << "Enter the total number of states in the NFA: ";
	cin >> statesN;
	cout << "Enter number of members in alphabet: ";
	cin >> alphabetN;
	cout << endl;
	vector<vector<vector<int>>> nfaTable;

	for (int i = 0; i < statesN; i++)  //for each state in the NFA
	{
		cout << "For state " << i << endl;
		vector<vector<int>> temp1;
		char currChar = 'a';//curr input letter
		int output, numOutputs;

		for (int j = 0; j < alphabetN; j++) //for each member in the alphabet
		{
			vector<int> temp2;
			cout << "Enter number of output states for input " << currChar++ << ": ";
			cin >> numOutputs;
			cout << "Enter output states: " << endl;
			for (int k = 0; k < numOutputs; k++) 
			{
				cin >> output;
				temp2.push_back(output);
			}
			temp1.push_back(temp2);
		}

		vector<int> temp2;
		cout << "Enter number of output states for the empty transition: ";
		cin >> numOutputs;
		cout << "Enter output states :" << endl;

		for (int k = 0; k < numOutputs; k++) 
		{
			cin >> output;
			temp2.push_back(output);
		}

		temp1.push_back(temp2);
		nfaTable.push_back(temp1);
	}

	cout << "\nNFA Table\n";
	printNFA(nfaTable);

	vector<vector<vector<int>>> dfaTable;
	vector<vector<int>> states;
	states.push_back(conversion(0, nfaTable));

	queue<vector<int>> queue;
	queue.push(states[0]);

	while (!queue.empty()) {
		vector<int> front = queue.front();
		queue.pop();

		vector<vector<int> > temp2;
		for (int i = 0; i < alphabetN; i++)
		{
			vector<int> temp1;
			set<int> sortedSet;
			for (int j = 0; j < front.size(); j++) 
			{

				for (int k = 0; k < nfaTable[front[j]][i].size(); k++) 
				{
					vector<int> conv = conversion(nfaTable[front[j]][i][k], nfaTable);

					for (int l = 0; l < conv.size(); l++) {
						if (sortedSet.find(conv[l]) == sortedSet.end())
							sortedSet.insert(conv[l]);
					}
				}
			}

			for (set<int>::iterator m = sortedSet.begin(); m != sortedSet.end(); m++)
			{
				temp1.push_back(*m);
			}

			temp2.push_back(temp1);

			if (find(states.begin(), states.end(), temp1) == states.end())
			{
				states.push_back(temp1);
				queue.push(temp1);
			}
		}

		dfaTable.push_back(temp2);
	}

	cout << "\nDFA Table\n";
	printDFA(states, dfaTable);
}