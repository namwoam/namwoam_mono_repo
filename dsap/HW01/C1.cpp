#include <iostream>
#include <string>
#include <algorithm>

bool equal(std::string a, std::string b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] != b[i])
            {
                return false;
            }
        }
    }
    return true;
}

std::string add(std::string a, std::string b)
{
    std::string c = std::string(std::max(a.size(), b.size()) + 1, '0');
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    a.append(std::string(c.size() - a.size(), '0'));
    b.append(std::string(c.size() - b.size(), '0'));
    for (int i = 0; i < c.size() - 1; i++)
    {
        int aNum = a[i] - '0';
        int bNum = b[i] - '0';
        int cNum = c[i] - '0';
        int cache = aNum + bNum + cNum;
        if (cache >= 10)
        {
            c[i + 1] = '1';
            cache -= 10;
        }
        c[i] = cache + '0';
    }
    while (c.back() == '0')
    {
        c.pop_back();
    }
    std::reverse(c.begin(), c.end());
    return c;
}

std::string standardize(std::string raw, int precision)
{
    std::string digitBeforeDot;
    std::string digitAfterDot;
    bool afterDot = false;
    for (int i = 0; i < raw.size(); i++)
    {
        if (raw[i] == '.')
        {
            afterDot = true;
        }
        else
        {
            if (afterDot == false)
            {
                digitBeforeDot.push_back(raw[i]);
            }
            else
            {
                digitAfterDot.push_back(raw[i]);
            }
        }
    }
    digitAfterDot.append(precision - digitAfterDot.size(), '0');
    digitAfterDot = digitAfterDot.substr(0, precision);
    return (digitBeforeDot + digitAfterDot);
}

int main()
{
    int precision = 20;
    std::string a, b, c, d;
    while (std::cin >> a >> b >> c >> d)
    {
        a = standardize(a, precision);
        b = standardize(b, precision);
        c = standardize(c, precision);
        d = standardize(d, precision);
        std::string e = add(a, b);
        std::string f = add(e, c);
        
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
        std::cout << d << std::endl;
        std::cout << e << std::endl;
        std::cout << f << std::endl;
        
        if (equal(d, f))
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