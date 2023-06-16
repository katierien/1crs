#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//тип данных для даты
struct TData
{
int D,M,G;
} ;
//тип данных для лидара
struct Lidar
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
//переменная для лидара
Lidar Lidd;
//переменная для имени файла
TName NameFile;
//файловая переменная
TFile *f;
//флаг выбора файла для работы
int flag=0;

//** вывод меню ************************************************************
void menu(void)
{ system("cls");
  cout<<"******** М Е Н Ю ********\n\n"
      <<"[1]-Создание/открытие базы лидаров\n"
      <<"[2]-Добавление лидара в базу\n"
      <<"[3]-Удаление лидара из базы\n"
      <<"[4]-Просмотр всей базы\n"
      <<"[5]-Обновление записи с заданным номером\n"
      <<"[6]-Выполнение задания. Поиск лидара по названию.\n"
      <<"[ ESC ]-Выход\n";
}
//** ввод лидара **************************************************
void InpuLidar(Lidar &Lidd)
{
cin.clear(); //очистить поток и затем выставить позиционирование в 0
cin.sync();

cout<<"Добавление лидара:\n";
cout<<"Наименование лидара ->"; //gets(Lidd.name);
cin.getline(Lidd.name,25);

cout<<"\nДата изготовления:\n";
cout<<"День->";                cin>>Lidd.data.D;
cout<<"Месяц->";               cin>>Lidd.data.M;
cout<<"Год->";                 cin>>Lidd.data.G;

cout<<"Стоимость лидара ->";   cin>>Lidd.cena;
cin.clear(); //очистить поток и затем выставить позиционирование в 0
cin.sync();

cout<<"Производитель ->";     gets(Lidd.madein);

}
//** вывод лидара на экран ************************************************
void OutpuLidar(Lidar Lidd)
{
cout <<"Наименование лидара: "<<Lidd.name<<"\n"
     <<"Дата изготовления лидара: "
     <<Lidd.data.D<<":"<<Lidd.data.M<<":"<<Lidd.data.G<<"\n"
     <<"Стоимость лидара: "<<Lidd.cena<<"\n"
     <<"Производитель: "<<Lidd.madein<<"\n";
}
//** создание/открытие файла базы данных ********************************
void CreateOpenFile( TName &NameFile,int &flag )
{
 char ch;
 flag=0;
 cout<<"Введите имя файла для работы-->";
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
	  cout<<"Файл с именем " <<NameFile<<" создан.\n"
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

//** добавление записи о лидаре в файл (в базу данных) **********
void RecordLidd(TName NameFile, Lidar &Lidd, int flag)
{
  if (flag)
    {
      f=fopen(NameFile,"a");
      InpuLidar(Lidd);
      fwrite(&Lidd,sizeof(Lidd),1,f);
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
      while (fread(&Lidd,sizeof(Lidd),1,f)  )
	{
	 cout<<"Номер записи = "<<i+1<<"\n\n";
	 OutpuLidar(Lidd);
	 cout<<"****************************************"<<sizeof(Lidd)<<"\n";
	 i++;
	 if (i % 3 == 0)  //вывод нескольких лидаров
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
void UpdateLidd(TName NameFile, Lidar &Lidd, int flag)
{
  long i=0;
  if (flag)
    {
	f=fopen(NameFile,"r+");

	cout<<"********  Обновление записи с заданным номером  ********\n\n"
	    <<"********************************************************\n\n"
	    <<"Введите номер записи для обновления "
	    <<"из "
	    <<(filesize(f)/sizeof(Lidd))
	    <<" --> ";
	cin>>i;
	//long q;
    fpos_t q;
	//перемещаемся на запись с номером i
	fseek(f, (i-1) * sizeof(Lidd) ,SEEK_CUR);
	//запоминаем текущее положение
	fgetpos(f,&q);

	fread(&Lidd,sizeof(Lidd),1,f);
	OutpuLidar(Lidd);
	cout<<"****************************************\n";

	char ch;
	cout<<"Обновить данные?\nНажмите [ Y ] / [ N ]\n";
	do
	   {
	   ch=getch();
	   if (ch=='Y'||ch=='y')
		{
		//вводим новые значения
		InpuLidar(Lidd);
		//переходим на старое место
		fsetpos(f,&q);
		//записываем новые значения
		fwrite(&Lidd,sizeof(Lidd),1,f);
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
//** удаление лидара из базы **********************************
void DeleteLidd(TName NameFile, Lidar &Lidd, int flag)
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
	    <<(filesize(f)/sizeof(Lidd))
	    <<" --> ";
	cin>>i;

	//перемещаемся на запись с номером i
	fseek(f, (i-1) * sizeof(Lidd) ,SEEK_CUR);
	fread(&Lidd,sizeof(Lidd),1,f);
	OutpuLidar(Lidd);
	cout<<"****************************************\n";

	char ch;
	cout<<"Удалить данные?\nНажмите [ Y ] / [ N ]\n";
	do
	   {
	   ch=getch();
	   if (ch=='Y'||ch=='y')
		{
		fseek(f,0L,SEEK_SET);
		cout<<"****"<<ftell(f);
		g=fopen("Temp","w");
		while (fread(&Lidd,sizeof(Lidd),1,f)  )
		  {
		  if (k != (i-1) ) fwrite(&Lidd,sizeof(Lidd),1,g);
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
    }
    else
    {
      cout<<"\nВыберите файл для работы.\n"
          <<"Нажмите [ 1 ] в разделе М Е Н Ю.";
      getch();
    }
}
//******************** поиск лидара в базе *****************
void SearchLidd()
{
 int i=0;
  if (flag)
    {
  f=fopen(NameFile,"r");
  char search[15];
  cout<<"Введите наименование лидара для поиска --> ";
  cin.getline(search, 15);

  cout<<"********  Поиск лидара в базе данных  ********\n"
      <<"****************************************\n";
  while (fread(&Lidd,sizeof(Lidd),1,f)  )
	{

	 
	 if ( strcmp(search, Lidd.name) == 0 )
	 {
	 	cout<<"Номер записи = "<<i+1<<"\n\n";
	    OutpuLidar(Lidd);
	    cout<<"****************************************"<<sizeof(Lidd)<<"\n";
	    i++;
	 	if (i % 3 == 0)  //вывод нескольких записей лидара
		{
			getch();
			system("cls");
			cout<<"********  Поиск лидара в базе данных  ********\n"
		    	<<"****************************************\n";
		}
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



//Начало программы

int main()
{
setlocale(0,"");
char ch;
  system("cls");
  do
  {
  menu();
  ch=getch();
  switch (ch)
   {
    case '1':   system("cls");
		CreateOpenFile(NameFile,flag); //создание и открытие файла базы данных
		break;
    case '2':   system("cls");
		RecordLidd(NameFile,Lidd,flag); //запись данных в файл
		break;
    case '3':   system("cls"); // Удаление лидара из базы данных
		cout<<"Удаление товара из базы данных\n";
		DeleteLidd(NameFile,Lidd,flag);
		getch();
		break;
    case '4':   system("cls");	// вывод файла на экран
		VivodFile();
		break;
    case '5':   system("cls");		//обновление записи о лидаре с заданным номером
		UpdateLidd(NameFile,Lidd,flag);
		break;
    case '6':	
		system("cls");
		cout<<"Выполнение задания в соответствии с вариантом:\nПоиск необходимого лидара в базе данных\n";
		SearchLidd();
		getch();
		
		break;
   }
  }
  while	( ch!=27 ) ;
  return 0;
}

