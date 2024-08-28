import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import sympy as sp

# Параметры
L = 2
l = 1
t = sp.Symbol('t')

# Зависимость phi(t)
phi = sp.cos(3 * t) - sp.pi / 2

# Зависимость s(t)
s = 0.5 * sp.cos(2 * t)

# Координаты кончика стержня
stickX = L * sp.cos(phi)
stickY = L * sp.sin(phi)

# Координаты конца пружины
springX = l * sp.cos(phi) + s * sp.cos(phi)
springY = l * sp.sin(phi) + s * sp.sin(phi)

# Скорость конца пружины
VxSpr = sp.diff(springX, t)
VySpr = sp.diff(springY, t)
# Модуль скорости конца пружины
VSpr = sp.sqrt(VxSpr**2 + VySpr**2)

# Ускорение конца пружины
WxSpr = sp.diff(VxSpr, t)
WySpr = sp.diff(VySpr, t)
# Модуль ускорения конца пружины
WSpr = sp.sqrt(WxSpr**2 + WySpr**2)

# Количество кадров анимации
countOfFrames = 550

T_start, T_stop = 0, 10
T = np.linspace(T_start, T_stop, countOfFrames)

# Создаём функции вышеописанных зависимостей
StickX_def = sp.lambdify(t, stickX)
StickY_def = sp.lambdify(t, stickY)
SpringX_def = sp.lambdify(t, springX)
SpringY_def = sp.lambdify(t, springY)
VSpr_def = sp.lambdify(t, VSpr)
WSpr_def = sp.lambdify(t, WSpr)

# Высчисляем массивы значений функций
StickX = StickX_def(T)
StickY = StickY_def(T)
SpringX = SpringX_def(T)
SpringY = SpringY_def(T)
VSpr = VSpr_def(T)
WSpr = WSpr_def(T)

# Координаты подвеса
SuspensionX = -1
SuspensionY = 1

# Размер крепления
bracingSize = 0.1

# Координаты крепления стержня
bracingX = [SuspensionX, SuspensionX - bracingSize , SuspensionX + bracingSize, SuspensionX]
bracingY = [SuspensionY, SuspensionY + 2 * bracingSize , SuspensionY + 2 * bracingSize, SuspensionY]

fig = plt.figure(figsize=(17, 8))

ax1 = fig.add_subplot(1, 2, 1)
ax1.set(xlim=[SuspensionX - 1.1 * L, SuspensionX + 1.1 * L], ylim=[-2 * L, max(bracingY) * 1.1])
ax1.set_xlabel('Axis X')
ax1.set_ylabel('Axis Y')

# График зависимости абсолютной скорости V(t)
PHI = fig.add_subplot(2, 2, 2)
PHI.set_xlabel('T')
PHI.set_ylabel('V')
PHI.set(xlim=[T_start, T_stop], ylim=[VSpr.min(), VSpr.max()])

tv_x = [T[0]]
tv_y = [VSpr[0]]

TV, = PHI.plot(tv_x, tv_y, '-')

# График зависимости абсолютного ускорения W(t)
S = fig.add_subplot(2, 2, 4)
S.set_xlabel('T')
S.set_ylabel('W')
S.set(xlim=[T_start, T_stop], ylim=[WSpr.min(), WSpr.max()])

tw_x = [T[0]]
tw_y = [WSpr[0]]

TW, = S.plot(tw_x, tw_y, '-')

# Рисуем объекты
Stick, = ax1.plot([SuspensionX, StickX[0] + SuspensionX], [SuspensionY, StickY[0] + SuspensionY], color='red')
Body, = ax1.plot( [SpringX[0] + SuspensionX], [SpringY[0] + SuspensionY],marker='o', color='grey', markersize=12)
Spring, = ax1.plot([SuspensionX, SpringX[0] + SuspensionX], [SuspensionY, SpringY[0] + SuspensionY], color='black', linestyle=':', linewidth=3)
bracing, = ax1.plot(bracingX, bracingY, color='black')

# Функция анимации
def anima(i):
    Stick.set_data([SuspensionX, StickX[i] + SuspensionX], [SuspensionY, StickY[i] + SuspensionY])
    Body.set_data([SpringX[i] + SuspensionX], [SpringY[i] + SuspensionY])
    Spring.set_data([SuspensionX, SpringX[i] + SuspensionX], [SuspensionY, SpringY[i] + SuspensionY])
    tv_x.append(T[i])
    tv_y.append(VSpr[i])
    tw_x.append(T[i])
    tw_y.append(WSpr[i])
    TV.set_data(tv_x, tv_y)
    TW.set_data(tw_x, tw_y)
    if i == countOfFrames - 1:
        tv_x.clear()
        tv_y.clear()
        tw_x.clear()
        tw_y.clear()
    return Stick, Body, Spring, TV, TW

# Показ анимации
anim = FuncAnimation(fig, anima, frames=countOfFrames, interval=40, blit=True)
plt.show()