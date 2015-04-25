/*
	Derek Prince
	April, 2015
	CSCI 2270 Final Project
	@ CU Boulder
	(even though we still have a final...)
	HashMap, a graph with perfect hashing lookup.
*/

#include<iostream>
#include<fstream>
#include"HashMap.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

void readFile(std::ifstream& inFile, HashMap* hm);

int main(int argc, char* argv[]) {

	HashMap* hashMap = new HashMap;

	string tmpName = "Action Jesus";
	Keys<2> k = hashMap->populateKeys(tmpName);
	if (k[0] == 1)
		cout << "cool";
	else
		cout << "radical";
	if (k[1] == 1)
		cout << "that worked. Somehow.";
	else
		cout << "Like I thought.";
		
	//Read in nodes
	std::ifstream inFile;
	if (argc > 1) {
		inFile.open(argv[1]);
		if (inFile.is_open()) {
			readFile(inFile, hashMap);
		}
		else {
			string fileName = "";
			while (!inFile.is_open()) {
				cout << " The file could not be opened."
					<< "\n Please enter the name of the desired CSV file: " << endl;
				getline(cin, fileName);
				inFile.open(fileName.c_str());
			}
			readFile(inFile, hashMap);
		}
	}
	else {	//else no argument was supplied
		string fileName = "";
			cout << "\n Please enter the name of the desired CSV file: " << endl;
			getline(cin, fileName);
			inFile.open(fileName.c_str());
			if (!inFile.is_open()) {
				cout << " The file either could not be opened or found." << endl;
				return 0;
			}
			readFile(inFile, hashMap);
	}//end read in nodes

	inFile.close();	//close in the end

	//error handling


	//menu
	// For the menu, I favored what is esentially a ton of if statements over something like a switch 
	// because variables can declared in if statements, while they cannot in switches. Probably because of RAII or something similar. Switches give stiches. Or something.
	// Presently I don't know how many things I am going to have this program do, so a bunch of blank templates are in place.
	// Probably a mixture of assignments 8 & 9
	int select = -1;
	while (select != 9) {
		cout << " =====Menu======" << endl
			<< "1. " << endl
			<< "2. " << endl
			<< "3. " << endl
			<< "4. " << endl
			<< "5. " << endl
			<< "6. " << endl
			<< "7. " << endl
			<< "8. " << endl
			<< "9. Quit" << endl;
		cout << " <#>: ";
		cin >> select;
		if (select == 1) {
		
		}
		if (select == 2) {

		}
		if (select == 3) {

		}
		if (select == 4) {

		}
		if (select == 5) {

		}
		if (select == 6) {

		}
		if (select == 7) {

		}
		if (select == 8) {

		}
		if (select == 9) {
			cout << " Goodbye!" << endl;
		}
		if (select > 9) {
			cout << " That was not an option." << endl;
		}
	}

	return 0;
}

void readFile(std::ifstream& inFile, HashMap* hm) {
	//FILE STRUCTURE:
	//Rank,Peak name, Elevation, Range, Latitude, Longitude
	//Ex: "39,Sunlight Peak,14059,San Juan,37.6274,N,107.5959,W"

	string buffer = "", name = "", range = "";
	int rank = 0;
	double elevation = 0, latitude = 0, longitude = 0;
	char N_S = ' ', E_W = ' ';
	getline(inFile, buffer, '\n');	//ditch the top explanatory line
	buffer = "";	//easier to make sure no rogue values are kept;
	while (!inFile.eof()) {
		getline(inFile, buffer, ',');
		rank = stoi(buffer);
		getline(inFile, buffer, ',');
		name = buffer;
		getline(inFile, buffer, ',');
		elevation = stod(buffer);
		getline(inFile, buffer, ',');
		range = buffer;
		getline(inFile, buffer, ',');
		latitude = stod(buffer);
		getline(inFile, buffer, ',');
		N_S = buffer[0];
		getline(inFile, buffer, ',');
		longitude = stod(buffer);
		getline(inFile, buffer, '\n');
		E_W = buffer[0];
		// Build edges sepparately? Hashing has the advantage of ditching O(n) lookup, so adding them after simplifies 
		// this program and makes each function more independant and standalone. 
		// Would take O(2+e) if e is the number of edges to be added as opposed to O(e) if done here.
		hm->insertMountain(rank, name, elevation, range, latitude, N_S, longitude, E_W);
	}
}
