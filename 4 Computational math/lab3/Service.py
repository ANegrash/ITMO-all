def get_float():
    try:
        number = float(input("> "))
        return number
    except:
        print("Неверный формат ввода, попробуйте ещё раз")
        return get_float()


def get_interval():
    print("Введите левую границу:")
    left_border = get_float()
    print("Введите правую границу:")
    right_border = get_float()
    return left_border, right_border


def get_sigma():
    print("Введите точность:")
    return get_float()

