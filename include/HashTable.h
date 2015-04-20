#ifndef HASHTABLE_H
#define HASHTABLE_H

#include"Mountain.h"

class HashTable_Secondary;

class HashTable_Primary {
public:
	HashTable_Primary();
	HashTable_Primary(int&);
	~HashTable_Primary();

	void printInventory();
	void insertMovie(std::string&, int&);					//title, year
	void deleteMovie(std::string&);							//title
	void collision_resolution(std::string&, int&, int&);	//title, year, key
	Mountain* findMovie(std::string&);						//title

	unsigned int get_size();
	bool is_empty();
protected:
	int get_hash_key(std::string&);

private:

	int size;
	HashTable_Secondary** hashTable;

};

class HashTable_Secondary : public HashTable_Primary {
public:
	HashTable_Secondary();
	HashTable_Secondary(int&);
	~HashTable_Secondary();
protected:

private:
	Mountain** hashTable();
};

#endif //HASHTABLE_H