#pragma once
#include <string>
#include <sstream>
using namespace std;

namespace gugw {
	template <typename T>
	string to_string(T value)
	{
		ostringstream oss;
		oss << value;
		return oss.str();
	}

	template <typename T>
	T string_to(string value, T)
	{
		T result;
		istringstream iss(value);
		iss >> result;
		return result;
	}

	vector<string> split(string str, char delimiter) {
		vector<string> arrays;
		string tmpstr;
		while (!str.empty()) {
			int ind = str.find_first_of(delimiter);
			if (ind == -1) {
				arrays.push_back(str);
				str.clear();
			}
			else {
				arrays.push_back(str.substr(0, ind));
				str = str.substr(ind + 1, str.size() - ind - 1);
			}
		}
		return arrays;
	}
	
}