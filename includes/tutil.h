#ifndef __TUTIL_H__
#define __TUTIL_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>


using std::vector, std::map, std::string;


template<typename T>
vector<T> &operator<<(vector<T>& vec, T value) {
	vec.push_back(value);
	return vec;
}

template<typename T>
vector<T> operator<<(vector<T> vec, T value) {
	vec.push_back(value);
	return vec;
}


template<typename T, typename T2>
T keyAt(map<T, T2> m, int idx) {
	auto it = m.begin();
	std::advance(it, idx);
	return it->first;
}


template<typename T, typename T2>
T2& valueAt(map<T, T2>& m, int idx) {
	auto it = m.begin();
	std::advance(it, idx);
	return it->second;
}

template<typename T, typename T2>
int indexOf(map<T, T2>& m, T key) {
	int idx = 0;
	for (auto it = m.begin(); it != m.end(); it++, idx++)
		if (it->first == key)
			return idx;
        return NULL;
}

template<typename T, typename T2, typename T3>
T keyOf(map<T, T2>& m, T3 value) {
	for (auto it = m.begin(); it != m.end(); it++) {
		T3 value2 = it->second.begin()->first;
		if (value == value2)
			return it->first;
	}
}

template<typename T1>
vector<string> explode(string s1, T1 ch) {
	vector<string> ret;
	string str;
	s1.push_back(ch);
	for (char ch2 : s1) {
		if (ch2 == ch) {
			if (not str.empty())
				ret.push_back(str);
			str.clear();
		} else
			str.push_back(ch2);
	}
	return ret;
}


template<class... T1>
string sto(string code, T1... t) {
	char ret[1024];
	auto v = explode(code, '%');
	auto it = v.begin();
	if (code.find("%") > 0) { 
		sprintf (ret, (*it).c_str());
		it++;
	} else
		ret[0] = '\0';
	[](...){}(([&](T1 v) {
		code = "%s%"+(*it);
		sprintf (ret, code.c_str(), ret, v);
		it++;
	}(std::forward<T1>(t)), 0)...);

	return string(ret);
}


template<class... T>
void log(T... lgs) {
	std::fstream fs;
	fs.open("/sdcard/log.txt", std::fstream::out | std::fstream::app);

	[](...){}(([&](T l) {
		fs << l << std::endl;
	}(std::forward<T>(lgs)),0)...);
	fs.flush();
	fs.close();
}


#endif
