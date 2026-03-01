/*Написать программу для возведения числа x в степень n */
#include <iostream>
using namespace std;
int main()
{
    cout<<"Возвести x в степень n"<<endl;
    int n, P=1, x;
    cout<<"Введите x=";
    cin>>x;
    cout<<"Введите n=";
    cin>>n;
    for (int i=1; i<=n; i++)
        P=P*x;
    cout<<x<<" в степени"<<n<<"="<<P<<endl;
    system("pause");
    return 0;
}
    
