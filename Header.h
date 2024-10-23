#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::swap;
using std::to_string;
using std::ofstream;
using std::ifstream;
using std::ios_base;
using std::remove;
using std::sort;

const short SIZE = 50;

enum Type
{
	BOOK = 1, MAGAZINE, NEWSPAPER
};

struct Source
{
	Type type;
	char name[SIZE]{};
	char author[SIZE]{};
	char genre[SIZE]{};
	int year;
};


void fillDB();
void editSource(Source& source);
void print(Source source, int index = -1);
void printAll(Source* sources, const int& size, bool numeric = false);
void save(Source source, string fname = "data.txt");
Source* read(int& size, string fname = "data.txt");
void clear(Source*& sources, int& size);
void remove_(Source* sources, const size_t& size, const int& id, string fname = "data.txt");
bool compareSources(const Source& a, const Source& b);
void sortSources(Source* sources, int size, string fname = "data.txt");
void FindSources(const Source* sources, int size);
void neznau(Source* sources, const int size);
int countBooks(Source* sources, int size, const string& category);
void removeNewspaper(Source*& sources, int& size, int year, const string& fname);
