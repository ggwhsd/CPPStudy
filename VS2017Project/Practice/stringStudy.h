#pragma once
#include <string>
#include <sstream>
using namespace std;

namespace gugw {
	//耗时相对itoa和sprintf延长了八倍，在无法通过其他环节提升速度时候，考虑这个替换为sprintf。
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
	
	class StringStudy
	{
		string str;
	public:
		void testSwap()
		{
			str = "bbbbbbb";
			string str2 = "aaaaa";
			std::cout << "now str=" << str << " str2=" << str2 << std::endl;
			str.swap(str2);
			std::cout << "now str=" << str << " str2=" << str2 << std::endl;
		}
		void testSubAndFindStr()
		{

			int i = 0;
			int testCount = 100;
			string result;
			string sessionId;
			string frontId;
			string orderref;
			//mts1 = tt1.getNowForMicro();
			while (i < testCount) {

				sessionId = to_string(223322233);
				frontId = to_string(111);
				orderref = "   3333333";
				result = sessionId.append(frontId).append(orderref);

				i++;
			}
			//mts2 = tt1.getNowForMicro();
			//cout << (double)(mts2 - mts1).count() / testCount << endl;
			i = 0;
			//mts1 = tt1.getNowForMicro();
			while (i < testCount) {

				char OrderRef[11 + 11 + 13];
				sprintf(OrderRef, "%10d@", 223322233);
				sprintf(&OrderRef[11], "%10d@", 111);
				strcpy_s(&OrderRef[22], 13, "   333333311");


				i++;
			}

			//mts2 = tt1.getNowForMicro();
			//cout << (double)(mts2 - mts1).count() / testCount << endl;

			string ss = "123123@111@   3333";
			int index = ss.find('@');

			string s1 = ss.substr(0, index);
			int index2 = ss.find('@', index + 1);

			string s2 = ss.substr(index + 1, index2 - index - 1);
			int index3 = ss.find('@', index2 + 1);
			string s3 = ss.substr(index2 + 1);

			index = ss.find_last_of('@');
			string s4 = ss.substr(index + 1);
			cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
			system("pause");
		}
	};
}