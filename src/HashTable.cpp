//NOTE:
//This too will be broken for some time. WIP.
#include<iostream>
#include<fstream>
#include<string>
#include"Mountain.h"
#include"HashTable.h"

HashTable_Primary::HashTable_Primary()
{
	size = 0;
	hashTable = new Movie*[H_TABLE_SIZE];
	for (int i = 0; i < H_TABLE_SIZE; i++)
		hashTable[i] = nullptr;
}

HashTable_Primary::HashTable_Primary(int& table_size)
{
	size = 0;
	hashTable = new Movie*[table_size];
	for (int i = 0; i < table_size; i++)
		hashTable[i] = nullptr;
}

HashTable_Primary::~HashTable_Primary()
{
	delete[]hashTable;
}

void HashTable_Primary::printInventory()
{
	if (size == 0)	//nothing in dood-ma-bob
	{
		std::cout << "empty" << std::endl;	//I'm only tolerating a print in this function because it is a print function.
		return;
	}
	for (int i = 0; i < H_TABLE_SIZE; i++)
	{
		if (hashTable[i] == nullptr)
			continue;	//skip rest
		std::cout << hashTable[i]->title << ":" << hashTable[i]->year << std::endl;
		if (hashTable[i]->next != nullptr)	//I wanted to do this after the initial cout because I don't want to allocate from the heap in the majority of cases.
		{
			Movie* temp = hashTable[i]->next;
			while (temp != nullptr)			//traverse the linked list
			{
				std::cout << temp->title << ":" << temp->year << std::endl;
				temp = temp->next;
			}
		}
	}
}

void HashTable_Primary::insertMovie(std::string& in_title, int& in_year)
{
	int key = get_hash_key(in_title);
	if (hashTable[key] != nullptr)
		collision_resolution(in_title, in_year, key);
	else
	{
		Movie* temp = new Movie(in_title, in_year, key);
		hashTable[key] = temp;
	}
	size++;
}

void HashTable_Primary::deleteMovie(std::string& in_title)
{

	int key = get_hash_key(in_title);

	if (hashTable[key]->title == in_title && hashTable[key]->next == nullptr)
	{
		delete hashTable[key];
		hashTable[key] = nullptr;
		size--;
		return;
	}

	Movie* it = hashTable[key];
	Movie* prev = it;
	Movie* del = nullptr;

	while (del == nullptr)
	{
		if (it->title == in_title)
		{
			del = it;
			prev->next = del->next;
			delete del;
			size--;
			return;
		}
		prev = it;
		it = it->next;
	}

	size--;
}

void HashTable_Primary::collision_resolution(std::string& in_title, int& in_year, int& key)
{
	Movie* new_movie = new Movie(in_title, in_year, key);
	Movie* it = hashTable[key];
	Movie* prev = it;
	if (new_movie->title.compare(hashTable[key]->title) < 0)	//if it is before the first entry...
	{
		new_movie->next = hashTable[key];
		hashTable[key] = new_movie;
		return;
	}
	it = it->next;
	while (it != nullptr)
	{
		if (new_movie->title.compare(it->title) < 0)
		{
			new_movie->next = it;
			prev->next = new_movie;
			return;
		}
		prev = it;
		it = it->next;
	}
	prev->next = new_movie;	//if it has not returned yet, make it the last of the chain
}

Movie* HashTable_Primary::findMovie(std::string& in_title)
{
	int key = get_hash_key(in_title);
	//case 1
	if (hashTable[key] == nullptr)	//if there is no movie in the index, nothing there, return nullptr for main() to handle
		return nullptr;
	Movie* ans = hashTable[key];	//else handle case 2 & 3
	if (hashTable[key]->title != in_title)
	while ((ans != nullptr) && (ans->title != in_title))	//also takes care of the case where the index is taken, but the movie does not exist
		ans = ans->next;

	return ans;	//at this point, ans either holds the answer the function call came for, or nullptr, which is the default case for not found
}

unsigned int HashTable_Primary::get_size()
{
	return size;
}

bool HashTable_Primary::is_empty()
{
	if (size > 0)
		return false;
	return true;
}

int HashTable_Primary::get_hash_key(std::string& in_title)
{
	int sum = 0;
	for (std::string::iterator it = in_title.begin(); it != in_title.end(); it++)
		sum += *it;	//sum ASCII

	return (sum % 10/*H_TABLE_SIZE*/);	//at this point, I've forgone the idea of adding extra baggage to let user redefine the size, 
	//because that happens before the compiler runs anyhow, so changing the macro is just as easy, if not easier
	//the other option is table_size, which would hold the table size passed to the constructor just for hash key use
	//the main reason I cared about a simple 8 bytes floating around my class is not because of the space, but because
	//unsigned int would be the correct choice (*one of many) for holding a size, while plain int would be plain stupid.
	//the reason being, is that the entire idea of giving a choice of table size from runtime is that the user could use it for any size
	//and any size is a rather large number. So rather than a hack job, I chose to cut the weight and use a compiler macro for that silky smooth action. nns.
}