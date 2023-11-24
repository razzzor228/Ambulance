#pragma once
#include"pch.h"
#include"HospitalDepartment.h"

class HOSPITAL_API Surgical: public HospitalDepartment
{
public:
	unordered_map<int, Patient> surgicPatients;
	vector<int> surgicCardNumbers;
	vector<Patient*> fullSurgicList;

	//Surgical();
	Surgical(string path);
	
	string sortByCardNumber();
	string sortByName();
	string print();

	string filterByGender(string gender);
	string printFilterByGender(pair<iter, iter> &filter);
	
	string setUnion(HospitalDepartment *object);
	string setIntersection(HospitalDepartment *object);
	string returnByCardNumber(int cardNumber);
	vector<int> getCards();

	void addPatient(string path, string info);

	~Surgical();
};
