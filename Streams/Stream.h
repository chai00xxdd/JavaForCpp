#pragma once
#include<string>
#include<vector>
#include<functional>
#include<iostream>
#include <numeric>
using namespace std;


/*Stream class!!!!!!!!!!*/

template<class T>//DS is to be able to change the original data struct
class StreamClass
{
private:
	vector<T> ds; 
public: 
	
	template<class DS>
	StreamClass(const DS& ds) :ds(ds.begin(), ds.end()) {}
	
	  template<class Pred>
	  StreamClass<T> filter(const Pred& pred)
	  {
		  vector<T> filterd;
		  int index = 0;
		  forEach([&pred, &index, &filterd](const T& item) {
			  if (pred(item))
			  {
				  filterd.push_back(item);
			  }
		  });

		  return { (const vector<T>&)filterd };
	  }

	  template<class Action>
	  void finally(const Action&action)
	  {
		  action();
	  }

	  template<class Action>
	  StreamClass<T>& then(const Action& action)
	  {
		  action();
		  return *this;
	  }

	  
	  StreamClass<T> & forEach(const std::function<void(T & item)> &callback)
	  {  
		std::for_each(ds.begin(), ds.end(), callback); 
		return *this;
	  }

	  void forEach(const std::function<void(int index,T& item)>& callback)
	  {
		  int index = 0;
		  forEach([&]( T& item) {callback(index++, item); });
	  }

	  void enumrate(const std::function<void(int index, T& item)>& callback)
	  {
		  int index = 0;
		  forEach([&]( T& item) {callback(index++, item); });
	  }

	  int size() { return ds.size(); }

	  template<class TO>
	  StreamClass<TO> map(const std::function<TO(const T& item)>& map_func)
	  {
		  vector<TO> mapped(size());
		  int index = 0;
		  forEach([&index,&mapped,&map_func](const T& item) {mapped[index++] = map_func(item); });
		  
		  return mapped;

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

	  StreamClass<T> reverse()
	  {
		  vector<T> reversed = ds;
		  std::reverse(ds.begin(), ds.end());
		  return reversed;
	  }

	 

	  T reduce(std::function<T(const T& item1, const T& item2)>func,const T &init_value = T())
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

	  double sum()
	  {
		  return reduce([](const T& item1, const T& item2) {return item1 + item2; }, 0);
 	  }

	  double prod()
	  {
		  return reduce([](const T& item1, const T& item2) {return item1 * item2; }, 1);
	  }

	  T max()
	  {
		  return reduce([](auto& item1, auto& item2) {return item1 > item2 ? item1 : item2; }, *ds.begin());
	  }

	  T min()
	  {
		  return reduce([](auto& item1, auto& item2) {return item1 > item2 ? item2 : item1; }, *ds.begin());
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
template<template<class> class DS,class T>
StreamClass<T> Stream(const DS<T>& ds)
{
	return ds;
}




