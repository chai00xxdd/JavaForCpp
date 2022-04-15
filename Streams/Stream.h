#pragma once
#include<string>
#include<vector>
#include<functional>
#include<iostream>
#include <numeric>
#include<algorithm>
#include"Templates.h"
using namespace std;
using namespace Templates;


/*Stream class!!!!!!!!!!*/
namespace JavaInterface
{
	template<class T>//DS is to be able to change the original data struct
	class StreamClass
	{
	private:
		vector<T> ds;
	public:

		template<class DS>
		StreamClass(const DS& ds) :ds(ds.begin(), ds.end()) {}

		StreamClass<T> filter(std::function<bool(const T&item)> pred)
		{
			return filter([&](int index, const T& item) {return pred(item); });
		}

		StreamClass<T> filter(std::function<bool(int index, const T& item)> pred)
		{
			vector<T> filterd;
			forEach([&pred, &filterd](int index,const T& item) {
				If(pred(index,item)).then(InsertBack(filterd, item));
			});

			return filterd;
		}

		template<class Action>
		void finally(const Action& action)
		{
			action();
		}

		template<class Action>
		StreamClass<T>& then(const Action& action)
		{
			action();
			return *this;
		}


		StreamClass<T>& forEach(const std::function<void(T& item)>& callback)
		{
			std::for_each(ds.begin(), ds.end(), callback);
			return *this;
		}

		StreamClass<T>& forEach(const std::function<void(int index, T& item)>& callback)
		{
			return enumrate(callback);
		}

		StreamClass<T>& enumrate(const std::function<void(int index, T& item)>& callback)
		{
			int index = 0;
			forEach([&](T& item) {callback(index++, item); });
			return *this;
		}

		StreamClass<T>& sort()
		{
			std::sort(ds.begin(), ds.end());
			return *this;
		}

		int size() { return ds.size(); }

		template<class TO>
		StreamClass<TO> map(const std::function<TO(int index,const T& item)>& map_func)
		{
			vector<TO> mapped(size());
			forEach([&](int index,const T& item) {mapped[index] = map_func(index,item); });
			return mapped;

		}

		template<class TO>
		StreamClass<TO> map(const std::function<TO(const T& item)>& map_func)
		{
			return map<TO>([&](int index, const T& item) {return map_func(item); });
		}

		template<class Pred>
		bool any(const Pred& pred)
		{
			return std::any_of(ds.begin(), ds.end(), pred);
		}

		template<class Pred>
		bool all(const Pred& pred)
		{
			return !any([&](const T& item) {return !pred(item); });
		}
		vector<T> toVector()
		{
			return vector<T>(ds.begin(), ds.end());;
		}

		list<T> toList()
		{
			return list<T>(ds.begin(), ds.end());
		}

		StreamClass<T> reverse()
		{
			vector<T> reversed = ds;
			std::reverse(ds.begin(), ds.end());
			return reversed;
		}



		T reduce(std::function<T(const T& item1, const T& item2)>func, const T& init_value = T())
		{
			return std::accumulate(ds.begin(), ds.end(), init_value, func);
		}

		template<class DS>
		bool equals(const DS& other)
		{
			auto itr = other.begin();
			return other.size() == size()
				&& all([&itr](const T& t) {return t == *itr++; });
		}


		int count(const std::function<bool(const T&item)> pred)
		{
			return filter(pred).size();
		}

		double sum()
		{
			return reduce(Sum<T>, 0);
		}

		double prod()
		{
			return reduce(Mul<T>, 1);
		}

		T max()
		{
			return reduce(Max<T>, *ds.begin());
		}

		T min()
		{
			return reduce(Min<T>, *ds.begin());
		}


	};


	/*This Templates functions are for not using <T> when creating the classs its looks better that way
	otherwise for string we will need to do StreamClass<char>(str);
	*/

	template <template<class, class> class H, class DT, class K>
	StreamClass<DT> Stream(const H<DT, K>& ds) {
		return ds;
	}

	/*String support*/
	StreamClass<char> Stream(const string& str)
	{
		return str;
	}

	/*Set support*/
	template<class T>
	StreamClass<T> Stream(const set<T>& i_set)
	{
		return i_set;
	}

	/*Other*/
	template<template<class> class DS, class T>
	StreamClass<T> Stream(const DS<T>& ds)
	{
		return ds;
	}
}





