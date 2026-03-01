//#include <iostream>
#include "myzad.h"
//using namespace std;



//****************************
int main()
{
     cout<<"работа с массивом\n";
     srand( time(0) );
     int n;
     cout << "Введите размер массива = ";
     cin >> n;
    //*********************************************
    InputRndMas(a,n);
    OutputMas(a,n);
    //********сдвинуть элементы массива на один влево ******************************
    cout<<endl<<"Сдвиг влево"<<endl;
    SdvigMas1Left(a,n);
    //*********************************
    OutputMas(a,n);    

    //***********************************
    //cout << "Среднее арифм. = " << SrArElMas(a,n);
    float Sr = SrArElMas(a,n);
    
    cout << "Среднее арифм. = " << Sr<<endl;
    
    
    
//********************************
cout<<endl<<endl;
system("pause");
return 0;
}
