#include <iostream>
#include <vector>
#include <string>
using namespace std;

//prints in format whatever table (NFA/DFA) is passed to it, with a vector of states also passed
void PrintTable(vector<vector<vector<string>>> table, vector<string> states){
        cout << "States\t\t|0\t|1\n";
        cout << "--------------------------------\n";
        for(int i = 0; i < table.size(); i++){
                cout << states[i] << "\t";
                for(int j = 0; j < table[i].size(); j++){
                        cout << "\t|";
                        for(int k = 0; k < table[i][j].size(); k++){
                                cout << table[i][j][k] << ", ";
                        }
                }
                cout << endl;
        }
}


int main(){
	//declarations of variables
	int i, j, k, stateN, outputStateN;
    string state, outputState;
    vector<vector<vector<string>>> table;
    vector<string> states;

	//enter states present on left side of NFA table
    cout << "Enter the total number of states of the NFA: ";
    cin >> stateN;

	//for loop for state rows, but states are not inputed in table but they are inputed in the states vector
    for(i = 0; i < stateN; i++){
		cout << endl;
		cout << "Enter state " << i+1 << "'s letter (one uppercase letter): ";
		cin >> state;
		states.push_back(state);
		vector<vector<string>> temp1;

		//for loop for inputs (0 and 1) of table
		for(j = 0; j < 2; j++){
			vector<string> temp2;
			cout << "Enter the # of output states for input "<< j << " of state " << state << ": ";
			cin >> outputStateN;
			cout << "Enter the output states for input " << j << " of state " << state << " (if there are no output states, type '-'): \n";

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
	PrintTable(table, states);

	return 0;
}
