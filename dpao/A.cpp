#include <string>
#include <iostream>
#include <set>

char mys(int c, int n)
{
    return (((((c) << ((n) % 7)) | ((c) >> (7 - ((n) % 7)))) & 127));
}

int main()
{
    std::string anchorBegin = "Ahoy!!";
    std::string anchorEnd = "!";
    std::set<int> possibleA, possibleB, possibleC, possibleD;
    std::string input;
    std::getline(std::cin, input);
    for (int i = 0; i < input.size(); i++)
    {
        
    }
}