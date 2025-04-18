#include <stdio.h>

void afisare(int nr10, int nr8);

int baza8(int nr10);

int main()
{
    for (int i = 32; i <= 126; i++)
    {
        int numar = baza8(i);
        afisare(i, numar);
    }
    printf("Ai reusit!");
    return 0;
}

int baza8(int nr10)
{
    int rest, p = 1, nr8 = 0;
    while (nr10 != 0)
    {
        rest = nr10 % 8;
        nr10 /= 8;
        nr8 = rest * p + nr8;
        p = p * 10;
    }
    return nr8;
}