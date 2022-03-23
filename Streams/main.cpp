#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<set>
#include"DynamicArray.h"
#include"Stream.h"
#include"Templates.h"
#include"Python.h"
using namespace std;
using namespace Templates;



int main()
{
	/*Some Examples*/
	
	DynamicArray<int> haha = { 1,2,3 };
	vector<int> vec = { 10,20,30 };
	auto vec_s = Stream(vec);
	cout << "equals = " << (vec_s.equals(vector<int>{ 10, 20, 30 }) ? "true" : "false") << endl;
	cout << "sum(vec) = " << vec_s.sum() << " prod(vec) = " << vec_s.prod() <<
		" max = " << vec_s.max() <<
		" min = " << vec_s.reduce(Min<>,INT_MAX) << endl;

	Stream("abcd").map<char>(next_char).filter(EvenIndices()).forEach(print<char>).then(dropLine);

	Stream(list<int>{ 1,2,3 }).forEach(print<int>).then(dropLine);
	Stream(haha).map<int>(Multiplier<>(5))
		        .filter(GreaterInt(5))
		        .forEach(print<int>) 
		        .finally(dropLine);

	cout << "*******" << endl;
	Stream(range(5,10)).forEach(print<int>).then(dropLine);// 5 6 7 8 9
	if (Stream(range(5, 10)).any(GreaterInt(6))) 
	{
		cout << Stream(range(5, 10)).count(GreaterInt(6)) << endl;
	}

	//modify an array
	Stream(vec).forEach([&vec](int index, auto& item) {vec[index] = item += 10; });
	vec = Stream(vec).map<int>([](int x) {return x + 10; }).toVector();

	



}