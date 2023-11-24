#include"pch.h"
#include "Patient.h"
#include <iostream>

Patient::Patient(string s)
{
	//Парсим текст
	int endOfCardNumber = s.find_first_of(',');
	cardNumber = (std::stoi(s.substr(0, endOfCardNumber)));
	s.erase(0, endOfCardNumber + 2);

	int endOfName = s.find_first_of(',');
	name = (s.substr(0, endOfName));
	s.erase(0, endOfName + 2);

	int endOfGender = s.find_first_of(',');
	gender = (s.substr(0, endOfGender));
	s.erase(0, endOfGender + 2);

	int endOfDiagnosis = s.find_first_of('.');
	diagnosis = (s.substr(0, endOfDiagnosis));
}

int Patient::getCardNumber() const
{
	return cardNumber;
}

string Patient::getName() const
{
	return name;
}

string Patient::getGender() const
{
	return gender;
}

string Patient::getDiagnosis() const
{
	return diagnosis;
}