#pragma once
#include<functional>
#include<iostream>
using namespace std;
namespace Templates
{
	void dropLine() { cout << endl; }
	char next_char(char c) { return c + 1; }
	template<class T>
	void print(const T& t)
	{
		cout << t << " ";
	}

	template<class T = int>
	class Greater
	{
	private:
		T x;
	public:
		Greater(const T& x) :x(x) {}
		bool operator()(const T& y) const { return y > x; }

	};

	using GreaterInt = Greater <>;

	template<class T = int>
	class Multiplier
	{
	private:
		T by;
	public:
		Multiplier(const T& by) :by(by) {}
		int operator()(const T& x) const { return x * by; }

	};

	class If
	{
	private:
		bool condition;
	public: 
		If(bool condition):condition(condition){}
		void then(std::function<void(void)> func)
		{
			if (condition)
				func();
		}
		void elseDo(std::function<void(void)> func)
		{
			if (!condition)
				func();
		}
		
	};

	class EvenIndices
	{
	public:
		template<class T>
		bool operator()(int index, const T& item) { return index % 2 == 0; };
	};
	

	template<class DS,class Item>
	std::function<void(void)> InsertBack(DS&ds, const Item&item)
	{
		return [&ds, &item]() {ds.push_back(item); }; // return a void function specilizer 
	}

	template<class T = int>
	T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	
	
}






