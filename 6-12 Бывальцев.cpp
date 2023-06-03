#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int main() {
    int a;
    set<int> numbers, repeat_numbers;   //создание множества
    setlocale(LC_ALL, "Russian");
    
    ifstream in("f.txt");
    fstream F;                              //открываем файл в режиме чтения
    F.open("f.txt");

    
    if (F) {         //если открытие файла прошло корректно, то цикл для чтения значений из файла;
        // выполнение цикла прервется, когда достигнем конца файла, в этом случае F.eof() вернет истину.
        while (!F.eof()) {
            F >> a;         //чтение очередного значения из потока F в переменную a
            
            if (numbers.count(a) > 0) repeat_numbers.insert(a);     //заполняем множество повторящихся чисел
            numbers.insert(a);  //заполняем множество чисел
            
        }
        F.close();       //закрытие потока
    }
    else cout << "Файл не существует" << endl; //если открытие файла прошло некорректно, то вывод ошибки


    ofstream G;     //открываем файл для записи
    G.open("g.txt", ios::out);
    set<int>::iterator it; //создание итератора
    for (it = numbers.begin(); it != numbers.end(); it++) { // перебор всех элементов множества
        if (repeat_numbers.count(*it) == 0) G << (*it);     //если число встречается 1 раз (перебираем все числа, оно не должно лежать в повторяющихся), то записываем его в файл
    }
    G.close();  //закрытие потока
    system("pause");
}

