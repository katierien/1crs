#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale.h>

using namespace std;

int main() 
{
	setlocale(LC_ALL, "rus");																				// �������� �� ���������� ����� �������� �������� �����
    int N;
    cout << "������� ������ ������� N (N <= 10): ";															// ����� ������ �������
    cin >> N;

    while (N < 1 || N > 10) 
	{
        cout << "������! ������ ������� ������ ���� � ��������� �� 1 �� 10. ������� ���������� ������: ";	// ���� ������������ �������� ������� �����
        cin >> N;
    }
	
    double A[N][N];
    srand(time(NULL));

    for (int i = 0; i < N; i++)																				// ���������� ������� ���������� �������
	{
        for (int j = 0; j < N; j++) 
		{
            A[i][j] = rand() % 100;																			// ��������� ���������� ����� �� 0 �� 99
        }
    }

    cout << "���������� �������:" << endl;																	// ����� ������� �� �����
    for (int i = 0; i < N; i++) 
	{
        for (int j = 0; j < N; j++) 
		{
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }

    double sum = 0;																							// ���������� �������� ��������������� ��������� ������ ����� ������� A
    int count = 0;
    for (int i = 1; i < N; i += 2) 
	{
        for (int j = 0; j < N; j++) 
		{
            sum += A[i][j];
            count++;
        }
        double average = sum / count;
        cout << "������� �������������� ��������� " << i+1 << "-� ������: " << average << endl;
        sum = 0;
        count = 0;
    }

    return 0;
}
