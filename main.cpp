#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<iterator>
using namespace std;


//prints in format whatever table (NFA/DFA) is passed to it, with a vector of states also passed
/*void PrintTable(vector<vector<vector<string>>> table, vector<string> states, int alphabetN, string alphabet) {
	cout << "States\t\t";
	for (int i = 0; i < alphabetN; i++)
	{
		cout << "|" << alphabet.at(i) << "\t";
	}
    cout << "\n--------------------------------\n";
    for(int i = 0; i < table.size(); i++){
            cout << states[i] << "\t";
            for(int j = 0; j < table[i].size(); j++){
                    cout << "\t|";
                    for(int k = 0; k < table[i][j].size(); k++){
						if (k != 0)
							cout << ", ";
						cout << table[i][j][k];
                    }
            }
            cout << endl;
    }
	cout << endl;
}

vector<string> DFAStates(vector<vector<vector<string>>> table, vector<string> states, string capsbet){
	vector<string> DFAStates;
	bool added = false;
	DFAStates.push_back(states[0]);

	for(int i=0; i<table.size(); i++){
		for(int j=0; j<table[i].size(); j++){
			string tempState;
			if(table[i][j].size() >= 1){
				for(int k=0; k<table[i][j].size(); k++)
				{
					if (table[i][j][k] != "-")
						tempState = tempState + table[i][j][k];
					else
						tempState = capsbet.at(table.size());
				}
				added = false;
				for (int l = 0; l < DFAStates.size(); l++)
				{
					if (DFAStates.at(l) == tempState)
					{
						added = true;
					}
				}
				if (!added)
				{
					DFAStates.push_back(tempState);
				}
			}
		}
	}

	for (int i = 0; i < DFAStates.size(); i++)
	{
		if (DFAStates.at(i).length() > 1) //for all DFA states with more than 1 character, AB, BC, CD, etc.
		{
			string tempState;
			for (int j = 0; j < DFAStates.at(i).size(); j++) //for every character in those states
			{
				for (int k = 0; k < states.size(); k++) //for every state from NFA
				{
					if (DFAStates.at(i).at(j) == states.at(k).at(0)) //If a character matches a state from NFA
					{
						for (int l = 0; l < table.at(k).size(); l++)
						{
							for (int m = 0; m < table.at(k).at(l).size(); m++)
							{
								tempState = tempState + table[k][l][m];
								cout << tempState;
							}
							DFAStates.push_back(tempState);
						}
					}
				}
			}
		}
	}

	cout << "DFA STATES\n";
    for(int i=0; i<DFAStates.size(); i++)
			cout << DFAStates[i]<< endl;

	return DFAStates;
}




void printDFA(vector<vector<vector<string>>> table, vector<string> DFAStates, int alphabetN, string alphabet)
{
	cout << "States\t\t";
	for (int i = 0; i < alphabetN; i++)
	{
		cout << "|" << alphabet.at(i) << "\t";
	}
	cout << "\n--------------------------------\n";
	for (int i = 0; i < DFAStates.size(); i++)
	{
		cout << DFAStates.at(i) << "\t\t|";
		for (int j = 0; j < DFAStates.at(i).length(); j++)
		{
			for (int k = 0; k < table.size(); k++)
			{
				for (int l = 0; l < table.at(k).size(); l++)
				{
					for (int m = 0; m < table.at(k).at(l).size(); m++)
					{
						for (int n = 0; n < table.at(k).at(l).at(m).size(); n++)
						if (DFAStates.at(i).at(j) == table.at(k).at(l).at(m).at(n))
						{
							
						}
					}
				}
			}
		}
		cout << endl;
	}
}*/

int main() {

	int statesN, alphabetN; //number of states, number of members in alphabet
	cout << "Enter the total number of states in the NFA: ";
	cin >> statesN;
	cout << "Enter number of members in alphabet: ";
	cin >> alphabetN;
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

	printDFA(states, dfaTable);
}