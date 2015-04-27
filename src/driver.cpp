/*
	Derek Prince
	April, 2015
	CSCI 2270 Final Project
	@ CU Boulder
	(even though we still have a final...)
	HashMap, a graph with perfect hashing lookup.

	In the saddest sort of way, I did a classic amature mistake of getting carried away with 
	the fancy implementation options (such as recursively overloading [] to abstract from the hashtable chain)
	and template inheritance/self inclusion and nesting to make for onely one class.
	And because of it, I ran out of time and had to implement it the simple way to something less than my expectations.
	I'm going to continue to update it, but it's due in a couple of hours. Lovely.
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
					<< "\n Please enter the name of the desired CSV file\n"
					<< " <name.csv>: ";
				//cin.ignore(10000, '\n');	//probably going to have to put a bunch of these in the menu loop as per usual. 
				getline(cin, fileName);
				cout << endl;
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
			<< "1. Print contents" << endl
			<< "2. Get hash location" << endl		//Since I use this largely to test my hash function, it does not complain if the mountain does not exist. It only returns the location it would be
			<< "3. Add Mountain" << endl
			<< "4. Add Mountain Edge" << endl
			<< "5. Add  all edges" << endl
			<< "6. Display mountain edges" << endl
			<< "7. Find shortest path" << endl
			<< "8. Find shortest distance" << endl
			<< "9. Quit" << endl;
		cout << " <#>: ";
		cin >> select;
		if (select == 1) {	//print contents
			hashMap->printContents();
		}
		if (select == 2) {	//get hash location
			cout << " Enter mountain name\n"
				<< " <name>: ";
			std::string name;
			getline(cin, name);
			Keys k = hashMap->populateKeys(name);
			cout << "(" << k[0] << "," << k[1] << ") : "
				<< name << endl;
		}
		if (select == 3) {	//add mountain
			string name = "", range = "";
			int rank = 0;
			double elevation = 0, latitude = 0, longitude = 0;
			char N_S = ' ', E_W = ' ';
			cout << " Enter rank\n"				//rank
				<< " <#>: ";
			cin >> rank;
			cout << "\n Enter name\n"			//name
				<< " <name>: ";
			getline(cin, name);
			cout << "\n Enter elevation\n"		//elevation
				<< " <#>: ";
			cin >> elevation;
			cout << "\n Enter range\n"			//range
				<< " <range>: ";
			getline(cin, range);
			cout << "\n Enter coordinates\n"	//coords
				<< " <Lat#>: ";
			cin >> latitude;
			cout << "\n <N/S>: ";
			cin >> N_S;
			cout << " <Long#>: ";
			cin >> longitude;
			cout << "\n <E/W>: ";
			cin >> E_W;
			cout << endl;
			hashMap->insertMountain(rank, name, elevation, range, latitude, N_S, longitude, E_W);
		}
		if (select == 4) {	//add mountain edge
			cout << " Enter origin mountain\n"
				<< " <name>: ";
			string origin = "";
			getline(cin, origin);
			cout << endl << " Enter destination mountain\n"
				<< " <name>: ";
			string destination = "";
			getline(cin, destination);
			cout << endl;
			Keys orig = hashMap->populateKeys(origin);
			Keys dest = hashMap->populateKeys(destination);
			if (!hashMap->mountainExists(orig, origin)) {
				cout << " The originating mountain does not exist." << endl;
				continue;
			}
			else  if (!hashMap->mountainExists(dest, destination)) {
				cout << " The destination mountain does not exist." << endl;
				continue;
			}
			else
				hashMap->addEdge(orig, dest);
		}
		if (select == 5) {

		}
		if (select == 6) {	//display specific Mountain edges
			cout << " Enter mountain name\n"
				<< " <name>: ";
			string name;
			getline(cin, name);
			cout << endl;

			Keys k = hashMap->populateKeys(name);
			if (hashMap->mountainExists(k, name)) {
				hashMap->displayEdges(hashMap->getMountain(k));
			} 
			else {
				cout << " Mountain not found." << endl;
			}
		}
		if (select == 7) {	//
			cout << " Enter starting mountain name\n"
				<< " <name>: ";
			string name;
			getline(cin, name);
			cout << endl;

			Keys k = hashMap->populateKeys(name);
			if (hashMap->mountainExists(k, name)) {
				hashMap->displayEdges(hashMap->getMountain(k));
			}
			else {
				cout << " Mountain not found." << endl;
			}
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
		rank = std::stoi(buffer);
		getline(inFile, buffer, ',');
		name = buffer;
		getline(inFile, buffer, ',');
		elevation = std::stod(buffer);
		getline(inFile, buffer, ',');
		range = buffer;
		getline(inFile, buffer, ',');
		latitude = std::stod(buffer);
		getline(inFile, buffer, ',');
		N_S = buffer[0];
		getline(inFile, buffer, ',');
		longitude = std::stod(buffer);
		getline(inFile, buffer, '\n');
		E_W = buffer[0];
		// Build edges sepparately? Hashing has the advantage of ditching O(n) lookup, so adding them after simplifies 
		// this program and makes each function more independant and standalone. 
		// Would take O(2+e) if e is the number of edges to be added as opposed to O(e) if done here.
		hm->insertMountain(rank, name, elevation, range, latitude, N_S, longitude, E_W);
	}
}
