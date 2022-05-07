#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>

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

std::string Evaluate(std::string &&cell);

int main()
{
    std::string line;
    while (getline(std::cin, line))
    {
        size_t begin_pos = 0;
        while (true)
        {
            size_t end_pos = line.find(',', begin_pos);
            if (begin_pos != 0)
            {
                std::cout << ",";
            }
            std::cout << Evaluate(line.substr(begin_pos, end_pos - begin_pos));
            if (end_pos == std::string::npos)
            {
                break;
            }
            begin_pos = end_pos + 1;
        }
        std::cout << std::endl;
    }
}

#include <sstream>

std::string Evaluate(std::string &&cell)
{
    if (cell[0] != '=')
    {
        return cell;
    }
    else
    {
        std::stringstream ss(cell);
        char operation;
        FixedPoint a, b;
        ss >> operation >> a >> operation >> b;
        if (operation == '+')
        {
            return (a + b).ToString();
        }
        else if (operation == '-')
        {
            return (a - b).ToString();
        }
        else if (operation == '*')
        {
            return (a * b).ToString();
        }
        else if (operation == '/')
        {
            FixedPoint zero = 0;
            if (b == zero)
            {
                return "ERROR";
            }
            else
            {
                return (a / b).ToString();
            }
        }
        else if (operation == '>')
        {
            if (a > b)
            {
                return "true";
            }
            else
            {
                return "false";
            }
        }
        else if (operation == '<')
        {
            if (a < b)
            {
                return "true";
            }
            else
            {
                return "false";
            }
        }
        else
        {
            return "Syntax_Error";
        }
    }
}