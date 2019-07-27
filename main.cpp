#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// A subsection can contain multiple values.
class DictionarySection
{
public:
	string section_name; // Original name (a copy string)
	map<string, vector <string> > subsections;
};

// First argument - A section: book, bookable, bookbinder
// Second argument - A list of subsections: adjective, noun, verb (case-sensitive)
typedef map<string, DictionarySection> Dictionary;

string trimSpaces(string s)
{
	if (s.empty()) return s;

	// Trim left spaces.
	int idx = 0;
	while (s[idx] == ' ') { ++idx; }

	s = s.substr(idx);

	// Trim right spaces.
	int size = s.size();
	while (size > 0 && s[size - 1] == ' ') --size;

	s.resize(size);

	return s;
}

// Convert all characters of a string to lowercase.
string toLowerStr(string s)
{
	for (int i = 0; i < (int)s.size(); ++i)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}

void readDictionaryFile(const char *file_name, Dictionary &dictionary_database)
{
	dictionary_database.clear();

	cout << "! Opening data file... " << file_name << endl;

	ifstream ifs(file_name);

	if (!ifs)
	{
		cout << "! Could not open the file! Program will exit." << endl;
		cin.get();
		exit(100);
	}

	cout << "! Loading data..." << endl;

	// Read each line, then process each line.
	string data_line;
	string section_name;
	string subsection_data;

	while (getline(ifs, data_line))
	{
		// Read the section name, then read its subsections.
		// The delimiter is |.
		istringstream iss(data_line);

		getline(iss, section_name, '|');
		DictionarySection &this_section = dictionary_database[toLowerStr(section_name)];

		if (this_section.section_name.size() == 0) {
			this_section.section_name = section_name;
		}

		while (getline(iss, subsection_data, '|'))
		{
			// A subsection's data: [Subsection name] => [Subsection value]
			// It is necessary to trim spaces after obtaining these entries.

			string::size_type pos = subsection_data.find("=>");
			if (pos != string::npos)
			{
				string subsection_name = trimSpaces(subsection_data.substr(0, pos));
				string subsection_value = trimSpaces(subsection_data.substr(pos + 2));

				this_section.subsections[subsection_name].push_back(subsection_value);
			}
		}
	}

	cout << "! Loading completed..." << endl;
	cout << "! Closing data file... " << file_name << "\n\n"; // ifstream will close the file automatically when the function exits.
}



int main()
{
	Dictionary dictionary_database;
	const char *file_name = "./Data.CS.SFSU.txt";

	readDictionaryFile(file_name, dictionary_database);

	cout << "-----DICTIONARY 340 C++-----\n\n";

	bool bQuit = false;
	string input_line;
	string first_arg, second_arg, blah_arg;

	const string indent = "    ";

	while (!bQuit)
	{
		cout << "Search: ";
		getline(cin, input_line);

		istringstream iss(input_line);

		first_arg = ""; second_arg = ""; blah_arg = "";
		iss >> first_arg >> second_arg >> blah_arg;

		string output = indent + "|" + "\n";

		if (first_arg == "!Q") {
			bQuit = true;
			break;
		}

		int count = 0;

		// Case 1: Only up to 2 arguments are allowed. At least one argument is required.
		// Case 2: This is like a tutorial. Typing "one two" will reveal additional information. 
		// Case 3: Only a section name is specified. List all subsections along with their values.
		// Case 4: Both arguments are specified. If a subsection is found, all of its values will be listed.

		if (blah_arg.size() || first_arg.size() == 0) // Case 1
		{
			output += indent + "<Please enter a search key(and a part of speech).>\n";
			count = 1;
		}
		else if(first_arg == "one" && second_arg == "two") // Case 2
		{
			output += indent + "<2nd argument must be a part of speech.>\n";
			count = 1;
		}
		else if (first_arg.size() != 0 && second_arg.size() == 0) // Case 3
		{
			DictionarySection &this_section = dictionary_database[toLowerStr(first_arg)];

			for (auto it = this_section.subsections.begin(); it != this_section.subsections.end(); ++it)
			{
				// A subsection can have multiple values. (std::vector is used)
				vector<string> &subsection_values = it->second;
				for (int i = 0; i < (int)subsection_values.size(); ++i)
				{
					output += indent + this_section.section_name + " [" + it->first + "] : " + subsection_values[i] + "\n";
					count += 1;
				}
			}
		}
		else if(first_arg.size() != 0 && second_arg.size() != 0) // Case 4
		{
			DictionarySection &this_section = dictionary_database[toLowerStr(first_arg)];
			string &subsection_name = second_arg;

			for (auto it = this_section.subsections.begin(); it != this_section.subsections.end(); ++it)
			{
				if (it->first == subsection_name)
				{
					vector<string> &subsection_values = it->second;
					for (int i = 0; i < (int)subsection_values.size(); ++i)
					{
						output += indent + this_section.section_name + " [" + it->first + "] : " + subsection_values[i] + "\n";
						count += 1;
					}
				}
			}
		}

		if (count == 0)
		{
			output += indent + "<Not found.>\n";
		}

		output += indent + "|" + "\n";

		cout << output;
	}

	cout << "\n-----THANK YOU-----\n";
	cout << "Press any key to continue. . .";

	cin.get();
	return 0;
}