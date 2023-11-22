import numpy as np

size = 30

x = np.linspace(-2, 2, size)
y = 7*x**3 - 2*x**2 + 3*x - 2

noise = np.random.normal(0, 0.001, size)

y = y + noise

for i in range(size):
    print(str(x[i]) + " " + str(y[i]))

print("c")
