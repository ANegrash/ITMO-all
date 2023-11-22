class Calculator:
    n = 0
    x = []
    system = []
    det = 0
    swap = 0

    def __init__(self, n, system):
        self.n = n
        self.system = system
        self.x = []
        self.swap = 0

    def calculate(self):
        try:
            self.__print_system()
            self.__make_triangle()
            print("\nТреугольная матрица:\n")
            self.__print_system()
            self.__get_determinate()
            self.__x_calculation()
            self.__print_x()
            self.__get_residuals()
        except ZeroDivisionError:
            print("")
            return
        except ArithmeticError:
            print("")
            return

    def __check_diagonal(self, i):
        j = i
        while j < self.n:
            if self.system[j][i] != 0 and self.system[i][j] != 0:
                swap = self.system[j]
                self.system[j] = self.system[i]
                self.system[i] = swap
                self.swap += 1
                return
            j += 1
        print("Нет решений")
        return ArithmeticError

    def __x_calculation(self):
        i = self.n - 2
        self.x.append(self.system[self.n - 1][-1]/self.system[self.n - 1][self.n - 1])
        while i > -1:
            k = self.n - 1
            value = self.system[i][-1]
            while k > i:
                value -= self.x[self.n - 1 - k] * self.system[i][k]
                k -= 1
            self.x.append(value/self.system[i][i])
            i -= 1

    def __make_triangle(self):
        try:
            i = 0
            while i < self.n:
                if self.system[i][i] == 0:
                    self.__check_diagonal(i)
                m = i
                while m < self.n - 1:
                    a = -(self.system[m + 1][i] / self.system[i][i])
                    j = i
                    while j < self.n:
                        self.system[m + 1][j] += a * self.system[i][j]
                        j += 1
                    self.system[m + 1][-1] += a * self.system[i][-1]
                    m += 1
                k = 0
                line_sum = 0
                while k < self.n:
                    line_sum += self.system[i][k]
                    k += 1
                if line_sum == 0:
                    print("Данная система уравнений несовместна, решений нет.")
                    return ArithmeticError
                i += 1
        except ValueError:
            print("Некорректные данные.")
            return

    def __print_system(self):
        i = 0
        while i < self.n:
            j = 0
            while j < self.n:
                print(str(self.system[i][j]) + " x_" + str(j) + " ", end='')
                j += 1
            print(str(self.system[i][-2]) + " " + str(self.system[i][-1]), end='')
            print("")
            i += 1

    def __print_x(self):
        i = 0
        print("\nСтолбец неизвестных:")
        self.x.reverse()
        while i < self.n:
            print("\tX_" + str(i) + ": " + str(self.x[i]))
            i += 1

    def __get_determinate(self):
        i = 0
        self.det = 1
        while i < self.n:
            self.det *= self.system[i][i]
            i += 1
        if self.swap % 2 == 1:
            self.det *= -1
        print("\nОпределитель: " + str(self.det))
        if self.det == 0:
            print("Данная система не имеет решений.")
            return ArithmeticError

    def __get_residuals(self):
        i = 0
        print("\nНевязки:")
        while i < self.n:
            res = 0
            j = 0
            while j < self.n:
                res += self.system[i][j] * self.x[j]
                j += 1
            res -= self.system[i][-1]
            i += 1
            print("\tЗначение невязки для уравнения №" + str(i) + " = " + str(abs(res)))
        print("")
