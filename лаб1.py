import random

N = int(input("Введите размерность матрицы N (N <= 10): "))
while N < 1 or N > 10:
    N = int(input("Ошибка! Размерность матрицы должна быть в диапазоне от 1 до 10. Введите корректную размерность: "))

A = [[random.randint(0, 99) for j in range(N)] for i in range(N)]

print("Исходная матрица:")
for i in range(N):
    for j in range(N):
        print(A[i][j], end="\t")
    print()

sum = 0
count = 0
for i in range(1, N, 2):
    for j in range(N):
        sum += A[i][j]
        count += 1
    average = sum / count
    print("Среднее арифметическое элементов", i+1, "строки:", average)

input()
