#include <iostream>
#include <cmath>
#include <limits>

int main()
{
    double a, b, c, d;
    double epsilon = 3e-6;
    while (std::cin >> a >> b >> c >> d)
    {
        double total = a + b + c;
        if (fabs(total - d) < epsilon)
        {
            std::cout << "YES" << std::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }
    }
    return 0;
}