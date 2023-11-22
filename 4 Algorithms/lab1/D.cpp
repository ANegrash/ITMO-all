#include "iostream"

int main() {
    int a, b, c, d, k;
    std::cin >> a  >> b  >> c >> d >> k;

    int checkA = a;

    for (int i = 0; i < k; ++i) {
        int middle = a*b;
        if (middle > c)
            middle -= c;
        else
            middle = 0;

        if (middle >= d)
            a = d;
        else
            a = middle;

        if (checkA == a)
            break;
        else
            checkA = a;
    }
    printf("%d", a);

    return 0;
}