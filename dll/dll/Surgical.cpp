#include"pch.h"
#include "Surgical.h"
//�������� ��� ���������� �������
struct PredCardNumber2
{
	bool operator()(const Patient *left, const Patient *right) const
	{
		return left->getCardNumber() < right->getCardNumber();
	}
} predCardNumber;

//�������� ��� ���������� ����
struct PredName2
{
	bool operator()(const Patient *left, const Patient *right) const
	{
		return left->getName() < right->getName();
	}
} predName;

//�������� ����� � ������
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

//���������� �� ������ ����
string Surgical::sortByCardNumber()
{
	sort(fullSurgicList.begin(), fullSurgicList.end(), predCardNumber);
	return print();
}

//���������� �� �����
string Surgical::sortByName()
{
	sort(fullSurgicList.begin(), fullSurgicList.end(), predName);
	return print();
}

//������ ���� ���������
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

//������ �� ����
string Surgical::filterByGender(string gender)
{
	buffer.clear();
	//FOR_EACH
	//��������� ��� � ����� ��������
	for_each(surgicPatients.begin(), surgicPatients.end(), [&](pair<int, Patient> obj)
	{
		buffer.emplace(obj.second.gender, obj.first);
	});

	//EQUAL_RANGE
	//������ ��������� �� ����
	if (gender == "�")
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

//������ ���������� ������� �� ����
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

//������� ���������� � �������� �� ��� ������ �����
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

//���������� ������ �������� � ������
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