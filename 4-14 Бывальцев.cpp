#include <iostream>
#include <map>
#include <list>

using namespace std;

struct student
{
	string name;
	map<string, list<int>> marks; //имя предмета:список оценок
	map<string, int> getPerf() //высчитываем для каждого предмета среднюю оценку
	{
		map<string, int> result;
		for (auto itr = marks.begin(); itr != marks.end(); itr++)
		{
			double count = 0;
			for (auto markItr = itr->second.begin(); markItr != itr->second.end(); markItr++)
			{
				count += *markItr;
				result[itr->first] = round(count);
			}
			result[itr->first] /= itr->second.size();
		}
		return result;
	}
};

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");

	student st1;
	st1.name = "Иванов Иван";
	st1.marks["Математика"].push_back(5);
	st1.marks["Математика"].push_back(5);
	st1.marks["Физика"].push_back(5);
	st1.marks["Физика"].push_back(5);
	st1.marks["Информатика"].push_back(5);
	st1.marks["Информатика"].push_back(5);

	student st2;
	st2.name = "Петров Петр";
	st2.marks["Математика"].push_back(2);
	st2.marks["Математика"].push_back(2);
	st2.marks["Физика"].push_back(5);
	st2.marks["Физика"].push_back(3);
	st2.marks["Информатика"].push_back(4);
	st2.marks["Информатика"].push_back(4);


	student st3;
	st3.name = "Васильев Василий";
	st3.marks["Математика"].push_back(3);
	st3.marks["Математика"].push_back(4);
	st3.marks["Физика"].push_back(5);
	st3.marks["Физика"].push_back(3);
	st3.marks["Информатика"].push_back(4);
	st3.marks["Информатика"].push_back(4);

	list<student*> _class, perfect, bad;
	_class.push_back(&st1);
	_class.push_back(&st2);
	_class.push_back(&st3);

	for (auto itr = _class.begin(); itr != _class.end(); itr++)
	{
		auto perf = (*itr)->getPerf();
		bool isBad = false;
		bool isPerfect = true;
		for (auto perfItr = perf.begin(); perfItr != perf.end(); perfItr++)
		{
			if (perfItr->second == 2)
			{
				isBad = true;
				break;
			}
			if (perfItr->second != 5)
			{
				isPerfect = false;
			}
		}

		if (isBad)
			bad.push_back(*itr);
		if (isPerfect)
			perfect.push_back(*itr);
	}

	cout << "Отличники:" << endl;
	for (auto itr = perfect.begin(); itr != perfect.end(); itr++)
		cout << (*itr)->name << endl;

	cout << endl << "Неуспевающие:" << endl;
	for (auto itr = bad.begin(); itr != bad.end(); itr++)
		cout << (*itr)->name << endl;

	cout << endl << "Процент успеваемости: " << (1 - (double)bad.size() / _class.size()) * 100 << "%";

	return 0;
}