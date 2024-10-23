#include "Header.h"

void fillDB()
{
	int tmp;
	cout << "Enter number of source --> "; cin >> tmp;
	for (size_t i = 0; i < tmp; i++)
	{
		Source temp;
		editSource(temp);
		save(temp);
	}
}

void editSource(Source& source)
{
	int tmp;
	cout << "Enter type fo source ([1] - BOOK, [2] - MAGAZINE, [3] - NEWSPAPER) --> ";
	cin >> tmp;
	source.type = (Type)tmp;

	cin.ignore();
	cout << "Enter title  --> "; cin.getline(source.name, SIZE);
	if (source.type == Type::BOOK)
	{
		cout << "Enter author --> "; cin.getline(source.author, SIZE);
		cout << "Enter genre  --> "; cin.getline(source.genre, SIZE);
	}
	cout << "Enter year   --> "; cin >> source.year;
}

void print(Source source, int index)
{
	string line = "==================================";
	cout << "\n\t" << line << " " << (index != -1 ? "#" + to_string(index) + " " : "") << (source.type == Type::BOOK ? "BOOK" : (source.type == Type::MAGAZINE) ? "MAGAZINE" : "NEWSPAPER") << " " << line << endl;
	cout << "\t\t Title  :: " << source.name << endl;
	if (source.type == Type::BOOK)
	{
		cout << "\t\t Author :: " << source.author << endl;
		cout << "\t\t Genge  :: " << source.genre << endl;
	}
	cout << "\t\t Year   :: " << source.year << endl;
}

void printAll(Source* sources, const int& size, bool numeric)
{

	for (size_t i = 0; i < size; i++)
	{
		numeric ? print(sources[i], i + 1) : print(sources[i]);
	}
}

void save(Source source, string fname)
{
	ofstream file(fname, ios_base::app | ios_base::binary);
	if (!file.is_open()) {
		cout << "Error" << endl;
		return;
	}

	file.write((char*)&source, sizeof(Source));
	file.close();
}

Source* read(int& size, string fname)
{
	ifstream file(fname);
	if (!file.is_open()) {
		cout << "Error file read" << endl;
		return nullptr;
	}

	file.seekg(0, ios_base::end);
	if (file.tellg() == 0)
	{
		cout << "Error file read" << endl;
		return nullptr;
	}
	size = file.tellg() / sizeof(Source);
	file.seekg(0);

	Source* tmp = new Source[size];
	for (size_t i = 0; i < size; i++)
	{
		file.read((char*)&tmp[i], sizeof(Source));
	}
	file.close();
	return tmp;
}

void clear(Source*& sources, int& size)
{
	if (sources != nullptr)
	{
		delete[] sources;
		sources = nullptr;
		size = 0;
	}
}

void remove_(Source* sources, const size_t& size, const int& id, string fname)
{
	remove(fname.c_str());
	for (size_t i = 0; i < size - 1; i++)
	{
		i < (id - 1) ? save(sources[i]) : save(sources[i + 1]);
	}
}

bool compareSources(const Source& a, const Source& b) {
	if (a.type == b.type) {
		return strcmp(a.name, b.name) < 0;
	}
	return a.type < b.type;
}

void sortSources(Source* sources, int size, string fname) {
	sort(sources, sources + size, compareSources);

	ofstream file(fname, ios_base::trunc | ios_base::binary);
	if (!file.is_open()) {
		cout << "Error opening file for sorting" << endl;
		return;
	}

	for (size_t i = 0; i < size; ++i) {
		file.write((char*)&sources[i], sizeof(Source));
	}

	file.close();
}



void FindSources(const Source* sources, int size)
{
	int choice;
	cout << "Search by: \n[1] - Author\n[2] - Name\nEnter your choice-  ";
	cin >> choice;

	string search;
	if (choice == 1) {
		cout << "Enter author -  ";
		cin.ignore();
		getline(cin, search);
	}
	else if (choice == 2) {
		cout << "Enter name - ";
		cin.ignore();
		getline(cin, search);
	}
	else {
		cout << "error\n";
		return;
	}

	int choice_2;
	cout << "Enter type of source ([1] - BOOK, [2] - MAGAZINE, [3] - NEWSPAPER) -  ";
	cin >> choice_2;

	Type searchTP;
	switch (choice_2) {
	case 1:
		searchTP = BOOK;
		break;
	case 2:
		searchTP = MAGAZINE;
		break;
	case 3:
		searchTP = NEWSPAPER;
		break;
	default:
		cout << "eror.\n";
		return;
	}

	bool found = false;
	for (size_t i = 0; i < size; i++) {
		if (sources[i].type == searchTP) {
			if ((choice == 1 && strcmp(sources[i].author, search.c_str()) == 0) ||
				(choice == 2 && strcmp(sources[i].name, search.c_str()) == 0)) {
				print(sources[i]);
				found = true;
			}
		}
	}

	if (!found) {
		cout << "not found.\n";
	}
}
void neznau(Source* sources, const int size) {
	int choice;
	cout << "Select - \n[1] - Books by Author and Category\n[2] - Magazines by Year\nEnter your choice -  ";
	cin >> choice;

	if (choice == 1) {
		string author, category;
		cout << "Enter author: ";
		cin.ignore();
		getline(cin, author);
		cout << "Enter category: ";
		getline(cin, category);

		cout << "Books by " << author << " in category " << category << " - \n";
		for (size_t i = 0; i < size; i++) {
			if (sources[i].type == BOOK && strcmp(sources[i].author, author.c_str()) == 0 && strcmp(sources[i].genre, category.c_str()) == 0) {
				print(sources[i]);
			}
		}
	}
	else if (choice == 2) {
		int year;
		string magazineName;
		cout << "Enter year: ";
		cin >> year;
		cout << "Enter magazine name - ";
		cin.ignore();
		getline(cin, magazineName);

		cout << "Magazines named '" << magazineName << "' from year " << year << " -\n";
		for (size_t i = 0; i < size; i++) {
			if (sources[i].type == MAGAZINE && sources[i].year == year && strcmp(sources[i].name, magazineName.c_str()) == 0) {
				print(sources[i]);
			}
		}
	}
	else {
		cout << "Invalid choice. Try again.\n";
	}
}
int countBooks(Source* sources, int size, const string& category) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (sources[i].type == Type::BOOK && category == sources[i].genre) {
			count++;
		}
	}
	return count;
}
void removeNewspaper(Source*& sources, int& size, int year, const string& fname) {
	int newSize = 0;

	Source* temp = new Source[size];

	for (int i = 0; i < size; i++) {
		if (!(sources[i].type == Type::NEWSPAPER && sources[i].year == year)) {
			temp[newSize++] = sources[i];
		}
	}

	remove(fname.c_str());
	for (int i = 0; i < newSize; i++) {
		save(temp[i], fname);
	}

	clear(sources, size);
	sources = temp;
	size = newSize;
}