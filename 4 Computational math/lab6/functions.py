import sys


def function1(x, y):
    return x ** 2 + y ** 2


def function2(x, y):
    return x * y


def print_functions():
    print("Выберите уравнение:")
    print("1: f(x,y) = x² + y²\n"
          "2: f(x,y) = x * y")


def read_function():
    print_functions()
    fun_num = 0
    while fun_num == 0:
        try:
            fun_num = int(input('> '))
            if fun_num < 1 or fun_num > 2:
                print("Уравнения с таким номером не существует. Попробуйте ещё раз")
                fun_num = 0
            else:
                if fun_num == 1:
                    print("Отлично! Вы выбрали функцию f(x,y) = x² + y²")
                    return function1
                else:
                    print("Отлично! Вы выбрали функцию f(x,y) = x * y")
                    return function2
        except ValueError:
            print("Нужно ввести одну цифру \"1\" или \"2\". Попробуйте ещё раз")
            fun_num = 0


def read_interval(char):
    while True:
        print("Введите левую границу промежутка для " + str(char) + ":")
        try:
            left_border = float(input('> '))
            break
        except ValueError:
            print("Неверный формат ввода")

    while True:
        print("Теперь введите правую границу промежутка для " + str(char) + ":")
        try:
            right_border = float(input('> '))
            break
        except ValueError:
            print("Неверный формат ввода")

    if left_border == right_border:
        print("Промежуток пустой, считать нечего, спасибо, что использовали этот решатель.")
        sys.exit()

    if left_border > right_border:
        return right_border, left_border
    return left_border, right_border


def read_accuracy():
    print("Последнее, что нужно ввести - погрешность:")
    while True:
        try:
            eps = float(input('> '))
            return eps
        except ValueError:
            print("Неверный формат ввода")
