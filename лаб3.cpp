#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <locale.h>

using namespace std;
struct pointer
{ 
	int d;
	pointer *p;
};

//===================== 
void FormSt(pointer **ph, int data)
{
	*ph = new pointer;
	(*ph) -> d = data;
	(*ph)->p = NULL;
}
//====================== 
void DobSt (pointer **ph, int data)
{ 
	pointer *px=new pointer;
	px->d=data;
	px->p=*ph;
	*ph=px;
}
//====================== 
void IskSt (pointer **ph, int &data)
{ 
	data = (*ph)->d;
	*ph = (*ph)->p;
}

//======================
int main()
{
	system("cls");
	setlocale(LC_ALL, "rus");
	int i;

 	pointer *ph=NULL;

 	cout<<"Введите первый элемент -->" ;
	int data;
	cin >> data ;

	FormSt(&ph,data);
	i=1;
	while (data!=0)
	{
		cout<<"Введите следующий элемент -->" ;
		cin >> data;
		DobSt(&ph,data);
		i++;
	}
 
	if (i >= 3 )
	{
		cout << "Удаление среднего(-их) элементов стека\n";
		pointer *pc = ph;
		int n = 0;
		
		if (i % 2 == 1)
			n = i / 2 - 1;
		else 
			n = i / 2 - 2;
	
		for (int j = 0; j < n; j++)
			pc = pc->p;
	
		cout << "Количество элементов = " << i << endl;


		if (i % 2 == 1)
			pc->p = pc->p->p;
		
		else
			pc->p = pc->p->p->p;
	}
	else
		cout << "Для удаления не хватает элементов!!!!\n";
		
	
 	cout<<"\nВывод полученного стека: \n\n";
	i = 0;
	while (ph!=NULL)    
	{
    	IskSt(&ph,data);
    
    	cout<<(i+1)<<" element  = "<<data<<"\n";
    	i++;
	}
   
getch();
}
