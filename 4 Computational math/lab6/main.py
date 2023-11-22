from functions import *

import numpy as np

LEFT = "left_method"
MIDDLE = "middle_method"
RIGHT = "right_method"


def hello():
    print("Лабораторная №6: \"Зачётная\"")
    print("Вариант: интегрирование по области")
    print("Автор: Неграш А.В., P3230")
    print_line()


def print_line():
    print("")


def solve_integral(count_steps, a, b, c, d, function, mode):
    step_x = abs(b - a) / count_steps
    step_y = abs(d - c) / count_steps
    x = np.linspace(a, b, count_steps)
    y = np.linspace(c, d, count_steps)
    integral = 0

    for i in range(0, len(y)):
        for j in range(0, len(x)):
            if mode == LEFT:
                integral += function(x[j], y[i]) * step_x * step_y
            elif mode == MIDDLE:
                integral += function(x[j] + step_x / 2, y[i] + step_y / 2) * step_x * step_y
            elif mode == RIGHT:
                integral += function(x[j] + step_x, y[i] + step_y) * step_x * step_y

    return integral


def rule_runge(step_num, accuracy, a, b, c, d, f, mode):
    I_0 = solve_integral(step_num, a, b, c, d, f, mode)
    step_num *= 2
    I_1 = solve_integral(step_num, a, b, c, d, f, mode)
    delta = abs(I_1 - I_0) / 3

    while delta > accuracy:
        I_0 = I_1
        step_num *= 2
        I_1 = solve_integral(step_num, a, b, c, d, f, mode)
        delta = abs(I_1 - I_0) / 3

        if step_num > 400:
            return step_num

    return step_num


hello()
function = read_function()
a, b = read_interval("X")
c, d = read_interval("Y")
eps = read_accuracy()

print_line()
print("Приблизительное значение вычисленного интеграла методом левых прямоугольников:\n"
      "I ≈ " + str(solve_integral(rule_runge(10, eps, a, b, c, d, function, LEFT), a, b, c, d, function, LEFT)))

print_line()
print("Приблизительное значение вычисленного интеграла методом средних прямоугольников:\n"
      "I ≈ " + str(solve_integral(rule_runge(10, eps, a, b, c, d, function, MIDDLE), a, b, c, d, function, MIDDLE)))

print_line()
print("Приблизительное значение вычисленного интеграла методом правых прямоугольников:\n"
      "I ≈ " + str(solve_integral(rule_runge(10, eps, a, b, c, d, function, RIGHT), a, b, c, d, function, RIGHT)))
