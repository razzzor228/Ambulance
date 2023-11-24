#pragma once
#include"pch.h"
#include <string>
using namespace std;

struct HOSPITAL_API Patient
{
	string name, gender, diagnosis;
	int cardNumber;

	Patient() = default;
	Patient(string s);

	int getCardNumber() const;
	string getName() const;
	string getGender() const;
	string getDiagnosis() const;
};
