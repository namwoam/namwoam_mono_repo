#include <string>
#include <iostream>
#include <vector>     // For Test
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

// Case Insensitive String
class CIString
{
    // TODO: case insensitive string comparision
    friend bool operator<(const CIString &lhs, const CIString &rhs);
    friend bool operator>(const CIString &lhs, const CIString &rhs);
    friend bool operator==(const CIString &lhs, const CIString &rhs);
    friend bool operator!=(const CIString &lhs, const CIString &rhs);

    // TODO: concatenate strings
    friend CIString operator+(const CIString &lhs, const CIString &rhs);

public:
    // copy
    CIString(const CIString &other) = default;

    // move
    CIString(CIString &&other) = default;

    // construct from C String
    CIString(const char *other) : repr_{other} {}

    // construct from C++ String (copy)
    CIString(const std::string &other) : repr_{other} {}

    // construct from C++ String (move)
    CIString(std::string &&other) : repr_{std::move(other)} {}

    // access the specified character
    char &operator[](size_t pos);
    char operator[](size_t pos) const;

    // clears the contents
    void Clear();

    // returns the number of characters
    size_t Length() const;

    // TODO: appends string to the end
    CIString &Append(const CIString &other);
    CIString &operator+=(const CIString &string);

    // TODO: appends character to the end
    CIString &Append(char ch);
    CIString &operator+=(char ch);

    // TODO: find string in the string
    size_t Find(const CIString &s, size_t start = 0) const;

    // TODO: find character in the string
    size_t Find(char ch, size_t start = 0) const;

    // TODO: returns a substring
    CIString Substr(size_t pos, size_t len) const;

    // TODO: swaps the contents
    void Swap(CIString &other);

private:
    std::string repr_;
};

std::ostream &operator<<(std::ostream &os, const CIString &s);

void Test1(); // Sample1
void Test2(); // operator==, operator!=
void Test3(); // operator<, operator>, operator+
void Test4(); // Append(char), operator+=(char), Append(const CIString&), operator+=(const CIString&)
void Test5(); // Find(const CIString&, size_t), Find(char, size_t)
void Test6(); // Substr(pos, len), Swap(other)
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

namespace Feis
{ /* HIDDEN */
}

void Test1()
{
    // Part 1. operator==, operator!=
    {
        const CIString a = "Hello!";
        const CIString b = "HELLO!";
        const CIString c = "Hello world";

        std::cout << "1.1) " << std::boolalpha << (a == b) << std::endl;
        std::cout << "1.2) " << std::boolalpha << (a != b) << std::endl;
        std::cout << "1.3) " << std::boolalpha << (a == c) << std::endl;
        std::cout << "1.4) " << std::boolalpha << (a != c) << std::endl;
    }

    // Part 2. operator<, operator>, operator+
    {
        const CIString a = "Hello!";
        const CIString b = "HELLO!";
        const CIString c = "Hello world";
        const CIString d = "world";
        const CIString e = "Hello#";
        std::cout << "2.1) " << std::boolalpha << (a > b) << std::endl;
        std::cout << "2.2) " << std::boolalpha << (a < b) << std::endl;
        std::cout << "2.3) " << std::boolalpha << (a > c) << std::endl;
        std::cout << "2.4) " << std::boolalpha << (a < c) << std::endl;
        std::cout << "2.5) " << std::boolalpha << (a > d) << std::endl;
        std::cout << "2.6) " << std::boolalpha << (a < d) << std::endl;

        std::cout << "2.7) " << (a + b) << std::endl;
        std::cout << "2.8) " << (a + " " + d) << std::endl;
    }

    // Part 3. Append(char), operator+=(char), Append(const CIString&), operator+=(const CIString&)
    {
        CIString a = "Hello!";

        std::cout << "3.1) " << a.Append('!').Append('!') << std::endl;
        std::cout << "3.2) " << a << std::endl;

        CIString b = "World";
        std::cout << "3.3) " << a.Append(b) << std::endl;
        std::cout << "3.4) " << a << std::endl;
        std::cout << "3.5) " << b << std::endl;

        CIString c = "Compile";
        std::cout << "3.6) " << (c += ' ') << std::endl;
        std::cout << "3.7) " << (c += "Error") << std::endl;
    }

    // Part 4. Find(const CIString&, size_t), Find(char, size_t)
    {
        const CIString a = "Hello world!";

        std::cout << "4.1) " << a.Find('o') << std::endl;
        std::cout << "4.2) " << a.Find('o', 6) << std::endl;
        std::cout << "4.3) " << a.Find("") << std::endl;
        std::cout << "4.4) " << a.Find("WOr") << std::endl;

        std::cout << "4.5) " << a.Find("WOrld!") << std::endl;
        std::cout << "4.6) " << a.Find("WOr", 7) << std::endl;
    }

    // Part 5. Substr(pos, len), Swap(other)
    {

        CIString a = "Hello world!";
        std::cout << "5.1) " << a.Substr(2, 3) << std::endl;
        std::cout << "5.2) " << a.Substr(1, 0) << std::endl;
        std::cout << "5.3) " << a << std::endl;

        CIString b = "Runtime Error";
        a.Swap(b);
        std::cout << "5.4) " << a << std::endl;
        std::cout << "5.5) " << b << std::endl;
    }
}

void Test2()
{
    CIString a = "abbAbc";
    CIString b = "abc";
    std::cout << "2.1) " << a.Find(b, 4) << std::endl;
}
void Test3()
{ /* HIDDEN */
}
void Test4()
{ /* HIDDEN */
}
void Test5()
{ /* HIDDEN */
}
void Test6()
{ /* HIDDEN */
}
void Test7()
{ /* HIDDEN */
}

std::ostream &operator<<(std::ostream &os, const CIString &s)
{
    for (size_t i = 0; i < s.Length(); ++i)
    {
        os << s[i];
    }
    return os;
}

char CIString::operator[](size_t pos) const
{
    return repr_[pos];
}

char &CIString::operator[](size_t pos)
{
    return repr_[pos];
}

size_t CIString::Length() const
{
    return repr_.length();
}

void CIString::Clear()
{
    repr_.clear();
}

// [YOUR CODE WILL BE PLACED HERE]

#include <algorithm>

int getCharLevel(char ch)
{
    return std::tolower(ch);
}

bool operator>(const CIString &lhs, const CIString &rhs)
{
    for (int i = 0; i < std::min(lhs.Length(), rhs.Length()); i++)
    {
        int levelA = getCharLevel(lhs[i]), levelB = getCharLevel(rhs[i]);
        // std::cout << levelA << ' ' << levelB << std::endl;
        if (levelA > levelB)
        {
            return true;
        }
        else if (levelA < levelB)
        {
            return false;
        }
    }
    if (lhs.Length() > rhs.Length())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operator<(const CIString &lhs, const CIString &rhs)
{
    return rhs > lhs;
}
bool operator==(const CIString &lhs, const CIString &rhs)
{
    if (rhs.Length() != lhs.Length())
    {
        return false;
    }
    else
    {
        if (rhs.Length() == 0 && lhs.Length() == 0)
        {
            return true;
        }
        return !((rhs > lhs) && (lhs > rhs));
    }
}
bool operator!=(const CIString &lhs, const CIString &rhs)
{
    return !(lhs == rhs);
}

CIString operator+(const CIString &lhs, const CIString &rhs)
{
    return CIString(lhs.repr_ + rhs.repr_);
}

CIString &CIString::Append(char ch)
{
    repr_.push_back(ch);
    return *this;
}

CIString &CIString::operator+=(char ch)
{
    return CIString::Append(ch);
}

CIString &CIString::Append(const CIString &other)
{
    repr_ += other.repr_;
    return *this;
}

CIString &CIString::operator+=(const CIString &other)
{
    return CIString::Append(other);
}

size_t CIString::Find(char ch, size_t start) const
{
    
    for (int i = start; i < CIString::Length(); i++)
    {
        if (getCharLevel(ch) == getCharLevel(repr_.at(i)))
        {
            return i;
        }
    }
    return CIString::Length();
}

CIString CIString::Substr(size_t pos, size_t len) const
{
    return CIString(repr_.substr(pos, len));
}

size_t CIString::Find(const CIString &s, size_t start) const
{
    if (s.Length() == 0 || CIString::Length() == 0)
    {
        return 0;
    }
    for (int i = start; i < CIString::Length() - s.Length() + 1; i++)
    {
        bool flag = true;
        // std::cout << "Start pos: " << i << std::endl;
        for (int k = 0; k < s.Length(); k++)
        {
            // std::cout << getCharLevel(repr_[i + k]) << ' ' << getCharLevel(s[k]) << std::endl;
            if (getCharLevel(repr_.at(i + k)) != getCharLevel(s.repr_.at(k)))
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            return i;
        }
    }
    return CIString::Length();
}

void CIString::Swap(CIString &other)
{
    std::swap(this->repr_, other.repr_);
}
