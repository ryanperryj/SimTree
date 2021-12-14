#pragma once
#include <vector>
#include <string>

template<typename T>
T FromString(std::string s) {
	if (typeid(T) == typeid(int))
		return std::stoi(s);
	if (typeid(T) == typeid(float))
		return std::stof(s);
	if (typeid(T) == typeid(double))
		return std::stod(s);
	if (typeid(T) == typeid(bool)) {
		if (s == "0")
			return false;
		else
			return true;
	}
	std::cerr << "FromString not implemented for this type.\n";
	exit(1);
}

template<typename T>
std::string VectorToString(std::vector<T> v) {
	std::string s = "";
	for (auto i = v.begin(); i != v.end(); i++) {
		s += std::to_string(*i) + " ";
	}
	s.pop_back();
	return s;
}

template<typename T>
std::vector<T> VectorFromString(std::string s) {
	std::vector<T> v;
	int pos = 0;
	int i = s.find_first_of(' ', pos);
	while (i != std::string::npos) {
		v.push_back(FromString<T>(s.substr(pos, i - pos)));
		pos = i + 1;
		i = s.find_first_of(' ', pos);
	}
	v.push_back(FromString<T>(s.substr(pos)));
	return v;
}