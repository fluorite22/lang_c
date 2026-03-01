#include <iostream>
#include <math.h>
using namespace std;
int main()
{
    float x,y,t;
    cout << "Вычислить функцию \n";
    cout << "Введите x=";
    cin >> x;
    t=x*x+4*x+3;
    if (x<-2)
       if (t!=0) { y=1/t; cout << "x=" << x << "y=" << y << "\n"; }
       else cout << "Нет решений";
    else if (x<0)
         if (t>0) { y=log(t);
                    cout << "x=" << x << "y=" << y << "\n";
                    }
         else cout << "Нет решений";
         else if (cos(t)!=0) { y=tan(t);
                               cout << "x=" << x << "y=" << y << "\n";
                               }
                               else cout << "Нет решений";
                               
         system("pause");
         return 0;
         }
