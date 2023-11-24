#include"pch.h"
#include "Cardiology.h"
#include<sstream>
#include<numeric>
//Предикат для сортировки номеров
struct PredCardNumber1
{
	bool operator()(const Patient *left, const Patient *right) const
	{
		return left->getCardNumber() < right->getCardNumber();
	}
} predCardNumber;

//Предикат для сортировки имен
struct PredName1
{
	bool operator()(const Patient *left, const Patient *right) const
	{
		return left->getName() < right->getName();
	}
} predName;

//Открытие файла и запись
Cardiology::Cardiology(string path)
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
			cardioPatients.emplace(obj.cardNumber, obj);
			cardioCardNumbers.push_back(obj.cardNumber);
			fullCardioList.push_back(new Patient(s));
		}
	}

	ifs.close();
}

//Сортировка по номеру карт
string Cardiology::sortByCardNumber()
{
	sort(fullCardioList.begin(), fullCardioList.end(), predCardNumber);
	return print();
}

//Сортировка по имени
string Cardiology::sortByName()
{
	sort(fullCardioList.begin(), fullCardioList.end(), predName);
	return print();
}

//Печать ВСЕХ пациентов
string Cardiology::print()
{
	string print;
	int counter = 1;
	for (vector<Patient*>::iterator i = fullCardioList.begin(); i != fullCardioList.end(); i++)
	{
		print += "[" + to_string(counter) + "]\t"s + to_string((*i)->getCardNumber()) + "\t" + (*i)->getName() + "\t\t" + (*i)->getGender() + "\t" + (*i)->getDiagnosis() + "\n";
		counter++;
	}
	return print;
}

//Фильтр по полу
string Cardiology::filterByGender(string gender)
{
	buffer.clear();
	//FOR_EACH
	//Вставляем пол и номер пациента
	for_each(cardioPatients.begin(), cardioPatients.end(), [&](pair<int, Patient> obj)
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
string Cardiology::printFilterByGender(pair<iter, iter> &filter)
{
	int counter = 1;
	string print;
	for (iter i = filter.first; i != filter.second; ++i)
	{
		Patient obj = cardioPatients[i->second];
		print += "[" + to_string(counter) + "]\t"s + to_string(obj.getCardNumber()) + "\t" + obj.getName() + "\t\t" + obj.getGender() + "\t" + obj.getDiagnosis() + "\n";
		counter++;
	}
	return print;
}

//Поиск и печать пациентов из обоих отделений
string Cardiology::setUnion(HospitalDepartment *object)
{
	vector<int> cardCardiology = this->getCards();
	vector<int> cardSurgical = object->getCards();
	vector<int> unionPatients;

	sort(cardSurgical.begin(), cardSurgical.end());
	sort(cardCardiology.begin(), cardCardiology.end());

	set_union(cardCardiology.begin(), cardCardiology.end(), cardSurgical.begin(), cardSurgical.end(), back_inserter(unionPatients));

	stringstream ss;
	int counter = 1;

	for_each(unionPatients.begin(), unionPatients.end(), [&](int card)
		{
			string result = returnByCardNumber(card);
			
			if (result[0] != '0')
			{
				ss << "[" << to_string(counter) << "]\t"s << result << '\n';
			}
			else //В противном случае печатаем результат из хирургического отделения
			{
				ss << "[" << to_string(counter) << "]\t"s << object->returnByCardNumber(card) << '\n';
			}
			counter++;
		});

	return ss.str();
}

//Поиск и печать пациентов, которые лежали в обоих отделениях
string Cardiology::setIntersection(HospitalDepartment *object)
{
	vector<int> cardCardiology = this->getCards();
	vector<int> cardSurgical = object->getCards();
	vector<int> intersectionPatients;

	sort(cardSurgical.begin(), cardSurgical.end());
	sort(cardCardiology.begin(), cardCardiology.end());

	set_intersection(cardCardiology.begin(), cardCardiology.end(), cardSurgical.begin(), cardSurgical.end(), back_inserter(intersectionPatients));

	stringstream ss;
	int counter = 1;

	for_each(intersectionPatients.begin(), intersectionPatients.end(), [&](int card)
		{
			ss << "[" << to_string(counter) << "]\t"s << returnByCardNumber(card) << '\n';
			counter++;
		});

	return ss.str();
}

//Возврат информации о пациенте по его номеру карты
string Cardiology::returnByCardNumber(int cardNumber)
{
	string print;

	print += to_string(cardioPatients[cardNumber].getCardNumber()) + "\t" + cardioPatients[cardNumber].getName() + "\t\t" + cardioPatients[cardNumber].getGender() + "\t";

	return print;
}

vector<int> Cardiology::getCards()
{
	return cardioCardNumbers;
}

//Добавление нового пациента в список
void Cardiology::addPatient(string path, string info)
{
	string s;
	ofstream ofs;

	ofs.open(path, std::ios_base::app);

	ofs << "\n" << info << "\n";

	ofs.close();

	fullCardioList.push_back(new Patient(info));
}

Cardiology::~Cardiology()
{
	for (vector<Patient*>::iterator i = fullCardioList.begin(); i != fullCardioList.end(); i++)
	{
		delete* i;
	}
}