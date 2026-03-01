            
            #include <iostream>
            using namespace std;
            int main()
            {
                
                //printf("Наибольшее из трёх\n");
                cout << "Наибольшее из трёх\n" << endl;
                cout << "Введите три целых числа" << endl;
                int a, b, c;
                cin >> a >> b >> c;
                if (a>b)
                   if (a>c) cout << "max=" << a << endl;
                   else cout << "max=" << c << endl;
                else if (b>c) cout << "max=" << b << endl;
                     else cout << "max=" << c << endl;
                system("pause");
                return 0;
            }
            
