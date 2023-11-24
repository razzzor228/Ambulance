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

    //Все записи
    cout << "Все пациенты кардиологического отделения\n";
    c.print();
    cout << "Все пациенты хирургического отделения\n";
    s.print();

    //Сортировка по номеру карты
    c.sortByCardNumber();
    s.sortByCardNumber();
    cout << "Отсортированный по номеру карт список пациентов кардиологического отделения\n";
    c.print();
    cout << "Отсортированный по номеру карт список пациентов хирургического отделения\n";
    s.print();

    //Сортировка по имени
    c.sortByName();
    s.sortByName();
    cout << "Отсортированный по имени список пациентов кардиологического отделения\n";
    c.print();
    cout << "Отсортированный по имени список пациентов хирургического отделения\n";
    s.print();

    //Фильтры по полу
    c.filterByGender();
    s.filterByGender();

    vector<int> intersectPatients, unionPatients; //intersectPatients - пациенты, которые были в обоих отделениях, unionPatients - общий список пациентов обоих отделений без повторений

    //SET_INTERSECTION
    sort(c.cardioCardNumbers.begin(), c.cardioCardNumbers.end());
    sort(s.surgicCardNumbers.begin(), s.surgicCardNumbers.end());

    set_intersection(c.cardioCardNumbers.begin(), c.cardioCardNumbers.end(), s.surgicCardNumbers.begin(), s.surgicCardNumbers.end(), back_inserter(intersectPatients));

    sort(intersectPatients.begin(), intersectPatients.end());

    cout << endl << "Совпадающие пациенты:" << endl;
    cout << " №\tНомер карты\t\t\t    ФИО\t\t\t\tПол\t\t  Диагноз\n";
    for (int i = 0; i < intersectPatients.size(); i++)
    {
        cout << "[" << i + 1 << "] \t    " << intersectPatients[i] << " " << c.returnByCardNumber(intersectPatients[i]) << endl;
    }

    //SET_UNION
    set_union(c.cardioCardNumbers.begin(), c.cardioCardNumbers.end(), s.surgicCardNumbers.begin(), s.surgicCardNumbers.end(), back_inserter(unionPatients));

    sort(unionPatients.begin(), unionPatients.end());

    cout << endl << "Все пациенты:" << endl;
    cout << " №\tНомер карты\t\t\t    ФИО\t\t\t\tПол\t\t  Диагноз\n";
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