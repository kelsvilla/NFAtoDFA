#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

//prints in format whatever table (NFA/DFA) is passed to it, with a vector of states also passed
void PrintTable(vector<vector<vector<string>>> table, vector<string> states, int alphabetN, string alphabet){
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
}

int main(){
	//declarations of variables
	int i, j, k, stateN, outputStateN, alphabetN;
    string state, outputState;
    vector<vector<vector<string>>> table;
    vector<string> states;
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string capsbet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


	//enter states present on left side of NFA table
    cout << "Enter the total number of states in the NFA (Max=26): ";
    cin >> stateN;

	cout << "Enter the total number of elements in the alphabet (Max=26): ";
	cin >> alphabetN;

	//for loop for state rows, but states are not inputed in table but they are inputed in the states vector
    for(i = 0; i < stateN; i++){
		cout << endl;
		//cout << "Enter state " << i+1 << "'s letter (one uppercase letter): ";
		state = capsbet.at(i);
		states.push_back(state);
		vector<vector<string>> temp1;

		//for loop for inputs of table
		for(j = 0; j < alphabetN; j++){
			vector<string> temp2;
			cout << "Enter the # of output states for input "<< alphabet.at(j) << " of state " << state << ": ";
			cin >> outputStateN;
			cout << "Enter the output states for input " << alphabet.at(j) << " of state " << state << " (if there are no output states, type '-'): \n";

			if(outputStateN == 0){
					outputStateN+=1;
			}

			//for loop for the output state(s) of inputs
			for(k=0;k<outputStateN;k++){
				cin >> outputState;
				temp2.push_back(outputState);
			}
				temp1.push_back(temp2);
		}
		table.push_back(temp1);
	}

	//nfa table printing
	cout << "\n\nNFA Table\n";
	PrintTable(table, states, alphabetN, alphabet);

	//Creating list of DFA states
	vector<string> DFAStateList;
	DFAStateList = DFAStates(table, states, capsbet);

	printDFA(table, DFAStateList, alphabetN, alphabet);

	return 0;
}
