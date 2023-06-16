import math
rad = 0
tg = 0
y = 0

x = int(input('Введите действительное значение х: '))

if x < -2:
    y = (x**2+4*x+3)**(1/4)
elif -2<=x<1:
    y = math.log((x**2+4*x+3),2.71828)
else:
    rad = math.radians((x**2+4*x+3)**(-1))
    tg = math.tan(rad)
    y = tg
print("Ответ: ", y)
input()



