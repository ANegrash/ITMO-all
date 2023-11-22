import re
import matplotlib.pyplot as plt
import operator as op
import numpy as np


def print_line():
    print("")


def print_help():
    print("Список команд:\n"
          "[x] [y]  - добавить точку (введите 2 числа через пробел)\n"
          "x [x]    - посчитать значение y в заданной координате\n"
          "o [id]   - наложить дополнительный график. В качестве параметра передайте id одного из уравнений:")
    for i in range(1, 5):
        print("     " + str(i) + ": " + get_add_func_label(i))
    print("     0: удалить все дополнительные графики\n"
          "d        - удалить все точки\n"
          "v        - просмотреть введённые точки\n"
          "c        - посчитать полином\n"
          "h        - вывод списка команд\n"
          "q        - выход из программы")
    print_line()


def print_err():
    print("Некорректная команда. Для просмотра списка возможных команд введите \"h\".")


def add_arrs(arr1, arr2):
    return list(map(op.add, arr1, arr2))


def multiply_arr(arr, coef):
    return [a * coef for a in arr]


def compute_multi(arr, pair):
    if len(arr) == 0:
        return [pair[0], pair[1]]

    multi1 = multiply_arr(arr, pair[0]) + [0]
    multi2 = [0] + multiply_arr(arr, pair[1])

    return add_arrs(multi1, multi2)


def generate_basis_poly(lst, i):
    ret = []
    xi = lst[i][0]
    for j in [x for x in range(len(lst)) if x != i]:
        xj = lst[j][0]
        ret = compute_multi(ret, (1 / (xi - xj), -xj / (xi - xj)))
    return ret


def generate_polynomial(lst):
    ret = generate_basis_poly(lst, 0)
    ret = multiply_arr(ret, lst[0][1])
    for i in range(1, len(lst)):
        newarr = generate_basis_poly(lst, i)
        newarr = multiply_arr(newarr, lst[i][1])
        ret = add_arrs(ret, newarr)

    return ret


def frm(num):
    return "{:.4f}".format(num)


def polynom_to_str(pol):
    ret = "y ="
    for i in range(0, len(pol)):
        if pol[i] >= 0:
            ret += " + "
        else:
            ret += " - "
        ret += frm(abs(pol[i]))
        if i < len(pol) - 1:
            ret += "x"
            power = len(pol) - i - 1
            if power > 1:
                if power == 2:
                    ret += "²"
                elif power == 3:
                    ret += "³"
                elif power == 4:
                    ret += "⁴"
                else:
                    ret += "^" + str(power)
    return ret


def edges(lst):
    max = lst[0][0]
    min = lst[0][0]
    for i in lst:
        if i[0] > max:
            max = i[0]
        if i[0] < min:
            min = i[0]
    return (min, max)


def plot(pol, lab, min, max, id):
    plt.title("Полином Лагранжа:")
    x = np.linspace(min, max, 1000)
    y = x * 0
    for i in range(len(pol)):
        y += pol[i] * (x ** (len(pol) - i - 1))

    y2 = 0
    if id == 1:
        y2 = x - 3
    elif id == 2:
        y2 = 2 * x ** 2 - 4 * x + 2
    elif id == 3:
        y2 = 7 * x ** 3 - 2 * x ** 2 + 3 * x - 2
    elif id == 4:
        y2 = np.sin(x)

    lab2 = get_add_func_label(id)

    plt.plot(x, y, 'r', label=lab)
    if 1 <= id <= 4:
        plt.plot(x, y2, 'k:', label=lab2)
    plt.legend(loc='upper left')


def compute(lst, id):
    if len(lst) < 2:
        print("Для проведения вычислений необходимо ввести хотя бы 2 точки")
        return []

    try:
        pol = generate_polynomial(lst)
    except ZeroDivisionError:
        print("Невозможно высчитать полином Лагранжа для введённого набора данных")
        return []

    print_line()
    print("Формула полинома:")
    str = polynom_to_str(pol)
    print(str)
    print_line()

    edge = edges(lst)
    plot(pol, str, edge[0], edge[1], id)
    plt.scatter(*zip(*lst))
    plt.show()

    return pol


def display(lst):
    print_line()
    print("Точки:")
    for a in lst:
        print("x = " + frm(a[0]) + "; y = " + frm(a[1]) + ";")
    print_line()


def calc_y(coefs, x):
    if len(coefs) == 0:
        print("Сначала сгенерируйте полином")
        return
    print("Полином: " + polynom_to_str(coefs))
    y = 0
    for i in range(len(coefs)):
        y += coefs[i] * (x ** (len(coefs) - i - 1))
    print("Для x = " + frm(x) + " y = " + frm(y))


def get_add_func_label(id):
    if id == 1:
        return "y = x - 3"
    elif id == 2:
        return "y = 2x² - 4x + 2"
    elif id == 3:
        return "y = 7x³ - 2x² + 3x - 2"
    elif id == 4:
        return "y = sin(x)"


def prompt():
    point_lst = []
    coefs = []
    id = 0
    while 1:
        try:
            inp = input("> ")
        except EOFError:
            print("")
            break

        if re.match(r"^-?\d+.?\d* -?\d+.?\d*$", inp):
            point_lst.append(tuple(map(float, inp.split())))
            print("Добавлена точка x = " + inp.split()[0] + "; y = " + inp.split()[1])
        elif re.match(r"^x -?\d+.?\d*$", inp):
            calc_y(coefs, float(inp.split()[1]))
        elif re.match(r"^o [0-4]$", inp):
            id = int(inp.split()[1])
            if id > 0:
                print("Добавлено " + get_add_func_label(id) + " на график.")
            else:
                print("Дополнительная функция удалена с графика.")
        elif inp == "h":
            print_help()
        elif inp == "v":
            display(point_lst)
        elif inp == "c":
            coefs = compute(point_lst, id)
        elif inp == "d":
            point_lst = []
            print("Все ранее добавленные точки успешно удалены")
        elif inp == "q":
            print("Спасибо за использование нашей программы. Поставьте зачёт, пожалуйста...")
            break
        else:
            print_err()


def main():
    print("Лабораторная №4: \"Интерполяция и аппроксимация\"")
    print("Вариант: метод интерполяции полиномом Лагранжа")
    print("Автор: Неграш А.В., P3230\n")

    print_help()
    prompt()


main()
