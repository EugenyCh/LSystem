#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
	ifstream in("input.bin", ios::binary);
	if (!in)
	{
		cout << "Error of opening \"input.bin\"" << endl;
		return 1;
	}

	string initString;
	int rulesCount;
	map<char, string> rules;
	int temp;
	char* strTemp;

	// Rules count
	in.read((char*)&rulesCount, sizeof(int));

	// Init string length
	in.read((char*)&temp, sizeof(int));

	// Init string
	strTemp = new char[temp + 1];
	in.read((char*)strTemp, temp);
	strTemp[temp] = 0;
	initString = strTemp;
	delete[] strTemp;

	for (int i = 0; i < rulesCount; ++i)
	{
		// Rule letter
		char ruleName;
		in.read((char*)&ruleName, 1);
		// Rule string length
		in.read((char*)&temp, sizeof(int));
		// Relu definition
		strTemp = new char[temp + 1];
		in.read((char*)strTemp, temp);
		strTemp[temp] = 0;
		rules[ruleName] = strTemp;
		delete[] strTemp;
	}

	in.close();
	cout << "Rules count : " << rulesCount << endl;
	cout << "Init string (" << temp << " bytes) : " << initString << endl;
	for (auto r : rules)
	{
		cout << "Rule '" << r.first << "' (" << r.second.length() << ") : " << r.second << endl;
	}

	return 0;
}
