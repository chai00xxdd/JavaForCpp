#pragma once
#include"Stream.h"
void dropLine() { cout << endl; }
char next_char(char c) { return c + 1; }
template<class T>
void print(const T& t)
{
	cout << t << " ";
}

vector<int> range(int num)
{
	vector<int> range_v(num);
	int index = 0;
	range_v = Stream(range_v).forEach([&index](int& x) {x = index++; }).toVector();
	return range_v;
}


vector<int> range(int start,int end)
{
	vector<int> range_v(end-start);
	range_v = Stream(range_v).forEach([&start](int& x) {x = start++; }).toVector();//could use map to
	return range_v;

}
