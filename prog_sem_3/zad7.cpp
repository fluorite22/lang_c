#include <iostream>
using namespace std;
int main()
{
    cout << "Сумма ряда\n";
    int n;
    cout << "Введите n";
    cin >> n;
    int S=0;
    for (int i=1; i<=n; i++)
        S=S+i;
    cout << "Сумма =" << S << endl;
    system("pause");
    return 0;
}
    
