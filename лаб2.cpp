#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//��� ������ ��� ����
struct TData
{
int D,M,G;
} ;
//��� ������ ��� ������
struct Lidar
{
  char name[25];
  char madein[25];
  float cena;
  TData data;
};

//��� ������ ��� ����� �����
typedef char TName[25];
//��� ������ ��� �������� ����������
typedef FILE TFile;
//���������� ��� ������
Lidar Lidd;
//���������� ��� ����� �����
TName NameFile;
//�������� ����������
TFile *f;
//���� ������ ����� ��� ������
int flag=0;

//** ����� ���� ************************************************************
void menu(void)
{ system("cls");
  cout<<"******** � � � � ********\n\n"
      <<"[1]-��������/�������� ���� �������\n"
      <<"[2]-���������� ������ � ����\n"
      <<"[3]-�������� ������ �� ����\n"
      <<"[4]-�������� ���� ����\n"
      <<"[5]-���������� ������ � �������� �������\n"
      <<"[6]-���������� �������. ����� ������ �� ��������.\n"
      <<"[ ESC ]-�����\n";
}
//** ���� ������ **************************************************
void InpuLidar(Lidar &Lidd)
{
cin.clear(); //�������� ����� � ����� ��������� ���������������� � 0
cin.sync();

cout<<"���������� ������:\n";
cout<<"������������ ������ ->"; //gets(Lidd.name);
cin.getline(Lidd.name,25);

cout<<"\n���� ������������:\n";
cout<<"����->";                cin>>Lidd.data.D;
cout<<"�����->";               cin>>Lidd.data.M;
cout<<"���->";                 cin>>Lidd.data.G;

cout<<"��������� ������ ->";   cin>>Lidd.cena;
cin.clear(); //�������� ����� � ����� ��������� ���������������� � 0
cin.sync();

cout<<"������������� ->";     gets(Lidd.madein);

}
//** ����� ������ �� ����� ************************************************
void OutpuLidar(Lidar Lidd)
{
cout <<"������������ ������: "<<Lidd.name<<"\n"
     <<"���� ������������ ������: "
     <<Lidd.data.D<<":"<<Lidd.data.M<<":"<<Lidd.data.G<<"\n"
     <<"��������� ������: "<<Lidd.cena<<"\n"
     <<"�������������: "<<Lidd.madein<<"\n";
}
//** ��������/�������� ����� ���� ������ ********************************
void CreateOpenFile( TName &NameFile,int &flag )
{
 char ch;
 flag=0;
 cout<<"������� ��� ����� ��� ������-->";
 gets(NameFile);
 f=fopen(NameFile,"r");
 if (f==NULL)
    do
     {
     system("cls");
     cout<<"����� � ������ "
         <<NameFile
         <<" ���.\n\n"
         <<"������� ���� � ������ "
         <<NameFile;
     cout<<"������� [ Y ] / [ N ]\n";
     ch=getch();
     if (ch=='Y'||ch=='y')
	{
	  f=fopen(NameFile,"w");
	  cout<<"���� � ������ " <<NameFile<<" ������.\n"
          <<"\n\n��� ����������� ������� ����� �������\n";
	  getch();
	  flag=1;
	}
     if (ch=='N'||ch=='n')
	{
	  cout<< "���� �� ������.\n"
	      <<"\n\n��� ����������� ������� ����� �������\n";
	  getch();
	}
     }
     while ( ! (ch =='Y' || ch=='y' || ch=='N'  || ch=='n'));
    else
	{flag=1;
	cout<<"���� ������� ������\n"
	    <<"\n��� ����������� ������� ����� �������\n";
	getch();
	}
fclose(f);
}

//** ���������� ������ � ������ � ���� (� ���� ������) **********
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
      cout<<"\n�������� ���� ��� ������.\n"
          <<"������� [ 1 ] � ������� � � � �.";
      getch();
    }
}
//** ����� ����� (���� ������) �� ����� *****************
void VivodFile()
{

  int i=0;
  if (flag)
    {
  f=fopen(NameFile,"r+");

  cout<<"********  ����� ����� �� �����  ********\n"
      <<"****************************************\n";
      while (fread(&Lidd,sizeof(Lidd),1,f)  )
	{
	 cout<<"����� ������ = "<<i+1<<"\n\n";
	 OutpuLidar(Lidd);
	 cout<<"****************************************"<<sizeof(Lidd)<<"\n";
	 i++;
	 if (i % 3 == 0)  //����� ���������� �������
		{
		getch();
		system("cls");
		cout<<"********  ����� ����� �� �����  ********\n"
		    <<"****************************************\n";
		}
	}
      getch();
      fclose(f);
    }
    else
    {
      cout<<"\n�������� ���� ��� ������.\n"
          <<"������� [ 1 ] � ������� � � � �.";
      getch();
    }

}
//** ������ ����� *****************************
long filesize(TFile *f)
{
   long curpos, length;

   curpos = ftell(f);		//���������� ������� ���������
   fseek(f, 0L, SEEK_END);	//���������� �� ����� �����
   length = ftell(f);		//���������� ��������� � ����� �����
   fseek(f, curpos, SEEK_SET);	//���������� �� ������ ���������
   return length;
}


//** ���������� ������ � �������� ������� ******
void UpdateLidd(TName NameFile, Lidar &Lidd, int flag)
{
  long i=0;
  if (flag)
    {
	f=fopen(NameFile,"r+");

	cout<<"********  ���������� ������ � �������� �������  ********\n\n"
	    <<"********************************************************\n\n"
	    <<"������� ����� ������ ��� ���������� "
	    <<"�� "
	    <<(filesize(f)/sizeof(Lidd))
	    <<" --> ";
	cin>>i;
	//long q;
    fpos_t q;
	//������������ �� ������ � ������� i
	fseek(f, (i-1) * sizeof(Lidd) ,SEEK_CUR);
	//���������� ������� ���������
	fgetpos(f,&q);

	fread(&Lidd,sizeof(Lidd),1,f);
	OutpuLidar(Lidd);
	cout<<"****************************************\n";

	char ch;
	cout<<"�������� ������?\n������� [ Y ] / [ N ]\n";
	do
	   {
	   ch=getch();
	   if (ch=='Y'||ch=='y')
		{
		//������ ����� ��������
		InpuLidar(Lidd);
		//��������� �� ������ �����
		fsetpos(f,&q);
		//���������� ����� ��������
		fwrite(&Lidd,sizeof(Lidd),1,f);
		cout<<"������ ���������.\n";
		}
	   if (ch=='N'||ch=='n')
		{
		cout<<"������ �� ����������.\n";
		}
	   }
	while ( ! (ch =='Y' || ch=='y' || ch=='N'  || ch=='n'));
    cout<<"\n��� ����������� ������� ����� �������\n";
    getch();
    fclose(f);
    }
    else
    {
      cout<<"\n�������� ���� ��� ������.\n"
          <<"������� [ 1 ] � ������� � � � �.";
      getch();
    }
}
//** �������� ������ �� ���� **********************************
void DeleteLidd(TName NameFile, Lidar &Lidd, int flag)
{
  long i=0,k=0;
  TFile *g;
  if (flag)
    {
	f=fopen(NameFile,"r+");

	cout<<"********  �������� ������ � �������� �������  ********\n\n"
	    <<"********************************************************\n\n"
	    <<"������� ����� ������ ��� �������� "
	    <<"�� "
	    <<(filesize(f)/sizeof(Lidd))
	    <<" --> ";
	cin>>i;

	//������������ �� ������ � ������� i
	fseek(f, (i-1) * sizeof(Lidd) ,SEEK_CUR);
	fread(&Lidd,sizeof(Lidd),1,f);
	OutpuLidar(Lidd);
	cout<<"****************************************\n";

	char ch;
	cout<<"������� ������?\n������� [ Y ] / [ N ]\n";
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
		cout<<"������ ���������.\n";
		fclose(g);
		fclose(f);
		remove(NameFile); 	//������� ������ ����
		rename("Temp",NameFile);//��������������� ��������� ����
		}
	   if (ch=='N'||ch=='n')
		{
		cout<<"������ �� ����������.\n";
		}
	   }
	while ( ! (ch =='Y' || ch=='y' || ch=='N'  || ch=='n'));
    cout<<"\n��� ����������� ������� ����� �������\n";
    getch();
    }
    else
    {
      cout<<"\n�������� ���� ��� ������.\n"
          <<"������� [ 1 ] � ������� � � � �.";
      getch();
    }
}
//******************** ����� ������ � ���� *****************
void SearchLidd()
{
 int i=0;
  if (flag)
    {
  f=fopen(NameFile,"r");
  char search[15];
  cout<<"������� ������������ ������ ��� ������ --> ";
  cin.getline(search, 15);

  cout<<"********  ����� ������ � ���� ������  ********\n"
      <<"****************************************\n";
  while (fread(&Lidd,sizeof(Lidd),1,f)  )
	{

	 
	 if ( strcmp(search, Lidd.name) == 0 )
	 {
	 	cout<<"����� ������ = "<<i+1<<"\n\n";
	    OutpuLidar(Lidd);
	    cout<<"****************************************"<<sizeof(Lidd)<<"\n";
	    i++;
	 	if (i % 3 == 0)  //����� ���������� ������� ������
		{
			getch();
			system("cls");
			cout<<"********  ����� ������ � ���� ������  ********\n"
		    	<<"****************************************\n";
		}
	 } 
	}
    
	getch();
    fclose(f);
    }
    else
    {
      cout<<"\n�������� ���� ��� ������.\n"
          <<"������� [ 1 ] � ������� � � � �.";
      getch();
    }	
}



//������ ���������

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
		CreateOpenFile(NameFile,flag); //�������� � �������� ����� ���� ������
		break;
    case '2':   system("cls");
		RecordLidd(NameFile,Lidd,flag); //������ ������ � ����
		break;
    case '3':   system("cls"); // �������� ������ �� ���� ������
		cout<<"�������� ������ �� ���� ������\n";
		DeleteLidd(NameFile,Lidd,flag);
		getch();
		break;
    case '4':   system("cls");	// ����� ����� �� �����
		VivodFile();
		break;
    case '5':   system("cls");		//���������� ������ � ������ � �������� �������
		UpdateLidd(NameFile,Lidd,flag);
		break;
    case '6':	
		system("cls");
		cout<<"���������� ������� � ������������ � ���������:\n����� ������������ ������ � ���� ������\n";
		SearchLidd();
		getch();
		
		break;
   }
  }
  while	( ch!=27 ) ;
  return 0;
}

