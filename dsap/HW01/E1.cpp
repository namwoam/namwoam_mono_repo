#include <iostream>
#include <string>
#include <set>

int main()
{
    std::string target;
    std::cin >> target;
    std::set<char> db;
    for (int i = 0; i < target.size(); i++)
    {
        if (db.count(target[i]) == 0)
        {
            db.insert(target[i]);
        }
    }
    std::string input;
    while (std::cin >> input)
    {
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] == target[i])
            {
                std::cout << 'G';
            }
            else if (db.count(input[i]) != 0)
            {
                std::cout << 'Y';
            }
            else
            {
                std::cout << '_';
            }
        }
        std::cout << std::endl;
    }
    return 0;
}