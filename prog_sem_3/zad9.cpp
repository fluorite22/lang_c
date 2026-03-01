/* Написать программу для вычисления факториала
числа n */
#include <iostream>
using namespace std;
int main()
{
    cout << "Факториал числа"<<endl;
    int n, P=1;
    cout << "Введите n=";
    cin >> n;
    for (int i=1; i<=n; i++)
        P=P*i;
    cout<<"Факториал !"<<n<<"="<<P<<endl;
    system("pause");
    return 0;
}
