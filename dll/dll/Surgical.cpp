#include"pch.h"
#include "Surgical.h"
//Предикат для сортировки номеров
struct PredCardNumber2
{
	bool operator()(const Patient *left, const Patient *right) const
	{
		return left->getCardNumber() < right->getCardNumber();
	}
} predCardNumber;

//Предикат для сортировки имен
struct PredName2
{
	bool operator()(const Patient *left, const Patient *right) const
	{
		return left->getName() < right->getName();
	}
} predName;

//Открытие файла и запись
Surgical::Surgical(string path)
{
	string s;
	ifstream ifs;

	ifs.open(path);
	if (!ifs)
	{
		cout << "error";
		return;
	}

	while (!ifs.eof())
	{
		getline(ifs, s);
		if (!s.empty())
		{
			Patient obj(s);
			surgicPatients.emplace(obj.cardNumber, obj);
			surgicCardNumbers.push_back(obj.cardNumber);
			fullSurgicList.push_back(new Patient(s));
		}
	}

	ifs.close();
}

//Сортировка по номеру карт
string Surgical::sortByCardNumber()
{
	sort(fullSurgicList.begin(), fullSurgicList.end(), predCardNumber);
	return print();
}

//Сортировка по имени
string Surgical::sortByName()
{
	sort(fullSurgicList.begin(), fullSurgicList.end(), predName);
	return print();
}

//Печать ВСЕХ пациентов
string Surgical::print()
{
	string print;
	int counter = 1;
	for (vector<Patient*>::iterator i = fullSurgicList.begin(); i != fullSurgicList.end(); i++)
	{
		print += "[" + to_string(counter) + "]\t"s + to_string((*i)->getCardNumber()) + "\t" + (*i)->getName() + "\t\t" + (*i)->getGender() + "\t" + (*i)->getDiagnosis() + "\n";
		counter++;
	}
	return print;
}

//Фильтр по полу
string Surgical::filterByGender(string gender)
{
	buffer.clear();
	//FOR_EACH
	//Вставляем пол и номер пациента
	for_each(surgicPatients.begin(), surgicPatients.end(), [&](pair<int, Patient> obj)
	{
		buffer.emplace(obj.second.gender, obj.first);
	});

	//EQUAL_RANGE
	//Фильтр пациентов по полу
	if (gender == "м")
	{
		pair<iter, iter> filterByMale = buffer.equal_range(gender);
		return printFilterByGender(filterByMale);
	}
	else
	{
		pair<iter, iter> filterByFemale = buffer.equal_range(gender);
		return printFilterByGender(filterByFemale);
	}
}

//Печать результата фильтра по полу
string Surgical::printFilterByGender(pair<iter, iter> &filter)
{
	int counter = 1;
	string print;
	for (iter i = filter.first; i != filter.second; ++i)
	{
		Patient obj = surgicPatients[i->second];
		print += "[" + to_string(counter) + "]\t"s + to_string(obj.getCardNumber()) + "\t" + obj.getName() + "\t\t" + obj.getGender() + "\t" + obj.getDiagnosis() + "\n";
		counter++;
	}
	return print;
}

string Surgical::setUnion(HospitalDepartment *object)
{
	return string();
}

string Surgical::setIntersection(HospitalDepartment *object)
{
	return string();
}

//Возврат информации о пациенте по его номеру карты
string Surgical::returnByCardNumber(int cardNumber)
{
	string print;

	print += to_string(surgicPatients[cardNumber].getCardNumber()) + "\t" + surgicPatients[cardNumber].getName() + "\t\t" + surgicPatients[cardNumber].getGender() + "\t";

	return print;
}

vector<int> Surgical::getCards()
{
	return surgicCardNumbers;
}

//Добавление нового пациента в список
void Surgical::addPatient(string path, string info)
{
	string s;
	ofstream ofs;

	ofs.open(path, std::ios_base::app);

	ofs << "\n" << info << "\n";

	ofs.close();

	fullSurgicList.push_back(new Patient(info));
}

Surgical::~Surgical()
{
	for (vector<Patient*>::iterator i = fullSurgicList.begin(); i != fullSurgicList.end(); i++)
	{
		delete* i;
	}
}