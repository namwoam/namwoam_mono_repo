#include <iostream>
#include <algorithm>
#include <vector>

void print(std::vector<long long> &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    long long n;
    std::vector<long long> data;
    while (std::cin >> n)
    {
        if (data.size() < 5)
        {
            data.push_back(n);
        }
        else
        {
            data.back() = n;
        }
        std::sort(data.begin(), data.end());
        std::reverse(data.begin(), data.end());
    }
    // print(data);
    std::cout << data[std::min(2, (int)(data.size() - 1))] << std::endl;

    return 0;
}