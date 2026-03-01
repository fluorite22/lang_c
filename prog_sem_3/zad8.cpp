/* Пусть дано k и ряд целых чисел , концом ряда
является число ноль. Найти номер первого числа
большего k */
#include <iostream>
using namespace std;
int main()
{
    cout << "Поиск 2" << endl;
    int k, x, i, m=0;
    cout << "Введите k=";
    cin >> k;
    i=1;
    cout << "Введите x"<<i<<" = ";
    cin >> x;
    while (x!=0)
    {
          if (x>k && m==0) m=i;
          i++;
          cout << "Введите x"<<i<<" = ";
          cin>>x;
    }
    cout << "Номер первого числа в наборе большего k равен " << m << endl;
    system("pause");
    return 0;
}
