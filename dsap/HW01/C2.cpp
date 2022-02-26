#include <vector>
#include <string>
#include <iostream>
#include <sstream>

auto split(std::string str, char target)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    char ch;
    std::string currentWord;
    while (ss >> ch)
    {
        if (ch == target)
        {
            result.push_back(currentWord);
            currentWord = "";
        }
        else
        {
            currentWord += std::string(1, ch);
        }
    }
    if (result.size() != 0)
    {
        result.push_back(currentWord);
    }
    return result;
}

int convert(std::string tar)
{
    bool isNegative = false;
    std::stringstream ss(tar);
    char ch;
    int result = 0;
    while (ss >> ch)
    {
        if (ch == '-')
        {
            isNegative = true;
        }
        if (ch == '$')
        {
            int cache;
            ss >> cache;
            result += 100 * cache;
        }
        if (ch == '.')
        {
            int cache;
            ss >> cache;
            result += cache;
        }
    }
    if (isNegative == true)
    {
        result *= -1;
    }
    return result;
}

bool check(std::vector<std::string> &data)
{
    int total = 0;
    for (int i = 0; i < data.size() - 1; i++)
    {
        total += convert(data[i]);
    }
    int last = convert(data.back());
    if (total == last)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void print(std::vector<std::string> &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::string row;
    std::vector<std::vector<std::string>> data;
    while (std::getline(std::cin, row))
    {
        data.push_back(split(row, ','));
    }
    int result = 0;
    for (int i = 1; i < data.size(); i++)
    {
        if (check(data[i]) == false)
        {
            result += 1;
        }
    }
    std::cout << result << std::endl;
    return 0;
}

