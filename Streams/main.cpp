#include<iostream>
#include<vector>
#include<list>
#include<array>
#include<algorithm>
#include<string>
#include<set>
#include"DynamicArray.h"
using namespace std;
#include"Stream.h"
#include"Templates.h"




int main()
{
	/*Some Examples*/
	DynamicArray<int> haha = { 1,2,3 };
	vector<int> vec = { 10,20,30 };
	auto vec_s = Stream(vec);
	cout << "equals = " << (vec_s.equals(vector<int>{ 10, 20, 30 }) ? "true" : "false") << endl;
	cout << "sum(vec) = " << vec_s.sum() << " prod(vec) = " << vec_s.prod() <<
		" max = " << vec_s.max() <<
		" min = " << vec_s.reduce([](auto& item1, auto& item2) {return std::min(item1, item2); },INT_MAX) << endl;

	Stream("abcd").map<char>(next_char).forEach(print<char>).then(dropLine);

	Stream(list<int>{ 1,2,3 }).forEach(print<int>).then(dropLine);
	Stream(haha).forEach([](auto& x) {x = x * 5; }) 
		        .forEach(print<int>) 
		        .finally(dropLine);

	cout << "*******" << endl;
	Stream(range(5,10)).forEach(print<int>).then(dropLine);// 5 6 7 8 9
	if (Stream(range(5, 10)).all([](int x) {return x > 3; })) //can use any to
	{
		cout << "yup dude" << endl;
	}

	//modify an array
	Stream(vec).forEach([&vec](int index, auto& item) {vec[index] = item += 10; });
	vec = Stream(vec).map<int>([](int x) {return x + 10; }).toVector();

	



}