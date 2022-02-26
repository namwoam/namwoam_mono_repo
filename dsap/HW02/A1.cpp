#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class fixedPointNumer
{
public:
    long long value = 0;
    friend std::istream &operator>>(std::istream &is, fixedPointNumer &n)
    {
        int a, b;
        char ch;
        std::string input;
        is >> input;
        std::stringstream ss(input);
        is >> a >> ch >> b;
        if (a > 0)
        {
            n.value = a * 100 + b;
        }
        else if (a < 0)
        {
            n.value = a * 100 - b;
        }
        else
        {
            n.value = (input[0] == '-' ? -b : b);
        }
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const fixedPointNumer n)
    {
        // std::cout << "real value = " << n.value << std::endl;
        if (n.value < 0)
        {
            os << '-';
        }

        long long absVal = llabs(n.value);
        os << absVal / 100 << '.';
        if (absVal % 100 < 10)
        {
            os << '0' << absVal % 100;
        }
        else
        {
            os << absVal % 100;
        }
        return os;
    }
    fixedPointNumer operator+(const fixedPointNumer n)
    {
        return fixedPointNumer(value + n.value);
    }
    fixedPointNumer operator-(const fixedPointNumer n)
    {
        return fixedPointNumer(value - n.value);
    }
    fixedPointNumer operator*(const fixedPointNumer n)
    {

        long long cache = ((value * n.value) / 10 + (value * n.value >= 0 ? 5 : -5)) / 10;
        // std::cout << cache << std::endl;
        return fixedPointNumer(cache);
    }
    fixedPointNumer operator/(const fixedPointNumer n)
    {
        double cache = (((double)(value)) / ((double)(n.value))) * 100.0;
        // std::cout << cache << std::endl;
        return fixedPointNumer(((long long)(cache + (cache >= 0 ? 0.5 : -0.5))));
    }

    fixedPointNumer(long long inputValue = 0)
    {
        value = inputValue;
    };
};

bool cmp(fixedPointNumer &a, fixedPointNumer &b, char operation)
{
    if (operation == '>')
    {
        return a.value > b.value;
    }
    else if (operation == '<')
    {
        return a.value < b.value;
    }
    else if (operation == '=')
    {
        return a.value == b.value;
    }
    else
    {
        return true;
    }
}

int main()
{
    fixedPointNumer a, b;
    char operation;
    while (std::cin >> a >> operation >> b)
    {
        fixedPointNumer c;
        if (operation == '+')
        {
            std::cout << a + b << std::endl;
        }
        else if (operation == '-')
        {
            std::cout << a - b << std::endl;
        }
        else if (operation == '>' || operation == '<')
        {
            if (cmp(a, b, operation))
            {
                std::cout << "true" << std::endl;
            }
            else
            {
                std::cout << "false" << std::endl;
            }
        }
        else if (operation == '*')
        {
            std::cout << a * b << std::endl;
        }
        else if (operation == '/')
        {
            fixedPointNumer zero;
            if (cmp(b, zero, '='))
            {
                std::cout << "ERROR" << std::endl;
            }
            else
            {
                std::cout << a / b << std::endl;
            }
        }
    }
    return 0;
}