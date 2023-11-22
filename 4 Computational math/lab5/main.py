import sys

import functions
import math_solve


def hello():
    print("Лабораторная №5: \"Численное дифференцирование и задача Коши\"")
    print("Вариант: метод Рунге-Кутты 4-го порядка")
    print("Автор: Неграш А.В., P3230\n")
    print_line()


def print_line():
    print("")


def start_ui():
    is_enter_not_good = True
    while is_enter_not_good:
        functions.print_functions()
        functions_id = is_number(input("> "))
        if 1 <= functions_id <= 3:
            is_enter_not_good = False
            n = enter_amount()
            h = enter_step()
            initial_point = enter_initial_point()
            result_points = math_solve.runge_kutta_solve(initial_point, functions_id, h, n)
            print_line()
            print_result(result_points)
            functions.plot_graph(functions_id, result_points)
        else:
            print("Функции под номером " + str(int(functions_id)) + " не существует. Выберите одну из предложенных.")
            print_line()


def enter_amount():
    print_line()
    n = 0
    is_good_enter = True
    print("Введите значение n (количество точек):")
    while is_good_enter:
        n = int(input("> "))
        if n > 0:
            is_good_enter = False
        else:
            print("Количество точек должно быть больше 0. Попробуйте ещё раз.")
    return n


def enter_step():
    print_line()
    print("Введите значение h (шаг):")
    h = -1
    is_good_enter = True
    while is_good_enter:
        h = is_number(input("> "))
        if h <= 0.0:
            print("Значение шага должно быть больше 0. Попробуйте ещё раз.")
        else:
            is_good_enter = False
    return h


def enter_initial_point():
    print_line()
    print("Введите начальное значение x: ")
    x = is_number(input("> "))
    print_line()
    print("Введите начальное значение y: ")
    y = is_number(input("> "))
    initial_point = [x, y]
    return initial_point


def print_result(points):
    print("Вычисленные точки:")
    for i in points:
        print("x = {:6.5f}".format(i[0]) + "; y = {:6.6f}".format(i[1]))
    return 0


def is_number(s):
    try:
        if float(s) or s.isnumeric():
            return float(s)
        else:
            print("Надо было вводить число. Система перегружена, у неё депрессия, запустите позже.")
            sys.exit()
    except ValueError:
        print("Надо было вводить число. Система перегружена, у неё депрессия, запустите позже.")
        sys.exit()


hello()
start_ui()
