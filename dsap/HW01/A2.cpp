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

void printGrade(int n)
{
    if (n >= 90)
    {
        std::cout << "A+";
    }
    else if (n >= 85)
    {
        std::cout << "A";
    }
    else if (n >= 80)
    {
        std::cout << "A-";
    }
    else if (n >= 77)
    {
        std::cout << "B+";
    }
    else if (n >= 73)
    {
        std::cout << "B";
    }
    else if (n >= 70)
    {
        std::cout << "B-";
    }
    else if (n >= 67)
    {
        std::cout << "C+";
    }
    else if (n >= 63)
    {
        std::cout << "C";
    }
    else if (n >= 60)
    {
        std::cout << "C-";
    }
    else
    {
        std::cout << "F";
    }
    return;
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
        printGrade(input);
        int finalGrade = convert(a, b, input);
        std::cout << " -> ";
        printGrade(finalGrade);
        std::cout << std::endl;
    }
    return 0;
}