#include "Cardiology.h"
#include "Surgical.h"

struct leaks
{
    ~leaks()
    {
        _CrtDumpMemoryLeaks();
    }
} leaks;

int main()
{
    setlocale(LC_ALL, "Russian");

    Cardiology c;
    Surgical s;

    //��� ������
    cout << "��� �������� ����������������� ���������\n";
    c.print();
    cout << "��� �������� �������������� ���������\n";
    s.print();

    //���������� �� ������ �����
    c.sortByCardNumber();
    s.sortByCardNumber();
    cout << "��������������� �� ������ ���� ������ ��������� ����������������� ���������\n";
    c.print();
    cout << "��������������� �� ������ ���� ������ ��������� �������������� ���������\n";
    s.print();

    //���������� �� �����
    c.sortByName();
    s.sortByName();
    cout << "��������������� �� ����� ������ ��������� ����������������� ���������\n";
    c.print();
    cout << "��������������� �� ����� ������ ��������� �������������� ���������\n";
    s.print();

    //������� �� ����
    c.filterByGender();
    s.filterByGender();

    vector<int> intersectPatients, unionPatients; //intersectPatients - ��������, ������� ���� � ����� ����������, unionPatients - ����� ������ ��������� ����� ��������� ��� ����������

    //SET_INTERSECTION
    sort(c.cardioCardNumbers.begin(), c.cardioCardNumbers.end());
    sort(s.surgicCardNumbers.begin(), s.surgicCardNumbers.end());

    set_intersection(c.cardioCardNumbers.begin(), c.cardioCardNumbers.end(), s.surgicCardNumbers.begin(), s.surgicCardNumbers.end(), back_inserter(intersectPatients));

    sort(intersectPatients.begin(), intersectPatients.end());

    cout << endl << "����������� ��������:" << endl;
    cout << " �\t����� �����\t\t\t    ���\t\t\t\t���\t\t  �������\n";
    for (int i = 0; i < intersectPatients.size(); i++)
    {
        cout << "[" << i + 1 << "] \t    " << intersectPatients[i] << " " << c.returnByCardNumber(intersectPatients[i]) << endl;
    }

    //SET_UNION
    set_union(c.cardioCardNumbers.begin(), c.cardioCardNumbers.end(), s.surgicCardNumbers.begin(), s.surgicCardNumbers.end(), back_inserter(unionPatients));

    sort(unionPatients.begin(), unionPatients.end());

    cout << endl << "��� ��������:" << endl;
    cout << " �\t����� �����\t\t\t    ���\t\t\t\t���\t\t  �������\n";
    for (int i = 0; i < unionPatients.size(); i++)
    {
        if (c.returnByCardNumber(unionPatients[i]).size() > 20)
        {
            cout << "[" << i + 1 << "] \t    " << unionPatients[i] << " " << c.returnByCardNumber(unionPatients[i]) << endl;
        }
        else
        {
            cout << "[" << i + 1 << "] \t    " << unionPatients[i] << " " << s.returnByCardNumber(unionPatients[i]) << endl;
        }

    }
    return 0;
}