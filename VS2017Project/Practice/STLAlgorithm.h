#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace gugw_stl {
	struct coutVector
	{
	public:
		void operator()(int i)
		{
			cout << " " << i;
		}
	};

	struct compare1
	{
		bool operator()(int i, int j)
		{
			cout << "compare" << i << " vs " << j << endl;
			if (i > j)
				return true;
			else
				return false;
		}
	};



	class Name
	{
	private:
		string first;
		string second;
	public:
		Name(const string &name1, const string&name2) :first(name1), second(name2) {}
		Name() = default;
		string get_first() const { return first; }
		string get_second() const { return second; }

		friend istream& operator>>(istream &in, Name& name);
		friend ostream& operator<<(ostream& out, const Name& name);

	};
	// Stream input for Name objects
	inline std::istream& operator>>(std::istream& in, Name& name)
	{
		return in >> name.first >> name.second;
	}
	// Stream output for Name objects
	inline std::ostream& operator<<(std::ostream& out, const Name& name)
	{
		return out << name.first << " " << name.second;
	}

	struct compareName
	{
		bool operator()(const Name& name1, const Name& name2)
		{
			return name1.get_second() < name2.get_second();
		}
			
	};
	class SortStudy
	{
	public:
		void testSortIntVector()
		{
			vector<int> numers1{ 1,3,5,2,4,6,0 };
			vector<int> numers{ 1,3,5,2,4,6,0 };
			sort(begin(numers), end(numers));
			for_each(begin(numers), end(numers), coutVector());
			cout << "\n ===========================================" << endl;

			//�������˵�һ�������һ��Ԫ������
			sort(++begin(numers), --end(numers));
			for_each(++begin(numers), --end(numers), coutVector());
			cout << "\n ===========================================" << endl;

			sort(begin(numers), end(numers), compare1());
			for_each(begin(numers), end(numers), coutVector());
			cout << "\n ===========================================" << endl;
		}
		void testSortClassVector()
		{
			std::vector<Name> names;
			names.push_back(Name("a","3"));
			names.push_back(Name("a", "2"));
			names.push_back(Name("c", "1"));
			names.push_back(Name("b", "1"));
			cout << "\n ====sort�Զ���ṹ�࣬�Զ������򷽷�====" << endl;
			std::sort(std::begin(names), std::end(names), compareName());
			for_each(begin(names), end(names), [](const Name& name) { cout << name.get_first() << name.get_second() << endl; });
		}
		void testStableSortClassVector()
		{
			std::vector<Name> names;
			names.push_back(Name("a", "3"));
			names.push_back(Name("a", "2"));
			names.push_back(Name("c", "1"));
			names.push_back(Name("b", "1"));
			cout << "\n ====StableSort�Զ���ṹ�࣬�Զ������򷽷�====" << endl;
			std::stable_sort(std::begin(names), std::end(names), compareName());
			for_each(begin(names), end(names), [](const Name& name) { cout << name.get_first() << name.get_second() << endl; });
		}
		void testnth_elementVector()
		{
			cout << "\n ===========================================" << endl;
			vector<int> numers{ 1,2,3,7,7,6,7,8,6,3,5,2,4,6,0 };
			//�� 5 ��Ԫ�� (6)֮ǰ��Ԫ�ض�С������������������ġ�ͬ������ 5��Ԫ�غ��Ԫ�ض�����������Ҳ�����������
			nth_element(begin(numers), begin(numers)+5,end(numers));
			for_each(begin(numers), end(numers), coutVector());
			
		}
	};

	class FindStudy
	{
	public:
		void testFind_if()
		{
			int value = 5;

			vector<int> numers{ 1,2,3,7,7,6,7,8,6,3,5,2,4,6,0 };
			cout << "\n =======find_if====================" << endl;
			auto iter = find_if(numers.begin(), numers.end(), [value](int n) -> bool { return n > value; });
			if (iter != end(numers))
			{
				cout << *iter << endl;
			}
		}
		void testFind_if_not()
		{
			int value = 5;

			vector<int> numers{ 1,2,3,7,7,6,7,8,6,3,5,2,4,6,0 };
			cout << "\n =======find_if_not=================" << endl;
			//=��ʾ���б���������ֵ��lambada�С�
			auto iter = find_if_not(numers.begin(), numers.end(), [=](int n) -> bool { return n > value; });

			if (iter != end(numers))
			{
				cout << *iter << endl;
			}
		}
		void testFind_first_of()
		{
			string text{ " e am a child" };
			string text2{ "child" };
			//Ѱ����text�е�һ��������text2������λ�õ�Ԫ��
			auto iter = find_first_of(text.begin(), text.end(), text2.begin(), text2.end());
			if (iter != text.end())
			{
				cout << "find first of " << *iter << endl;
			}
			
		}

		void testSearch()
		{
			//��ѯ�Ӵ�
			string text{ "Hello  boy boy \"boy\", boy boy \"boy boy\"."" \"boy boy\" boy boy  are good\' boy." };
			std::cout << text << std::endl;
			string phrase{ "boy boy" };
			size_t count{};
			auto iter = std::begin(text);
			auto end_iter = end(text);
			//���Դ�Сд
			while ((iter = std::search(iter, end_iter, std::begin(phrase), std::end(phrase), [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); })) != end_iter)
			{
				++count;
				std::advance(iter, phrase.size()); // Move to beyond end of subsequence found
			}
			std::cout << "\n\"" << phrase << "\" was found " << count << " times." << std::endl;
			
		}
		void testBinarySearch()
		{
			std::vector<int> values{ 17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43 };
			sort(values.begin(), values.end(), less<int>());
			for_each(begin(values), end(values), coutVector());
			int wanted{ 22 };   
			//����ֵΪtrue����false�����õ�Ҳ��lower_bound������
			if (std::binary_search(std::begin(values), std::end(values), wanted))
				std::cout << wanted << " found" << std::endl;
			else
				std::cout << wanted << " not found" << std::endl;
		}
		void testEqualRange()
		{
			std::vector<int> values{ 17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43 };
			sort(values.begin(), values.end(), less<int>());
			for_each(begin(values), end(values), coutVector());
			int wanted{ 22 };
			//11 17 22 36 40 43 48 54 61 70 78 82 89 92 99
			auto pr = std::equal_range(std::begin(values), std::end(values), wanted);
			//22
			std::cout << "the lower bound for " << wanted << " is " << *pr.first << std::endl;
			//36
			std::cout << "Tthe upper bound for " << wanted << " is " << *pr.second << std::endl;
		}
		void testLowerBound()
		{
			std::vector<int> values{ 17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43 };
			sort(values.begin(), values.end(), less<int>());
			for_each(begin(values), end(values), coutVector());
			int wanted{ 22 };
			//11 17 22 36 40 43 48 54 61 70 78 82 89 92 99
			auto pr = std::lower_bound(std::begin(values), std::end(values), wanted);
			//22
			std::cout << "the lower bound for " << wanted << " is " << *pr << std::endl;
			//11 17 22 36 40 43 48 54 61 70 78 82 89 92 99
		 pr = std::upper_bound(std::begin(values), std::end(values), wanted);
			//36
			std::cout << "the lower bound for " << wanted << " is " << *pr << std::endl;
		}
	};

	class CopyStudy
	{
	public:
		void testCopy()
		{
			std::vector<string> names{ "A1","Beth", "Carol", "Dan", "Eve","Fred","George" ,"Harry", "Iain", "Joe" };
			vector<string> names2;
			names2.reserve(20);
			copy(names.begin(), names.end(), inserter(names2,begin(names2)));
			for_each(begin(names2), end(names2), [](string str)-> void { cout << str << endl; });
		}
	
	};
}