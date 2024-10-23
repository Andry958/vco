#include "Header.h"

using namespace std;

int main()
{
	int choice;

	Source* sources = nullptr;
	int size = 0;
	string fname = "data.txt";
	while (true)
	{
		cout << "\t [1] - fill db; \n\t [2] - print; \n\t [3] - add; \n\t [4] - remove; \n\t [5] - sort; \n\t [0] - exit; \n\t\t Enter :: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			fillDB();
			break;
		case 2:
			clear(sources, size);
			sources = read(size);
			if (sources == nullptr) {
				continue;
			}
			printAll(sources, size);
			break;
		case 3: {
			Source tmp;
			editSource(tmp);
			save(tmp);
			break;
		}
		case 4: {
			clear(sources, size);
			sources = read(size);
			if (sources == nullptr) {
				continue;
			}
			printAll(sources, size, true);
			int id;
			cout << "Enter #id :: ";
			cin >> id;

			remove_(sources, size, id);
			size--;
			break;
		}
		case 5: {
			clear(sources, size);
			sources = read(size, fname);
			if (sources == nullptr) {
				continue;
			}
			sortSources(sources, size, fname);
			cout << "sorted!" << endl;
			break;
		}
		case 6: {
			clear(sources, size);
			sources = read(size, fname);
			if (sources == nullptr) {
				continue;
			}
			FindSources(sources, size);
			break;
		}
		case 7: {
			clear(sources, size);
			sources = read(size, fname);
			if (sources == nullptr) {
				continue;
			}
			neznau(sources, size);

			break;
		}
		case 8: {
			string category;
			cout << "Enter category (genre) to count books - ";
			cin.ignore();
			getline(cin, category);

			clear(sources, size);
			sources = read(size, fname);
			if (sources == nullptr) {
				continue;
			}

			int count = countBooks(sources, size, category);
			cout << "Number of books in category \"" << category << "\"- " << count << endl;
			break;
		}
		case 9: {
			int year;
			cout << "Enter the year to remove newspapers - ";
			cin >> year;

			clear(sources, size);
			sources = read(size, fname);
			if (sources == nullptr) {
				continue;
			}

			removeNewspaper(sources, size, year, fname);
			cout << "Newspapers from year " << year << " removed" << endl;
			break;
		}
		case 0:
			clear(sources, size);
			return 0;
		default:
			cout << "error\n";
			break;
		}
	}
}