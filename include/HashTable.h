#ifndef HASHTABLE_H
#define HASHTABLE_H

class Mountain {

};

class HashTable {
public:
	HashTable();
	HashTable(int&);
	~HashTable();

	void printInventory();
	void insertMovie(std::string&, int&);					//title, year
	void deleteMovie(std::string&);							//title
	void collision_resolution(std::string&, int&, int&);	//title, year, key
	Mountain* findMovie(std::string&);						//title

	unsigned int get_size();
	bool is_empty();

private:
	int get_hash_key(std::string&);

	//int table_size ? <- could use for non macro-defined table size. But for this specific assignment, macro defined is better.
	//used to have int max_index, but it isn't worth the pain of manipulating some records to make delete movie work.
	//since I would potentially have to check all indicies to find the next highest index, deleting in marticular can reach O(*graph size*). Which is worse than O(n)
	int size;
	Mountain** hashTable;

};

#endif //HASHTABLE_H