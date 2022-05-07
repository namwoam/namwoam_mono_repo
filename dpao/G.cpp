#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

std::vector<int> players(11);

struct info
{
    int owner;
    std::tuple<int, int> parent, self;
    int value;
};

auto find(std::vector<std::vector<struct info>> &data, std::tuple<int, int> ptr)
{
    if (data[std::get<0>(ptr)][std::get<1>(ptr)].parent == ptr)
    {
        return ptr;
    }
    else
    {
        auto parent = find(data, data[std::get<0>(ptr)][std::get<1>(ptr)].parent);
        data[std::get<0>(ptr)][std::get<1>(ptr)].parent = parent;
        return parent;
    }
}

void join(std::vector<std::vector<struct info>> &data, std::tuple<int, int> a, std::tuple<int, int> b)
{
    auto parentA = find(data, a);
    auto parentB = find(data, b);
    if (parentA != parentB)
    {
        if (data[std::get<0>(parentA)][std::get<1>(parentA)].value < data[std::get<0>(parentB)][std::get<1>(parentB)].value)
        {
            return join(data, b, a);
        }
        else
        {
            // A >= B
            data[std::get<0>(parentA)][std::get<1>(parentA)].value += data[std::get<0>(parentB)][std::get<1>(parentB)].value;
            data[std::get<0>(parentB)][std::get<1>(parentB)].parent = parentA;
        }
    }
}

struct chunk
{
    int owner, value;
};

bool cmp(struct chunk a, struct chunk b)
{
    if (a.value == b.value)
    {
        return players[a.owner] > players[b.owner];
    }
    return a.value > b.value;
}

int main()
{
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<struct info>> data(m, std::vector<struct info>(n));

    std::vector<struct chunk> chunkRecord;

    for (int i = 0; i < data.size(); i++)
    {
        for (int k = 0; k < data[i].size(); k++)
        {
            std::cin >> data[i][k].owner;
            data[i][k].value = 1;
            data[i][k].parent = std::make_tuple(i, k);
            data[i][k].self = std::make_tuple(i, k);
            players[data[i][k].owner] += 1;
        }
        for (int i = 0; i < data.size(); i++)
        {
            for (int k = 0; k < data[i].size(); k++)
            {
                try
                {
                    if (data.at(i).at(k - 1).owner == data.at(i).at(k).owner)
                    {
                        join(data, data.at(i).at(k - 1).self, data.at(i).at(k).self);
                    }
                }
                catch (const std::out_of_range &e)
                {
                    ;
                }
                try
                {
                    if (data.at(i).at(k + 1).owner == data.at(i).at(k).owner)
                    {
                        join(data, data.at(i).at(k + 1).self, data.at(i).at(k).self);
                    }
                }
                catch (const std::out_of_range &e)
                {
                    ;
                }
                try
                {
                    if (data.at(i - 1).at(k).owner == data.at(i).at(k).owner)
                    {
                        join(data, data.at(i - 1).at(k).self, data.at(i).at(k).self);
                    }
                }
                catch (const std::out_of_range &e)
                {
                    ;
                }
                try
                {
                    if (data.at(i + 1).at(k).owner == data.at(i).at(k).owner)
                    {
                        join(data, data.at(i + 1).at(k).self, data.at(i).at(k).self);
                    }
                }
                catch (const std::out_of_range &e)
                {
                    ;
                }
            }
        }
    }
    for (int i = 0; i < data.size(); i++)
    {
        for (int k = 0; k < data[i].size(); k++)
        {
            if (data[i][k].parent == data[i][k].self && data[i][k].owner != 1 && )
            {
                struct chunk newChunk;
                newChunk.owner = data[i][k].owner;
                newChunk.value = data[i][k].value;
                chunkRecord.push_back(newChunk);
            }
        }
    }
    std::sort(chunkRecord.begin(), chunkRecord.end(), cmp);
    for (auto el : chunkRecord)
    {
        // std::cout<<el.value<<' '<<el.owner<<std::endl;
        players[el.owner] -= el.value;
        players[1] += el.value;
        break;
    }
    for (int i = 2; i < players.size(); i++)
    {
        if (players[i] > players[1])
        {
            std::cout << -1 << std::endl;
            return 0;
        }
    }
    std::cout << players[1] << std::endl;
}