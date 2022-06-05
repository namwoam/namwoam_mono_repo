#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // For Test
#include <random>    // For Test

struct IStringDatabase
{
    virtual void Add(const std::string &) = 0;
    virtual bool Remove(const std::string &) = 0;
    virtual std::vector<std::string> StartsWith(const std::string &prefix) = 0;
    virtual ~IStringDatabase() {}
};

// [YOUR CODE WILL BE PLACED HERE]
#include <set>
#include <algorithm>

class StringDatabase : public IStringDatabase
{
    void Add(const std::string &str)
    {
        data.insert(str);
    }
    bool Remove(const std::string &str)
    {
        size_t pre = data.size();
        data.erase(str);
        size_t aft = data.size();
        return pre != aft ? true : false;
    }
    std::vector<std::string> StartsWith(const std::string &prefix)
    {
        std::vector<std::string> res;
        size_t prefixPtr = 0;
        bool found = false, advance = true;
        auto dummy = data.begin();
        for (auto i = data.begin(); i != data.end(); (advance == true ? i++ : dummy++))
        {
            advance = true;
            // std::cout << "Checking: " << *i << std::endl;
            // advance = true;
            if (i->size() < prefix.size())
            {
                continue;
            }
            if (i->at(prefixPtr) == prefix.at(prefixPtr))
            {
                // std::cout << "Correct at " << prefixPtr << std::endl;
                if (prefixPtr == prefix.size() - 1)
                {
                    found = true;
                    res.push_back(*i);
                }
                else
                {
                    prefixPtr += 1;
                    advance = false;
                }
            }
            else
            {
                if (found == true || prefixPtr != 0)
                {
                    break;
                }
            }
        }
        return res;
    }

private:
    std::set<std::string> data;
};

void Test1(); // Sample1
void Test2(); // Add, StartsWith
void Test3(); // Add, StartsWith
void Test4(); // Add, StartsWith
void Test5(); // All
void Test6(); // All
void Test7(); // All

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = {Test1, Test2, Test3, Test4, Test5, Test6, Test7};
    f[id - 1]();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << '[';
    if (v.size() > 0)
    {
        os << v[0];
        for (size_t i = 1; i < v.size(); ++i)
        {
            os << ", " << v[i];
        }
    }
    return os << ']';
}

namespace Feis
{
}

void Test1()
{
    IStringDatabase &&db = StringDatabase();
    db.Add("Helloworld");
    db.Add("HelloWorld");
    db.Add("Hello");
    db.Add("Helloworld");
    db.Add("Hello");
    db.Add("Hi");

    std::cout << "01) " << db.StartsWith("Hello") << std::endl;
    std::cout << "02) " << db.StartsWith("hello") << std::endl;
    std::cout << "03) " << db.StartsWith("H") << std::endl;

    db.Remove("Helloworld");
    db.Remove("Hi");
    std::cout << "04) " << db.StartsWith("H") << std::endl;
}

void Test2() {}
void Test3() {}
void Test4() {}
void Test5() {}
void Test6() {}
void Test7() {}