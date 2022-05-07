#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <utility>
#include <set>

class FixedPoint
{
public:
    FixedPoint() : repr_{0} {}
    FixedPoint(double val)
    {
        repr_ = std::round(val * 100);
    }
    explicit FixedPoint(long long repr) : repr_{repr}
    {
    }
    std::string ToString() const
    {
        std::ostringstream out;
        out.precision(2);
        out << std::fixed << (repr_ / 100.);
        return out.str();
    }

    long long GetRepr() const
    {
        return repr_;
    }

private:
    long long repr_;
};

FixedPoint operator+(const FixedPoint &lhs, const FixedPoint &rhs)
{
    return FixedPoint{lhs.GetRepr() + rhs.GetRepr()};
}
FixedPoint operator-(const FixedPoint &lhs, FixedPoint &rhs)
{
    return FixedPoint{lhs.GetRepr() - rhs.GetRepr()};
}
FixedPoint operator*(const FixedPoint &lhs, const FixedPoint &rhs)
{
    long long repr = lhs.GetRepr() * rhs.GetRepr();
    if (repr >= 0)
    {
        return FixedPoint{(repr + 50) / 100};
    }
    return FixedPoint{(repr - 50) / 100};
}
FixedPoint operator/(const FixedPoint &lhs, const FixedPoint &rhs)
{
    long long repr = lhs.GetRepr() * 1000 / rhs.GetRepr();
    if (repr >= 0)
    {
        return FixedPoint{(repr + 5) / 10};
    }
    return FixedPoint{(repr - 5) / 10};
}
bool operator>(const FixedPoint &lhs, const FixedPoint &rhs)
{
    return lhs.GetRepr() > rhs.GetRepr();
}
bool operator<(const FixedPoint &lhs, const FixedPoint &rhs)
{
    return lhs.GetRepr() < rhs.GetRepr();
}
bool operator==(const FixedPoint &lhs, const FixedPoint &rhs)
{
    return lhs.GetRepr() == rhs.GetRepr();
}
std::ostream &operator<<(std::ostream &os, const FixedPoint &p)
{
    return os << p.ToString();
}
std::istream &operator>>(std::istream &is, FixedPoint &p)
{
    double val;
    is >> val;
    p = FixedPoint{val};
    return is;
}

#include <sstream>

void Evaluate(int a, int b, std::vector<std::vector<std::string>> &data, std::set<std::pair<int, int>> &been)
{
    if (been.count(std::make_pair(a, b)) == 0)
    {
        been.insert(std::make_pair(a, b));
    }
    else
    {
        data[a][b] = "ERROR";
        return;
    }
    // std::cout << "Evaluate: " << a << ' ' << b << std::endl;
    if (data[a][b][0] == '=')
    {
        data[a][b] = data[a][b].substr(1);
        std::stringstream ss(data[a][b]);
        char operation;
        FixedPoint l, r, fx;
        if (isalpha(ss.peek()))
        {
            char row;
            ss >> row;
            int newB = row - 'A', newA;
            ss >> newA;
            newA -= 1;
            Evaluate(newA, newB, data, been);
            if (data[newA][newB] == "ERROR" || data[newA][newB] == "true" || data[newA][newB] == "false" || data[newA][newB][0] == '#')
            {
                data[a][b] = "ERROR";
                return;
            }
            std::stringstream cell(data[newA][newB]);
            cell >> l;
        }
        else
        {
            ss >> l;
        }
        ss >> operation;
        if (isalpha(ss.peek()))
        {
            char row;
            ss >> row;
            int newB = row - 'A', newA;
            ss >> newA;
            newA -= 1;
            Evaluate(newA, newB, data, been);
            if (data[newA][newB] == "ERROR" || data[newA][newB] == "true" || data[newA][newB] == "false" || data[newA][newB][0] == '#')
            {
                data[a][b] = "ERROR";
                return;
            }
            std::stringstream cell(data[newA][newB]);
            cell >> r;
        }
        else
        {
            ss >> r;
        }

        std::string result;
        if (operation == '+')
        {
            fx = l + r;
        }
        else if (operation == '-')
        {
            fx = l - r;
        }
        else if (operation == '*')
        {
            fx = l * r;
        }
        else if (operation == '/')
        {
            FixedPoint zero = 0;
            if (r == zero)
            {
                data[a][b] = "ERROR";
                return;
            }
            else
            {
                fx = l / r;
            }
        }
        else
        {
            if (operation == '>')
            {
                if (l > r)
                {
                    result = "true";
                }
                else
                {
                    result = "false";
                }
            }
            else if (operation == '<')
            {
                if (l < r)
                {
                    result = "true";
                }
                else
                {
                    result = "false";
                }
            }
            data[a][b] = result;
            return;
        }
        if (fx > 100000.0 || fx < -100000.0)
        {
            data[a][b] = "ERROR";
        }
        else
        {
            data[a][b] = fx.ToString();
        }
        return;
    }
    else
    {
        return;
    }
}

int main()
{
    std::vector<std::vector<std::string>> data;
    std::string line;
    while (getline(std::cin, line))
    {
        data.push_back(std::vector<std::string>());
        size_t begin_pos = 0;
        while (true)
        {
            size_t end_pos = line.find(',', begin_pos);
            data.back().push_back(line.substr(begin_pos, end_pos - begin_pos));
            if (end_pos == std::string::npos)
            {
                break;
            }
            begin_pos = end_pos + 1;
        }
    }
    std::set<std::pair<int, int>> been;
    for (int i = 0; i < data.size(); i++)
    {
        for (int k = 0; k < data[i].size(); k++)
        {
            been.clear();
            Evaluate(i, k, data, been);
        }
    }
    for (int i = 0; i < data.size(); i++)
    {
        for (int k = 0; k < data[i].size(); k++)
        {
            if (data[i][k][0] == '#')
            {
                std::cout << data[i][k].substr(1);
            }
            else
            {
                std::cout << data[i][k];
            }
            if (k == data[i].size() - 1)
            {
                std::cout << std::endl;
            }
            else
            {
                std::cout << ',';
            }
        }
    }
}
