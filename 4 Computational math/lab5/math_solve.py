import functions


def create_basic_polynomial(points, i):
    def basic_polynomial(x):
        upper_part = 1
        divider_part = 1
        for j in range(len(points)):
            if j != i:
                upper_part *= (x - points[j][0])
                divider_part *= (points[i][0] - points[j][0])
        return upper_part / divider_part

    return basic_polynomial


def create_Lagrange_polynomial(points):
    basic_polynomials = []
    for i in range(len(points)):
        basic_polynomials.append(create_basic_polynomial(points, i))

    def lagrange_polynomial(x):
        result = 0
        for j in range(len(points)):
            result += points[j][1] * basic_polynomials[j](x)
        return result

    return lagrange_polynomial


def runge_kutta_solve(initial_point, function_id, h, n):
    x_current = initial_point[0]
    y_current = initial_point[1]
    points = [[x_current, y_current]]
    for i in range(1, n):
        k1 = functions.get_function(function_id, x_current, y_current)
        k2 = functions.get_function(function_id, x_current + h / 2, y_current + h * k1 / 2)
        k3 = functions.get_function(function_id, x_current + h / 2, y_current + h * k2 / 2)
        k4 = functions.get_function(function_id, x_current + h, y_current + h * k3)

        dyi = (k1 + 2 * k2 + 2 * k3 + k4) * h / 6
        x_current += h
        y_current += dyi
        points.append([x_current, y_current])

    return points
