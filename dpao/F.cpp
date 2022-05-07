#include <iostream>
#include <vector>

bool solve(std::vector<int> &data)
{
    unsigned long long sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }

}

int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int m;
        std::cin >> m;
        std::vector<int> data(m);
        for (int i = 0; i < data.size(); i++)
        {
            std::cin >> data[i];
        }
        if (solve(data) == true)
        {
            std::cout << "YES" << std ::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }
    }
}