#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;
#define PATH "..\\Catalog\\info.txt"
class Book
{
	size_t code;
	string name;
	string author;
	size_t year;
public:
	Book(size_t _code, string _name, string _author, size_t _year):
		   code(_code), name(_name), author(_author), year(_year)
	{
		string _n = "\0", _a = "\0";
		if (_name == _n) name = "Empty!";
		if (_author == _a) author = "Empty!";
	}
	
	bool set_name(string _name)
	{
		name = _name;
		return true;
	}
	bool set_author(string _author)
	{
		author = _author;
		return true;
	}
	bool set_year(size_t _year)
	{
		year = _year;
		return true;
	}

	size_t get_code()const
	{
		return code;
	}
	string get_name()const
	{
		return name;
	}
	string get_author()const
	{
		return author;
	}
	size_t get_year()const
	{
		return year;
	}

	void show_book()
	{
		cout << "\nCode:   " << get_code()
			 << "\nName:   " << get_name()
			 << "\nAuthor: " << get_author()
			 << "\nYear:   " << get_year() << "\n\n";
	}

	void change_book(string _name, string _author, size_t _year)
	{
		set_name(_name);
		set_author(_author);
		set_year(_year);
	}




};


class Catalog_books {
	vector<Book> arr;
public:
	Catalog_books()
	{
		fstream f;
		f.open(PATH, fstream::in);
		if (!(f.is_open()))  cout << "Error opening file!!!\n";
		string co, na, au, ye, str;
		size_t code_int, year_int;
		while (!f.eof())
		{
			getline(f, str);
			if (str == "\0") break;
			co = str.substr(0, str.find_first_of('|'));
			str.erase(0, str.find_first_of('|')+1);

			na = str.substr(0, str.find_first_of('|'));
			str.erase(0, str.find_first_of('|')+1);

			au = str.substr(0, str.find_first_of('|'));
			str.erase(0, str.find_first_of('|')+1);

			ye = str.substr(0, str.find_first_of('|'));
			str.empty();

			code_int = stoi(co);
			year_int = stoi(ye);

			add_book((Book (code_int, na, au, year_int) ));
			
		}
		f.close();
	}
	
	~Catalog_books()
	{
		fstream f;
		f.open(PATH, fstream::out);
		for (size_t i = 0; i < arr.size(); i++)
		{
			f  << arr[i].get_code() << "|" << arr[i].get_name() << "|" << arr[i].get_author() << "|" << arr[i].get_year() << "|\n";
		}
	}

	Book& operator[] (int ind)
	{
		return arr.at(ind);
	}
	
	size_t code_code()const
	{
		if (arr.size())
			return arr[arr.size() - 1].get_code();
		else return 1110;
	}

	bool add_book(const Book& obj)
	{
		arr.push_back(obj);
		return true;
	}

	int find_code(int _code)const
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (arr[i].get_code() == _code) return i;

		return -1;
	}
	int find_name(string _name)const
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (arr[i].get_name() == _name) return i;

		return -1;
	}
	int find_author(string _author)const
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (arr[i].get_author() == _author) return i;

		return -1;
	}
	int find_year(size_t _year)const
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (arr[i].get_year() == _year) return i;

		return -1;
	}

	bool del_book(size_t code)
	{
		if (find_code(code) == -1) return false;
		vector<Book>::iterator it = arr.begin();
		int k = 0;
		for (int k = 0; it != arr.end(); it++)
		{
			if (find_code(code) == k) { it = arr.erase(it); return true; }
			k++;
		}
		return false;
	}

	bool change_book(size_t _code, string _name, string _author, size_t _year)
	{

		int ind = find_code(_code);
		if (ind == -1) return false;

		arr[ind].set_name(_name);
		arr[ind].set_author(_author);
		arr[ind].set_year(_year);
		return true;
	}

	void all_books()const
	{
		if (arr.size())
		{
			
			for (size_t i = 0; i < arr.size(); i++)
				cout << "\nCode:   " << arr[i].get_code()
				<< "\nName:   " << arr[i].get_name()
				<< "\nAuthor: " << arr[i].get_author()
				<< "\nYear:   " << arr[i].get_year() << "\n\n";
		}
		else cout << "\nEmpty catalog";
	}
};

int main()
{
	Catalog_books c;
	char q = 'q';
	size_t main_code = (c.code_code() + 1), cin_year, cin_code;
	string cin_name, cin_author;

	cout << "You're welcome in book catalog.\n";
	while (q != '0')
	{
		cout << "\n\n\
1 - See all the books\n\
2 - Add new book\n\
3 - Change selected book\n\
4 - Delete selected book\n\
5 - Search for some book\n\
       0 - Exit\n\n";
		cin >> q;
		switch (q)
		{
		case'1':
			c.all_books(); break;


		case'2':
			cout << "Enter the book's Name: ";
			getchar();
			getline(cin, cin_name);
			cout << "Enter the book's Author: ";
			getline(cin, cin_author);
			cout << "Enter the book's Year: ";
			cin >> cin_year;
			while (cin_year < 1 || cin_year > 2050) { cout << "Wrong year!!!\nTry again\n"; cin >> cin_year; }
			cout << "Book added.\n";
			c.add_book(Book(main_code++, cin_name, cin_author, cin_year));
			break;


		case'3':
			cout << "Enter the book's Code: ";
			cin >> cin_code;
			cout << "Enter the book's Name: ";
			getchar();
			getline(cin, cin_name);
			cout << "Enter the book's Author: ";
			getline(cin, cin_author);
			cout << "Enter the book's Year: ";
			cin >> cin_year;
			while (cin_year < 1 || cin_year > 2050) { cout << "Wrong year!!!\nTry again\n"; cin >> cin_year; }
			cout << "Book has changed.\n";
			c[c.find_code(cin_code)].change_book(cin_name, cin_author, cin_year); break;


		case'4':
			cout << "Enter code of the book: ";
			cin >> cin_code;
			if (c.find_code(cin_code) == -1) { cout << "\nWrong Code!\n"; break; }
			c.del_book(cin_code);
			cout << "Book has been deleted.\n";
			break;


		case'5':
			cout << "\
1 - Search with Code\n\
2 - Search with Name\n\
3 - Search with Author\n\
4 - Search with Year\n\
        0 - Exit\n\n";


			cin >> q;
			switch (q)
			{

			case'1':
				cout << "Enter the Code\n";
				cin >> cin_code;
				if (c.find_code(cin_code) == -1) { cout << "\nWrong Code!\n"; break; }

				cout << "\n\
Here's your book\n\
      ↓\n";
				c[c.find_code(cin_code)].show_book(); break;


			case'2':
				cout << "Enter the Name\n";
				cin >> cin_name;
				if (c.find_name(cin_name) == -1) { cout << "\nWrong Name!\n"; break; }
				cout << "\n\
Here's your book\n\
      ↓\n";
				c[c.find_name(cin_name)].show_book(); break;


			case'3':
				cout << "Enter the Author\n";
				cin >> cin_author;
				if (c.find_author(cin_author) == -1) { cout << "\nWrong Author!\n"; break; }
				cout << "\n\
Here's your book\n\
      ↓\n";
				c[c.find_author(cin_author)].show_book(); break;


			case'4':
				cout << "Enter the Year\n";
				cin >> cin_year;
				if (c.find_year(cin_year) == -1) { cout << "\nWrong Year!\n"; break; }
				cout << "\n\
Here's your book\n\
      ↓\n";
				c[c.find_year(cin_year)].show_book(); break;


			case'0': break;
			default: cout << "Unknown command!\n\n"; break;


			}

		case'0': break;
		default: cout << "Unknown command!\n\n"; break;


		}
	}
	
}