import Service


def hello():
    print("Лабораторная №3: \"Численное интегрирование\"")
    print("Вариант: метод Симпсона (метод парабол)")
    print("Автор: Неграш А.В., P3230\n")


def get_data():
    print("""Выберите уравнение:
    1: x²
    2: 1 / x
    3: x³ - 3x² + 6x - 19""")

    match input("> "):
        case "1":
            func = lambda x: x ** 2
            print("Вы выбрали функцию x²")
        case "2":
            func = lambda x: 1 / x
            print("Вы выбрали функцию 1 / x")
        case "3":
            func = lambda x: x ** 3 - 3 * (x ** 2) + 6 * x - 19
            print("Вы выбрали функцию x³ - 3x² + 6x - 19")
        case _:
            print("Вы ввели некорректное значение")
            return get_data()
    left_border, right_border = Service.get_interval()
    return func, left_border, right_border, Service.get_sigma()


def simpson(func, a, b, eps):
    max_itr = 10
    n = 4

    result = float('inf')

    while n <= n * (2 ** max_itr):
        last_result = result
        result = func(a) + func(b)

        h = (b - a) / n
        x = a + h

        try:
            for i in range(n - 1):
                if i % 2 == 0:
                    result += 4 * func(x)
                else:
                    result += 2 * func(x)
                x += h
        except ZeroDivisionError:
            print("Найден разрыв 2 рода. Работа программы завершена")
            return None, None
        result *= h / 3

        if abs(result - last_result) <= eps:
            break
        else:
            n *= 2

    return result, n


hello()
func, left_border, right_border, eps = get_data()
result, n = simpson(func, left_border, right_border, eps)
if result is not None:
    print("Подсчитанный интеграл на интервале [" + str(left_border) + "; " + str(right_border) + "] равен: " + str(
        result))
    print("Количество разбиений: " + str(n))
