#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale.h>

using namespace std;

int main() 
{
	setlocale(LC_ALL, "rus");																				// Отвечает за корректный вывод символов Русского языка
    int N;
    cout << "Введите размер матрицы N (N <= 10): ";															// Задаём размер матрицы
    cin >> N;

    while (N < 1 || N > 10) 
	{
        cout << "Ошибка! Размер матрицы должен быть в диапазоне от 1 до 10. Введите корректный размер: ";	// Если пользователь нарушили условие ввода
        cin >> N;
    }
	
    double A[N][N];
    srand(time(NULL));

    for (int i = 0; i < N; i++)																				// Заполнение матрицы случайными числами
	{
        for (int j = 0; j < N; j++) 
		{
            A[i][j] = rand() % 100;																			// генерация случайного числа от 0 до 99
        }
    }

    cout << "Получаемая матрица:" << endl;																	// Вывод матрицы на экран
    for (int i = 0; i < N; i++) 
	{
        for (int j = 0; j < N; j++) 
		{
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }

    double sum = 0;																							// Вычисление среднего арифметического элементов четных строк матрицы A
    int count = 0;
    for (int i = 1; i < N; i += 2) 
	{
        for (int j = 0; j < N; j++) 
		{
            sum += A[i][j];
            count++;
        }
        double average = sum / count;
        cout << "Среднее арифметическое элементов " << i+1 << "-й строки: " << average << endl;
        sum = 0;
        count = 0;
    }

    return 0;
}
