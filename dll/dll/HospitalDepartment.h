#pragma once
#include"pch.h"
#include"Patient.h"
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<unordered_map>

using iter = unordered_multimap<std::string, int>::iterator;

class HOSPITAL_API HospitalDepartment
{
protected:
	unordered_multimap<std::string, int> buffer;
public:
	HospitalDepartment() = default;

	virtual string sortByCardNumber() = 0;
	virtual string sortByName() = 0;
	virtual string print() = 0;

	virtual string filterByGender(string gender) = 0;
	virtual string printFilterByGender(std::pair<iter, iter> &filter) = 0;
	
	virtual string setUnion(HospitalDepartment *object) = 0;
	virtual string setIntersection(HospitalDepartment *object) = 0;
	virtual string returnByCardNumber(int cardNumber) = 0;
	virtual vector<int> getCards() = 0;

	virtual void addPatient(string path, string info) = 0;
};