import random
from calculator import Calculator

if __name__ == "__main__":
    print("Для запуска лабораторной выберите файл \'main.py\'")


def console_input():
    try:
        size = int(input("Пожалуйста, введите размер системы уравнений (от 2 до 20):").strip())
        if 20 >= size > 1:
            string_format = ""
            if size > 3:
                string_format = " ai1 ai2 ... ai" + str(size) + " | bi"
            elif size == 3:
                string_format = " ai1 ai2 ai3 | bi"
            elif size == 2:
                string_format = " ai1 ai2 | bi"

            print("Вводите строки системы в формате:\n" +
                  string_format)

            data_array = []
            for i in range(size):
                while 1:
                    current_line = list((input(str(i + 1) + ". ").split()))
                    if (int(len(current_line) - 2) != size) or (current_line[-2] != "|"):
                        print("Некорректный ввод: количество введённых элементов не соответствует заявленному")
                    else:
                        data_array.append(current_line)
                        break
            calculator = Calculator(size, optimize(data_array, size))
            calculator.calculate()
            del calculator
        else:
            print("Введено неверное значение. Пожалуйста, введите размер в диапазоне от 2 до 20")
            return
    except ValueError:
        print("Некорректный ввод. Требуется число")


def file_input(path):
    try:
        size = 0
        data_array = []

        with open(path, 'r', encoding='utf-8') as file:
            for line in file:
                if line != "\n" and line != " " and line != " \n":
                    size += 1
        file.close()

        with open(path, 'r', encoding='utf-8') as file:
            for row in file:
                line = list(row.split())
                if line[-2] != "|" or len(line) - 2 != size:
                    print("Файл содержит некорректные данные.")
                    return
                data_array.append(list(line))
        file.close()
        calculator = Calculator(size, optimize(data_array, size))
        calculator.calculate()
        del calculator
    except FileNotFoundError:
        print("Ошибка 404. Файл " + path + " не найден.")
        return
    except UnboundLocalError:
        return


def random_system():
    try:
        size = int(input("Пожалуйста, введите размер системы уравнений (от 2 до 20):").strip())

        if 20 >= size > 1:
            data_array = []
            for i in range(size):
                line = []
                for j in range(size):
                    line.append(random.random() * 100 - 50)
                line.append("|")
                line.append(random.random() * 100 - 50)
                data_array.append(line)
            calculator = Calculator(size, data_array)
            calculator.calculate()
            del calculator
        else:
            print("Введено неверное значение. Пожалуйста, введите размер в диапазоне от 2 до 20.")
            return
    except ValueError:
        print("Некорректный ввод. Требуется число")


def optimize(array, size):
    i = 0
    while i < size:
        j = 0
        while j < size:
            array[i][j] = float(array[i][j])
            j += 1
        array[i][j + 1] = float(array[i][j + 1])
        i += 1
    return array


