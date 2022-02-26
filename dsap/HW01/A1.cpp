#include <iostream>

int convert(double a, double b, int n)
{
    double cache = a * ((double)n) + b;
    int result = (int)(cache + 0.5);
    if (result > 100)
    {
        result = 100;
    }
    else if (result < 0)
    {
        result = 0;
    }
    return result;
}

int main()
{
    int n;
    double a, b;
    std::cin >> n >> a >> b;
    for (int i = 0; i < n; i++)
    {
        int input;
        std::cin >> input;
        std::cout << convert(a, b, input) << std::endl;
    }
    return 0;
}