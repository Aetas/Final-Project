/*
	Derek Prince
	Binary conversion program for 14ers hashmap.
*/
#include<fstream>
#include<iostream>
#include<string>
//specify -v for vertex and -e for edge? Probably for this program. Not for the main program. That will need default (-t -> text) -b binary
//come to think of it, edge files have no predefined structure other than name -> *list of edges* endl.
//Maybe a null terminator to signify new mountain? Something to look into at any rate.
//Apparently you can just print endl in binary files for an endline code print. Okay then.
//Now I just need the friggin file.

void vertexFileTransfer(std::fstream& in_file);
void edgeFileTransfer(std::fstream& in_file);

int main(int argc, char* argv[]) {
	
	std::fstream file;
	if (argc > 0) {
		if (argc > 1) {	//if an option is specified, the 3rd thing will be the file name.
			file.open(argv[2], std::fstream::in);
			while (!file.is_open()) {
				std::cout << " File did not open, please reenter file name\n"
					<< " <name.csv>: ";
				std::string file_name = "";
				getline(std::cin, file_name);
				file.open(file_name.c_str());
			}
		}
		else {
			file.open(argv[1]);	//else it is the first argument.
			while (!file.is_open()) {	//if file did not open
				std::cout << " File did not open, please reenter file name\n"
					<< " <name.csv>: ";
				std::string file_name = "";
				getline(std::cin, file_name);
				file.open(file_name.c_str());
				std::cout << std::endl;
			}
			std::string option = "";
			std::cout << " Enter -v for a vertex file, or -e for an edge file\n <-v/-e>: ";
			std::cin >> option;
			if (option == "-v")
				vertexFileTransfer(file);
			else
				edgeFileTransfer(file);
		}
		if (argv[1] == "-v")	//vertex file
			vertexFileTransfer(file);
		else
			edgeFileTransfer(file);
			

	}
	else {	//nothing was specified, start from scratch.
		std::string file_nm = "";
		std::cout << " Please enter file name\n <name.csv>: ";
		getline(std::cin, file_nm);
		file.open(file_nm.c_str());
		while (!file.is_open()) {	//if file did not open
			std::cout << " File did not open, please reenter file name\n"
				<< " <name.csv>: ";
			std::string file_name = "";
			getline(std::cin, file_name);
			file.open(file_name.c_str());
			std::cout << std::endl;
		}
		std::string option = "";
		std::cout << " Enter -v for a vertex file, or -e for an edge file\n <-v/-e>: ";
		std::cin >> option;
		if (option == "-v")
			vertexFileTransfer(file);
		else
			edgeFileTransfer(file);
	}
	file.close();
	return 0;
}

void vertexFileTransfer(std::fstream& in_file) {
	//FILE STRUCTURE:
	//Rank,Peak name, Elevation, Range, Latitude, Longitude
	//Ex: "39,Sunlight Peak,14059,San Juan,37.6274,N,107.5959,W"
	std::cout << " ...";
	std::string buffer = "", name = "", range = "";
	int rank = 0;
	double elevation = 0, latitude = 0, longitude = 0;
	char N_S = ' ', E_W = ' ';
	getline(in_file, buffer, '\n');	//ditch the top explanatory line
	buffer = "";	//easier to make sure no rogue values are kept;
	std::fstream out_file("14ers.bin", std::fstream::out | std::fstream::binary);	//write file.
	std::fstream out_readme("Vertices - Binary Structure.txt", std::fstream::out);

	while (!in_file.eof()) {
		getline(in_file, buffer, ',');
		if (buffer == "")
			break;
		rank = std::stoi(buffer);		//rank
		out_file << rank;
		getline(in_file, buffer, ',');
		name = buffer;					//name
		out_file << name;
		getline(in_file, buffer, ',');
		elevation = std::stod(buffer);	//elevation
		out_file << elevation;
		getline(in_file, buffer, ',');
		range = buffer;					//range
		out_file << range;
		getline(in_file, buffer, ',');
		latitude = std::stod(buffer);	//latitude
		out_file << latitude;
		getline(in_file, buffer, ',');
		N_S = buffer[0];				//North/South
		out_file << N_S;
		getline(in_file, buffer, ',');
		longitude = std::stod(buffer);	//longitude
		out_file << longitude;
		getline(in_file, buffer, '\n');
		E_W = buffer[0];				//East/West
		out_file << E_W;
		out_file << std::endl;
	}
	out_readme << "The structure of the binary vertices file is as follows:" << std::endl
		<< "rank<int>, name<sting>, elevation<double>, range<string>, latitude<double>, north/south<char>, longitude<double>, east/west<char>, endl" << std::endl;
	out_readme.close();
	std::cout << "write successful!" << std::endl << std::endl;
}

void edgeFileTransfer(std::fstream& in_file) {
	//Structure:
	//Name, edge, edge, edge, ..., edge\n
	std::string name;
	std::cout << " ...";
	std::fstream out_file("edges.bin", std::fstream::out | std::fstream::binary);
	while (!in_file.eof()) {
		if (in_file.peek() != '\n') {
			getline(in_file, name, ',');
			out_file << name;
		}
		else	//else grab the trash bit
			getline(in_file, name, '\n');
	}
	std::fstream out_readme("Edges - Binary Structure.txt", std::fstream::out);
	out_readme << "The structure of the binary edge file is as follows:" << std::endl
		<< "Origin name<string>, edge<string>, edge<string>, ..., edge<string>\\n" << std::endl;
	out_readme.close();
	std::cout << "write successful!" << std::endl << std::endl;
}