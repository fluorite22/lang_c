//Работа с типизированным файлом
//база данных "ТОВАР"

//#include <stdio.h>
#include <conio.h>
//#include <stdlib.h>
#include <iostream>
//#include <streambuf.h>
using namespace std;
//тип данных для даты
struct TData
{
int D,M,G;
} ;
//тип данных для товара
struct TTovar
{
  char name[25];
  char madein[25];
  float cena;
  TData data;
};

//тип данных для имени файла
typedef char TName[25];
//тип данных для файловой переменной
typedef FILE TFile;
//переменная для товара
TTovar Tovar;
//переменная для имени файла
TName NameFile;
//файловая переменная
TFile *f;
//флаг открытия файла
int flag=0;

//** вывод меню ************************************************************
void menu(void)
{ system("cls");
  cout<<"******** М Е Н Ю ********\n\n"
      <<"[1]-Создание/открытие базы товаров\n"
      <<"[2]-Добавление товара в базу\n"
      <<"[3]-Удаление товара из базы\n"
      <<"[4]-Просмотр всей базы\n"
      <<"[5]-Обновление записи с заданным номером\n"
      <<"[6]-Выполнение задания. Поиск товара по названию.\n"
      <<"[ ESC ]-Выход\n";
}
//** ввод товара **************************************************
void InputTovar(TTovar &Tovar)
{
     cin.clear(); //очистить поток и затем выставить позиционирование в 0
while (!isspace(cin.get())) //Избавиться от результатов неверного ввода
      continue;
cout<<"Добавление товара:\n";
cout<<"Наименование товара ->"; //gets(Tovar.name);
cin.getline(Tovar.name,25);

cout<<"\nдата изготовления:\n";
cout<<"День->";                cin>>Tovar.data.D;
cout<<"Месяц->";               cin>>Tovar.data.M;
cout<<"Год->";                 cin>>Tovar.data.G;

cout<<"Стоимость товара ->";   cin>>Tovar.cena;
cin.clear(); //очистить поток и затем выставить позиционирование в 0
while (!isspace(cin.get()))
      continue;            //Избавиться от результатов неверного ввода

cout<<"Производитель ->";     gets(Tovar.madein);

}
//** вывод товара на экран ************************************************
void OutputTovar(TTovar Tovar)
{
cout <<"Наименование товара: "<<Tovar.name<<"\n"
     <<"Дата изготовления товара: "
     <<Tovar.data.D<<":"<<Tovar.data.M<<":"<<Tovar.data.G<<"\n"
     <<"Стоимость товара: "<<Tovar.cena<<"\n"
     <<"Производитель: "<<Tovar.madein<<"\n";
}
//** создание/открытие файла базы данных ********************************
void CreateOpenFile( TName &NameFile,int &flag )
{
 char ch;
 flag=0;
 cout<<"Введите имя файла для работы-->";
 //scanf("%s",&NameFile);
 gets(NameFile);
 f=fopen(NameFile,"r");
 if (f==NULL)
    do
     {
     system("cls");
     cout<<"ФАЙЛА с именем "
         <<NameFile
         <<" НЕТ.\n\n"
         <<"Создать файл с именем "
         <<NameFile;
     cout<<"Нажмите [ Y ] / [ N ]\n";
     ch=getch();
     if (ch=='Y'||ch=='y')
	{
	  f=fopen(NameFile,"w");
	  cout<<"Файл с именем %s создан.\n"
          <<NameFile
          <<"\n\nДля продолжения нажмите любую клавашу\n";
	  getch();
	  flag=1;
	}
     if (ch=='N'||ch=='n')
	{
	  cout<< "Файл не создан.\n"
	      <<"\n\nДля продолжения нажмите любую клавашу\n";
	  getch();
	}
     }
     while ( ! (ch =='Y' || ch=='y' || ch=='N'  || ch=='n'));
    else
	{flag=1;
	cout<<"Файл успешно открыт\n"
	    <<"\nДля продолжения нажмите любую клавашу\n";
	getch();
	}
fclose(f);
}

//** добавление записи (товара) в файл (в базу данных) **********
void RecordTovar(TName NameFile, TTovar &Tovar, int flag)
{
  if (flag)
    {
      f=fopen(NameFile,"a");
      InputTovar(Tovar);
      fwrite(&Tovar,sizeof(Tovar),1,f);
      fclose(f);
    }
    else
    {
      cout<<"\nВыберите файл для работы.\n"
          <<"Нажмите [ 1 ] в разделе М Е Н Ю.";
      getch();
    }
}
//** вывод файла (базы данных) на экран *****************
void VivodFile()
{

  int i=0;
  if (flag)
    {
  f=fopen(NameFile,"r+");

  cout<<"********  Вывод файла на экран  ********\n"
      <<"****************************************\n";
      while (fread(&Tovar,sizeof(Tovar),1,f)  )
	{
	 //printf("%d",ftell(f));
	 cout<<"Номер записи = "<<i+1<<"\n\n";
	 OutputTovar(Tovar);
	 cout<<"****************************************"<<sizeof(Tovar)<<"\n";
	 i++;
	 if (i % 3 == 0)  //вывод по несколько записей (товаров)
		{
		getch();
		system("cls");
		cout<<"********  Вывод файла на экран  ********\n"
		    <<"****************************************\n";
		}
	}
      getch();
      fclose(f);
    }
    else
    {
      cout<<"\nВыберите файл для работы.\n"
          <<"Нажмите [ 1 ] в разделе М Е Н Ю.";
      getch();
    }

}
//** размер файла *****************************
long filesize(TFile *f)
{
   long curpos, length;

   curpos = ftell(f);		//запоминаем текущее положение
   fseek(f, 0L, SEEK_END);	//перемещаем на конец файла
   length = ftell(f);		//запоминаем положение в конце файла
   fseek(f, curpos, SEEK_SET);	//перемещаем на старое положение
   return length;
}


//** обновление записи с заданным номером ******
void UpdateTovar(TName NameFile, TTovar &Tovar, int flag)
{
  long i=0;
  if (flag)
    {
	f=fopen(NameFile,"r+");

	cout<<"********  Обновление записи с заданным номером  ********\n\n"
	    <<"********************************************************\n\n"
	    <<"Введите номер записи для обновления "
	    <<"из "
	    <<(filesize(f)/sizeof(Tovar))
	    <<" --> ";
	cin>>i;
	//long q;
    fpos_t q;
	//перемещаемся на запись с номером i
	fseek(f, (i-1) * sizeof(Tovar) ,SEEK_CUR);
	//запоминаем текущее положение
	fgetpos(f,&q);

	fread(&Tovar,sizeof(Tovar),1,f);
	OutputTovar(Tovar);
	cout<<"****************************************\n";

	char ch;
	cout<<"Обновить данные?\nНажмите [ Y ] / [ N ]\n";
	do
	   {
	   //clrscr();
	   ch=getch();
	   if (ch=='Y'||ch=='y')
		{
		//вводим новые значения
		InputTovar(Tovar);
		//fseek(f, (i-1) * sizeof(Tovar) ,SEEK_CUR);
		//переходим на старое место
		fsetpos(f,&q);
		//записываем новые значения
		fwrite(&Tovar,sizeof(Tovar),1,f);
		cout<<"Данные обновлены.\n";
		}
	   if (ch=='N'||ch=='n')
		{
		cout<<"Данные не обновленны.\n";
		}
	   }
	while ( ! (ch =='Y' || ch=='y' || ch=='N'  || ch=='n'));
    cout<<"\nДля продолжения нажмите любую клавашу\n";
    getch();
    fclose(f);
    }
    else
    {
      cout<<"\nВыберите файл для работы.\n"
          <<"Нажмите [ 1 ] в разделе М Е Н Ю.";
      getch();
    }
}
//** удаление товара из базы **********************************
void DeleteTovar(TName NameFile, TTovar &Tovar, int flag)
{
  long i=0,k=0;
  TFile *g;
  if (flag)
    {
	f=fopen(NameFile,"r+");

	cout<<"********  Удаление записи с заданным номером  ********\n\n"
	    <<"********************************************************\n\n"
	    <<"Введите номер записи для удаления "
	    <<"из "
	    <<(filesize(f)/sizeof(Tovar))
	    <<" --> ";
	cin>>i;

	//перемещаемся на запись с номером i
	fseek(f, (i-1) * sizeof(Tovar) ,SEEK_CUR);
	fread(&Tovar,sizeof(Tovar),1,f);
	OutputTovar(Tovar);
	cout<<"****************************************\n";

	char ch;
	cout<<"Удалить данные?\nНажмите [ Y ] / [ N ]\n";
	do
	   {
	   //clrscr();
	   ch=getch();
	   if (ch=='Y'||ch=='y')
		{
		fseek(f,0L,SEEK_SET);
		cout<<"****"<<ftell(f);
		g=fopen("Temp","w");
		while (fread(&Tovar,sizeof(Tovar),1,f)  )
		  {
		  if (k != (i-1) ) fwrite(&Tovar,sizeof(Tovar),1,g);
		  k++;
		  }
		cout<<"Данные обновлены.\n";
		fclose(g);
		fclose(f);
		remove(NameFile); 	//удаляем старый файл
		rename("Temp",NameFile);//переименовываем временный файл
		}
	   if (ch=='N'||ch=='n')
		{
		cout<<"Данные не обновленны.\n";
		}
	   }
	while ( ! (ch =='Y' || ch=='y' || ch=='N'  || ch=='n'));
    cout<<"\nДля продолжения нажмите любую клавашу\n";
    getch();
    //fclose(f);
    }
    else
    {
      cout<<"\nВыберите файл для работы.\n"
          <<"Нажмите [ 1 ] в разделе М Е Н Ю.";
      getch();
    }
}

//Начало программы

int main()
{
char ch;
  system("cls");
  do
  {
  menu();
  ch=getch();
  switch (ch)
   {
    case '1':   system("cls");
		CreateOpenFile(NameFile,flag);
		break;
    case '2':   system("cls");
		RecordTovar(NameFile,Tovar,flag);
		//getch();
		break;
    case '3':   system("cls");
		cout<<"Удаление товара из базы данных\n";
		DeleteTovar(NameFile,Tovar,flag);
		getch();
		break;
    case '4':   system("cls");
		VivodFile();
		break;
    case '5':   system("cls");
		//printf("Обновление записи с заданным номером\n");
		UpdateTovar(NameFile,Tovar,flag);
		//getch();
		break;
    case '6':	cout<<"Выполнение задания в соответствии с вариантом\n";
		getch();
		break;
//    case '8':	exit(1);
   }
  }
  while	( ch!=27 ) ;
  return 0;
}
