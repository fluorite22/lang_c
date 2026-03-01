#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

struct pointer
{ int d;
  pointer *p;
};

//=====================
void FormOch(pointer **ph, int data)
{
 *ph = new pointer;
 (*ph) -> d = data;
 (*ph)->p = NULL;
}

//======================
void DobOch (pointer **pk, int data)
      {   pointer *px=new pointer;
	  px->d=data;
	  (*pk)->p=px;
	  *pk=px;
	  (*pk)->p=NULL;
       }


//======================
void IskOch (pointer **ph, int &data)
{ data = (*ph)->d;
  *ph = (*ph)->p;
}


//======================
int main()
{
system("cls");
// ======= ”®а¬Ёа®ў ­ЁҐ бвҐЄ  ======
 pointer *ph=NULL;
 cout<<"Введите элемент списка -->" ;
 int data;
 cin >> data ;

 FormOch(&ph,data);

 pointer *pk = ph;
 int i=1;
//cout<<"====="<<ph->d<<pk->d;

while (data!=0)
 {
	cout<<"Введите "<<i+1<<"элемент списка -->" ;
	cin >> data;
	DobOch(&pk,data);
	i++;
 }
 
 
 i=0;
 pointer *pc=ph;
 while (pc!=NULL)
  {
      IskOch(&pc,data);
      cout<<(i+1)<<" элемент  = "<<data<<"\n";
      i++;
   }
   
   
cout <<"Введите данные для поиска ";
int key;
cin >>key;
pc=ph;
while ((pc!=NULL) && (key!=pc->d)) pc=pc->p;
//cout<<"***"<<pc->d;

cout<< "Введите данные для добавления в список ->";
int insert;
cin>>insert;
pointer *px=new pointer;
px->d=insert;
px->p=pc->p;
pc->p=px;
pc=ph;
i=0;
 while (pc!=NULL)
  {
      IskOch(&pc,data);
      cout<<(i+1)<<" элемент  = "<<data<<"\n";
      i++;
   }

cout<<"Введите данные для удаления -> ";
cin>>key;
pc=ph;
while ((pc!=NULL) && (key!=pc->d))
	{
	px=pc;
	pc=pc->p;
	}
px->p=pc->p;
i=0;
pc=ph;
 while (pc!=NULL)
  {
      IskOch(&pc,data);
      cout<<(i+1)<<" элемент  = "<<data<<"\n";
      i++;
   }

getch();
}
