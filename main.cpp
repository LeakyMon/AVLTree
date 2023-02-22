#include "BST.h"
#include <fstream>
#include <vector>
#include <map>
using namespace std;


//NEW AND UPDATED READ THAT JUST TAKES USER INPUT DIRECTLY NOT FROM A FILE
void NewRead(int num, string line, vector<string>& input_cmd, vector<string>& input_name, vector<int>& input_ID) {

	//Pushing back an element allows all vectors to be lined up, 
	//ex even if there is no ID at a command, the inputId still gets pushed back so when retrieving data from vectors at i, they line up
	input_cmd.push_back("");
	input_name.push_back("");
	input_ID.push_back(0);
		
	istringstream input(line);
	string currWord;
	string lastName;
	char q = '\"'; //quotation marks are wrapped with the \, q will help easily locate them without typing it

	//FIRST WORD COMMAND
	//Input reads the first word to find the command and stores in cmd vector
	if (input >> currWord) {
		input_cmd.at(num) = currWord;

		//SECOND WORD NAME
		//Input reads the second word and if it has a quote starting it continues
		if (input >> currWord) { //IF ITS A NAME
			if (currWord.front() == q) {
				//IF NO LAST NAME
				if (currWord.back() == q) { //If it has end quotations we know its only a first name
					//endIndex is position of end of word \"
					size_t endIndex = currWord.find(q, 1);
					string name = currWord.substr(1, endIndex - 1);
					input_name.at(num) = name;

					if (input >> currWord) {
						int tempID = stoi(currWord);
						input_ID.at(num) = tempID;
					}
				}
				else {
					//IF LAST NAME
					//Since there are no end quotations before the space, we know it has a last name
					input >> lastName;
					currWord += " ";
					currWord += lastName;
					size_t endIndex = currWord.find(q, 1);
					if (endIndex != string::npos) {
						string name = currWord.substr(1, endIndex - 1);
						//Find space bar to separate words
						size_t spaceIndex = name.find(' ');
						if (spaceIndex != string::npos) {

							string first = name.substr(0, spaceIndex);
							string last = name.substr(spaceIndex + 1);
							//Combine first and last name and push into name vector
							input_name.at(num) = (first + " " + last);
						}
						else {
							input_name.at(num) = name;
						}
						currWord = currWord.substr(endIndex + 1);
						//IF THERE IS AN ID AFTER THE NAME
						if (input >> currWord) {
							int tempID = stoi(currWord);
							input_ID.at(num) = tempID;

						}
					}
				}
			}
			//IF ITS AN ID NOT A NAME
			else {
				int tempID = stoi(currWord);
				input_ID.at(num) = tempID;
				currWord.clear();
			}
		}

	}
		

}

int main() {

	//Gets Number of Commands
	int numCmds;
	cin >> numCmds;
	//When I pressed enter to insert number cin stored the new line so this removes it
	cin.ignore(1, '\n');
	//Creating AVTTree Object
	AVLTree obj;
	//Vectors to store commands, names, and IDs
	vector<string> cmd, name;
	vector<int> ID_;

	//Loops for num commands and divides and stores input
	for (int i = 0; i < numCmds; i++) {

		string line;
		getline(cin, line);
		//Calls function, uses I as index, line as input, and passes ref of the 3 vectors so the line data can be stored accordingly
		NewRead(i, line, cmd, name, ID_);

	}

	cout << endl;
	//For the size of the commands, it finds what the command was and acts as necessary
		string print = "";
		//Loops through and compares the objects stored in the command vector with the text to find which command to run
		for (int i = 0; i < cmd.size(); i++) {
			if (cmd.at(i) == "insert") {
				obj.insert(name.at(i), ID_.at(i));
			}
			else if (cmd.at(i) == "remove" || cmd.at(i) == "removeInorder") {
				bool t = cmd.at(i) == "remove" ? true : false;
				if (t) {
					obj.remove(ID_.at(i), 0);
				}
				else {
					obj.remove(ID_.at(i), ID_.at(i));
				}
			}
			else if (cmd.at(i) == "search") {
				if (name.at(i) != "") { //Search by name
					obj.searchName(name.at(i));
				}
				else if (ID_.at(i) != 0){
					obj.searchID(ID_.at(i));
				}
			}
			else if (cmd.at(i) == "printInorder") {
				print = obj.inOrder();
				//Gets rid of comma at the end;
				print.resize(print.size() - 2);
				cout << print << endl;
				obj.lines.push_back(print);
			}
			else if (cmd.at(i) == "printPreorder") {
				print = obj.preOrder();
				print.resize(print.size() - 2);
				cout << print << endl;
				obj.lines.push_back(print);
			}
			else if (cmd.at(i) == "printPostorder") {
				print = obj.postOrder();
				print.resize(print.size() - 2);
				cout << print << endl;
				obj.lines.push_back(print);
			}
			else if (cmd.at(i) == "printLevelCount") {
				print = obj.numLvls();
				//print.resize(print.size() - 2);
				cout << print << endl;
				obj.lines.push_back(print);
			}
			else {
				cout << "Command doesn't exist" << endl;
			}
		
		}
		obj.Display(1);
	
	return 0;
}

