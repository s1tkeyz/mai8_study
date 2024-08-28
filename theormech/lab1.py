import math
import sympy as s
import matplotlib.pyplot as plt
import numpy as n
from matplotlib.animation import FuncAnimation

# Временной параметр симуляции
t = s.Symbol('t')

# Зависимость x(t)
x = (2 + s.cos(6 * t)) * s.cos(t + 6/5 * s.cos(6 * t))
# Зависимость y(t)
y = (2 + s.cos(6 * t)) * s.sin(t + 6/5 * s.cos(6 * t))

# Скорость Vx(t)
Vx = s.diff(x, t)
# Скорость Vy(y)
Vy = s.diff(y, t)
# Модуль скорости
v = (Vx ** 2 + Vy ** 2) ** 0.5 

# Ускорение Ax
Ax = s.diff(Vx, t)
# Ускорение Ay
Ay = s.diff(Vy, t)
# Модуль ускорения
a = (Ax ** 2 + Ay ** 2) ** 0.5
# Модуль тангенциального ускорения
Atan = s.diff(v, t)
# Модуль центростремительного ускорения
Anor = (a ** 2 - Atan ** 2) ** 0.5

# находим координаты вектора тангенциального ускорения:
# нормируем вектор скорости и умножаем на величину тангенциального
ATanx = Vx / v * Atan
ATany = Vy / v * Atan


# Находим координаты вектора центростремительного ускорения
ANorX = Ax - ATanx
ANorY = Ay - ATany

ANor = (ANorX ** 2 + ANorY ** 2) ** 0.5

# N - единичный вектор, сонаправленный с центростремительным ускорением
Nx = ANorX / ANor
Ny = ANorY / ANor

# Вычисляем вектор радиуса кривизны
CRx = Nx * v**2 / Anor
CRy = Ny * v**2 / Anor

FRAMES_COUNT = 300

T = n.linspace(0, 10, FRAMES_COUNT)

X = n.zeros_like(T)
Y = n.zeros_like(T)
VX = n.zeros_like(T)
VY = n.zeros_like(T)
AX = n.zeros_like(T)
AY = n.zeros_like(T)
CRX = n.zeros_like(T)
CRY = n.zeros_like(T)

for i in n.arange(len(T)):
    X[i] = s.Subs(x, t, T[i])
    Y[i] = s.Subs(y, t, T[i])
    VX[i] = s.Subs(Vx, t, T[i])
    VY[i] = s.Subs(Vy, t, T[i])
    AX[i] = s.Subs(Ax, t, T[i])
    AY[i] = s.Subs(Ay, t, T[i])
    CRX[i] = s.Subs(CRx, t, T[i])
    CRY[i] = s.Subs(CRy, t, T[i])

fig = plt.figure()

axis = fig.add_subplot(1, 1, 1)
axis.axis('equal')
axis.set(xlim = [-5, 5], ylim = [-5, 5])
axis.plot(X, Y)

Pnt = axis.plot(X[0], Y[0], marker = 'o')[0]
Vp = axis.plot([X[0], X[0] + VX[0]], [Y[0], Y[0] + VY[0]], 'r')[0]
Ap = axis.plot([X[0], X[0] + AX[0]], [Y[0], Y[0] + AY[0]], 'g')[0]
Cr = axis.plot([X[0], X[0] + CRX[0]], [Y[0], Y[0] + CRY[0]], 'm')[0]

def Vect_arrow(X, Y, ValX, ValY):
    a = 0.2
    b = 0.3
    Arx = n.array([-b, 0, -b])
    Ary = n.array([a, 0, -a])
    alp = math.atan2(ValY, ValX)
    RotArx = Arx * n.cos(alp) - Ary * n.sin(alp)
    RotAry = Arx * n.sin(alp) + Ary * n.cos(alp)

    Arx = X + ValX + RotArx
    Ary = Y + ValY + RotAry
    return Arx, Ary

RVx, RVy = Vect_arrow(X[0], Y[0], VX[0], VY[0])
RAx, RAy = Vect_arrow(X[0], Y[0], AX[0], AY[0])
CRx, CRy = Vect_arrow(X[i], Y[i], CRX[0], CRY[0])
Varrow = axis.plot(RVx, RVy, 'red')[0]
Aarrow = axis.plot(RAx, RAy, 'green')[0]
CRarrow = axis.plot(CRx, CRy, 'magenta')[0]

def animation(i):
    Pnt.set_data(X[i], Y[i])
    Vp.set_data([X[i], X[i] + VX[i]],[Y[i], Y[i] + VY[i]])
    Ap.set_data([X[i], X[i] + AX[i]],[Y[i], Y[i] + AY[i]])
    Cr.set_data([X[i], X[i] + CRX[i]],[Y[i], Y[i] + CRY[i]])
    RVx, RVy = Vect_arrow(X[i], Y[i], VX[i], VY[i])
    RAx, RAy = Vect_arrow(X[i], Y[i], AX[i], AY[i])
    CRx, CRy = Vect_arrow(X[i], Y[i], CRX[i], CRY[i])
    Varrow.set_data(RVx, RVy)
    Aarrow.set_data(RAx, RAy)
    CRarrow.set_data(CRx, CRy)

an = FuncAnimation(fig, animation, frames=FRAMES_COUNT, interval=1)
plt.show()