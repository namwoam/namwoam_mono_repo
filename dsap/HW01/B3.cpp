#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

int main()
{
    std::vector<std::list<std::string>> data(101);
    int n;
    std::cin >> n;
    int score;
    std::string id;
    std::map<std::string, int> prevScore;
    while (std::cin >> score >> id)
    {
        if (prevScore.count(id) == 0)
        {
            prevScore[id] = score;
            data[score].push_back(id);
        }
        else
        {
            int prev = prevScore[id];
            if (score > prev)
            {
                data[prev].remove(id);
                data[score].push_back(id);
                prevScore[id] = score;
            }
        }
    }
    int scorePtr = 100;
    while (scorePtr >= 0 && n > 0)
    {
        if (data[scorePtr].empty() == true)
        {
            scorePtr -= 1;
        }
        else
        {
            n -= 1;
            std::string student = data[scorePtr].front();
            data[scorePtr].pop_front();
            std::cout << student << std::endl;
        }
    }
    return 0;
}