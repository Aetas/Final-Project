//#ifndef HASHTABLE_H
#define HASHTABLE_H
#define PRIMARY_SIZE 10
#define SECONDARY_SIZE 10

#include<string>
#include"Mountain.h"

//Fair warning - if you look at this page long enough you will invariably start reading 'HashTable' as 'HashTag.' Which is of course, unfortunate.
class HashTable_Secondary;

class HashTable_Primary {
public:
	HashTable_Primary();
	HashTable_Primary(int& in_size);
	~HashTable_Primary();

	void printInventory();
	void insertMountain(std::string& in_name, double& in_elevation);//name, elevation
	void deleteMountain(std::string& in_name);						//name
	void collision_resolution(std::string& in_name, double& in_elevation, int& key);	//name, year, key
	Mountain* findMountain(std::string& name);						//name

	unsigned int get_size();
	bool is_empty();
protected:
	int get_hash_key(std::string&);

private:
	int size;
	//pointer to pointers for secondary hash table which represents the range that the mountains are found in
	HashTable_Secondary** hashTable_Range;	//figure out the hash functions, revisit naming convention	

};

class HashTable_Secondary : public HashTable_Primary {
public:
	HashTable_Secondary();
	HashTable_Secondary(int& in_size);
	~HashTable_Secondary();
protected:

private:
	Mountain** hashTable_Mountain;
};

//#endif //HASHTABLE_H