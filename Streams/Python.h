#pragma once
#include<vector>
#include"Stream.h"
using namespace std;
using namespace JavaInterface;
vector<int> range(int num)
{
	vector<int> range_v(num);
	int index = 0;
	range_v = Stream(range_v).forEach([&index](int& x) {x = index++; }).toVector();
	return range_v;
}


vector<int> range(int start, int end)
{
	vector<int> range_v(end - start);
	range_v = Stream(range_v).forEach([&start](int& x) {x = start++; }).toVector();//could use map to
	return range_v;

}