#pragma once
#include<string>
#include<vector>
using namespace std;
class String : public string
{
public:
	 
	 String() = default;
	 String(const string& str) :string(str) {}
	 String& operator=(const string& str) { string::operator=(str); return*this; }
	 String(const char* str) :string(str) {}
	 String& operator=(const char* str) { string::operator=(str); return *this; }
	vector<string> split(char c) {
		string str = "";
		vector<string> res;
		unsigned int index = 0;
		string& string = *this;
		while (index < size())
		{
			str = "";

			while (index < size() && string[index] != c)
			{
				str += string[index++];
			}

			if (str != "")
				res.push_back(str);
			index++;
		}

		return res;
	}
};;