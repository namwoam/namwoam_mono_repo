#include <iostream>
#include <vector>
#include <string>
#include <set>
bool validate(std::string guess, std::string result, std::string word)
{
    std::set<char> exist;
    std::set<char> notExist;
    for (int i = 0; i < result.size(); i++)
    {
        if (result[i] == '_')
        {
            if (notExist.count(guess[i]) == 0)
            {
                notExist.insert(guess[i]);
            }
        }
        else if (result[i] == 'Y')
        {
            if (guess[i] == word[i])
            {
                //std::cout << "case 1" << std::endl;
                return false;
            }
            else
            {
                if (exist.count(guess[i]) == 0)
                {
                    exist.insert(guess[i]);
                }
            }
        }
        else
        {
            if (guess[i] != word[i])
            {
                //std::cout << "case 2" << std::endl;
                return false;
            }
        }
    }
    std::set<char> withinWord;
    for (int i = 0; i < word.size(); i++)
    {
        if (withinWord.count(word[i]) == 0)
        {
            withinWord.insert(word[i]);
        }
        if (notExist.count(word[i]) != 0)
        {
            //std::cout << "case 3" << std::endl;
            return false;
        }
    }
    for (auto i = exist.begin(); i != exist.end(); i++)
    {
        if (withinWord.count(*i) == 0)
        {
            //std::cout << "case 4" << std::endl;
            return false;
        }
    }
    return true;
}

bool check(std::vector<std::string> guess, std::vector<std::string> result, std::string word)
{
    for (int i = 0; i < guess.size(); i++)
    {
        if (validate(guess[i], result[i], word) == false)
        {
            //std::cout << "Fail " << guess[i] << ' ' << result[i] << ' ' << word << std::endl;
            return false;
        }
    }
    return true;
}

int main()
{
    std::vector<std::string> guess(6);
    std::vector<std::string> result(6);
    for (int i = 0; i < guess.size(); i++)
    {
        std::cin >> guess[i];
    }
    for (int i = 0; i < result.size(); i++)
    {
        std::cin >> result[i];
    }
    std::string word;
    while (std::cin >> word)
    {
        if (check(guess, result, word) == true)
        {
            std::cout << word << std::endl;
        }
    }
    return 0;
}