import math
import matplotlib.pyplot as plt
import numpy as np
import math_solve


def print_functions():
    print("Выберите уравнение, которое необходимо решить:")
    print("1: y' = -2 * y " + "\n" +
          "2: y' = y * (x² + 1)" + "\n" +
          "3: y' = sin(x) + y")
    return 0


def get_function(number, x, y):
    if number == 1:
        return - 2 * y
    elif number == 2:
        return y * (x ** 2 + 1)
    elif number == 3:
        return math.sin(x) + y
    return 0


def get_derivative_of_function(number, x, C):
    if number == 1:
        return C * math.exp(-2 * x)
    elif number == 2:
        return C * math.exp((x ** 3) / 3 + x)
    elif number == 3:
        return (-math.sin(x) / 2) - (math.cos(x) / 2) + C * math.exp(x)
    return 0


def calculate_C(number, x, y):
    if number == 1:
        return y / math.exp(-2 * x)
    elif number == 2:
        return y / math.exp((x ** 3) / 3 + x)
    elif number == 3:
        return (y+(math.sin(x)/2)+(math.cos(x)/2))/math.exp(x)


def scan_x_for_minmax(points):
    max = points[0][0]
    min = points[0][1]

    for i in points:
        if i[0] > max:
            max = i[0]
        if i[0] < min:
            min = i[0]

    return [min, max]


def plot_graph(function, points):
    plt.title("Решатель уравнений методом Рунге–Кутты")
    minmax = scan_x_for_minmax(points)
    min = minmax[0]
    max = minmax[1]
    lagrange_polynomial = math_solve.create_Lagrange_polynomial(points)
    x = np.linspace(min, max, 1000)
    y = []
    for i in x:
        y.append(lagrange_polynomial(i))

    plt.plot(x, y, color='red', zorder=2, label='полином Лагранжа', linewidth=2)

    function_x_points = x
    function_y_points = []
    c = calculate_C(function, points[0][0], points[0][1])
    for i in function_x_points:
        function_y_points.append(get_derivative_of_function(function, i, c))

    function_label = "функция"
    plt.plot(function_x_points, function_y_points, '--', color='green', zorder=4, label=function_label)

    x_points = []
    y_points = []
    plt.scatter(points[0][0], points[0][1], color='purple', zorder=5, label='начальные точки')
    for i in range(1, len(points)):
        x_points.append(points[i][0])
        y_points.append(points[i][1])
    plt.scatter(x_points, y_points, color='blue', zorder=3, label='вычисленные точки')
    plt.legend(loc='lower right')
    plt.minorticks_on()
    plt.grid(which='major',
             color='k')

    plt.grid(which='minor',
             color='k',
             linestyle=':')
    plt.show()

