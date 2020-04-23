#include <iostream>
#include <fstream>
#include <map>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define COLORED(v) BOLDGREEN << v << RESET

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
	int startIter;
	float width0, width1;
	unsigned char color0[4], color1[4];
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

	// Start iteration
	in.read((char*)&startIter, sizeof(int));

	// Color 0
	in.read((char*)&color0, 4);

	// Color 1
	in.read((char*)&color1, 4);

	// Width 0
	in.read((char*)&width0, sizeof(float));

	// Width 1
	in.read((char*)&width1, sizeof(float));

	in.close();
	cout << "Rules count : " << COLORED(rulesCount) << endl;
	cout << "Init string (" << COLORED(initString.length()) << " bytes) : " << COLORED(initString) << endl;
	for (auto r : rules)
	{
		cout << "Rule '" << COLORED(r.first) << "' (" << COLORED(r.second.length()) << " bytes) : " << COLORED(r.second) << endl;
	}
	cout << "Start iteration : " << COLORED(startIter) << endl;
	cout << "Color 0 : " << COLORED("[")
		<< COLORED((int)(color0[0])) << COLORED(", ")
		<< COLORED((int)(color0[1])) << COLORED(", ")
		<< COLORED((int)(color0[2])) << COLORED(", ")
		<< COLORED((int)(color0[3])) << COLORED("]") << endl;
	cout << "Color 1 : " << COLORED("[")
		<< COLORED((int)(color1[0])) << COLORED(", ")
		<< COLORED((int)(color1[1])) << COLORED(", ")
		<< COLORED((int)(color1[2])) << COLORED(", ")
		<< COLORED((int)(color1[3])) << COLORED("]") << endl;
	cout << "Width 0 : " << COLORED(width0) << endl;
	cout << "Width 1 : " << COLORED(width1) << endl;

	return 0;
}
