import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from scipy.integrate import odeint
import sympy as sp

# СДУ системы
def dsyseq(y, t, _mu, _g, _c, _P, _l):
    # y = [s phi s' phi'] -> dy = [s' phi' s'' phi'']
    dy = np.zeros_like(y)

    dy[0] = y[2]
    dy[1] = y[3]

    # a11 * s'' + a12 * phi'' = b1
    # a21 * s'' + a22 * phi'' = b2

    a11 = 1
    a12 = 0

    b1 = _g * sp.cos(y[1]) + (_l + y[0]) * y[3]**2 - (_c * _g * y[0]) / _P - (_mu * _g * y[2]) / _P

    a21 = 0
    a22 = (_l + y[0])

    b2 = -y[2] * y[3] - _g * (_l + y[0]) * sp.sin(y[1])

    d0 = a11 * a22 - a12 * a21
    dy[2] = (b1 * a22 - b2 * a12) / d0
    dy[3] = (a11 * b2 - a21 * b1) / d0
    
    return dy

# Начальные параметры
L = 2
P = 10
l = 0.5
c = 20
g = 9.81
mu = 2

s0 = 0
phi0 = sp.pi / 4
dphi0 = 0.3
ds0 = 0

# Начальные условия СДУ
y0 = [s0, phi0, ds0, dphi0]

t0 = 0
t1 = 10
frames = 600

T = np.linspace(t0, t1, frames)

# Решаем систему
Y = odeint(dsyseq, y0, T, (mu, g, c, P, l))

# Зависимость phi(t)
phi = np.subtract(Y[:,1], np.pi / 2)

# Зависимость s(t)
s = Y[:,0]

# Координаты кончика стержня
stickX = L * np.cos(phi)
stickY = L * np.sin(phi)

# Координаты конца пружины
springX = (l + s) * np.cos(phi)
springY = (l + s) * np.sin(phi)

StickX = stickX
StickY = stickY
SpringX = springX
SpringY = springY

# Координаты подвеса
SuspensionX = 0
SuspensionY = 0

# Размер крепления
bracingSize = 0.1

# Координаты крепления стержня
bracingX = [SuspensionX, SuspensionX - bracingSize , SuspensionX + bracingSize, SuspensionX]
bracingY = [SuspensionY, SuspensionY + 2 * bracingSize , SuspensionY + 2 * bracingSize, SuspensionY]

fig = plt.figure(figsize=(17, 8))

ax1 = fig.add_subplot(1, 2, 1)
ax1.set(xlim=[SuspensionX - 1.1 * L, SuspensionX + 1.1 * L], ylim=[-2 * L, max(bracingY) * 1.1])
ax1.set_xlabel('X')
ax1.set_ylabel('Y')

ax1.plot([SuspensionX - 1.1 * L, SuspensionX + 1.1 * L], [0, 0], 'grey')
ax1.plot([0, 0], [-2 * L, max(bracingY) * 1.1], 'grey')

# Стоим график phi(t)
phiPlt = fig.add_subplot(2, 2, 4)
phiPlt.set_xlabel("T, s")
phiPlt.set_ylabel("Phi, rad")
phiPlt.plot(T, phi)

# Строим график s(t)
sPlt = fig.add_subplot(2, 2, 2)
sPlt.set_xlabel("T, s")
sPlt.set_ylabel("S, m")
sPlt.plot(T, s)

# Рисуем объекты
Stick, = ax1.plot([SuspensionX, StickX[0] + SuspensionX], [SuspensionY, StickY[0] + SuspensionY], color='red', linewidth=3)
Body, = ax1.plot( [SpringX[0] + SuspensionX], [SpringY[0] + SuspensionY],marker='o', color='black', markersize=16)
Spring, = ax1.plot([SuspensionX, SpringX[0] + SuspensionX], [SuspensionY, SpringY[0] + SuspensionY], color='black', linestyle=':', linewidth=5)
Bracing, = ax1.plot(bracingX, bracingY, color='black')

# Функция анимации
def animation(i):
    Stick.set_data([SuspensionX, StickX[i] + SuspensionX], [SuspensionY, StickY[i] + SuspensionY])
    Body.set_data([SpringX[i] + SuspensionX], [SpringY[i] + SuspensionY])
    Spring.set_data([SuspensionX, SpringX[i] + SuspensionX], [SuspensionY, SpringY[i] + SuspensionY])
    return Stick, Body, Spring

# Показ анимации
anim = FuncAnimation(fig, animation, frames=frames, interval=40, blit=True)
plt.show()