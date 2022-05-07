#include <vector>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

// 模板參數 T 的合理型態會支援：
// - 值初始化：歸零
// - 複製語意：複製建構與賦值
// - 同型態間的比較運算：==, !=, >, >=, <, <=
// 符合以上要求的可能型態有：int, double, std::string, ...
template <typename T>
class Set
{
public:
    Set() = default;
    Set(std::initializer_list<T> l);
    Set(const std::vector<T> &values);

    void Add(const T &);
    void Add(T &&);
    void Remove(const T &);
    bool Contains(const T &) const;

    size_t Size() const { return repr_.size(); }
    const std::vector<T> &Values() const { return repr_; }

    // TODO: swap content
    void Swap(Set<T> &other);

    // TODO: clear content
    void Clear();

    // TODO: check whether the two sets are disjoint or not
    bool IsDisjointWith(const Set<T> &other) const;

private:
    std::vector<T> repr_;
};

template <typename T>
Set<T>::Set(std::initializer_list<T> l)
{
    for (const T &v : l)
    {
        Add(v);
    }
}

template <typename T>
Set<T>::Set(const std::vector<T> &values)
{
    for (const T &v : values)
    {
        Add(v);
    }
}

template <typename T>
void Set<T>::Add(const T &val)
{
    if (!Contains(val))
    {
        repr_.push_back(val);
    }
}

template <typename T>
void Set<T>::Add(T &&val)
{
    if (!Contains(val))
    {
        repr_.push_back(std::move(val));
    }
}

template <typename T>
void Set<T>::Remove(const T &val)
{
    auto p = std::find(std::begin(repr_), std::end(repr_), val);
    if (p != std::end(repr_))
    {
        repr_.erase(p);
    }
}

template <typename T>
bool Set<T>::Contains(const T &val) const
{
    return std::find(std::begin(repr_), std::end(repr_), val) != std::end(repr_);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Set<T> &s)
{
    std::vector<T> output(s.Values());
    std::sort(std::begin(output), std::end(output));
    os << '{';
    if (output.size() > 0)
    {
        os << output[0];
        for (size_t i = 1; i < output.size(); ++i)
        {
            os << ", " << output[i];
        }
    }
    os << '}';
    return os;
}

// TODO: checks if the contents of lhs and rhs are equal
template <typename T>
bool operator==(const Set<T> &lhs, const Set<T> &rhs);

// TODO: checks if the contents of lhs and rhs are not equal
template <typename T>
bool operator!=(const Set<T> &lhs, const Set<T> &rhs);

// TODO: check whether every element in lhs is in rhs
template <typename T>
bool operator<=(const Set<T> &lhs, const Set<T> &rhs);

// TODO: check whether every element in rhs is in lhs
template <typename T>
bool operator>=(const Set<T> &lhs, const Set<T> &rhs);

// TODO: return a new set with elements common to lhs and rhs
template <typename T>
Set<T> operator&(const Set<T> &lhs, const Set<T> &rhs);

// TODO: return a new set with elements from lhs and rhs
template <typename T>
Set<T> operator|(const Set<T> &lhs, const Set<T> &rhs);

void Test1(); // Sample1
void Test2(); // Swap, Clear
void Test3(); // operator==, operator!=
void Test4(); // operator<=, operator>=
void Test5(); // operator&, operator|, IsDisjointWith
void Test6(); // All

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = {Test1, Test2, Test3, Test4, Test5, Test6};
    f[id - 1]();
}

namespace Feis
{ /* HIDDEN */
}

void Test1()
{
    // Swap, Clear
    {
        Set<int> a = {3, 9, 5};
        Set<int> b = {3, 9, 1, 7, 5, 3};
        std::cout << "1.1)  " << a << std::endl;
        std::cout << "1.2)  " << b << std::endl;

        a.Swap(b);
        std::cout << "1.3)  " << a << std::endl;
        std::cout << "1.4)  " << b << std::endl;

        a.Clear();
        std::cout << "1.5)  " << a << std::endl;
    }

    // operator==, operator !=
    {
        Set<int> a = {1, 3};
        Set<int> b = {1, 3, 2};
        Set<int> c = {3, 1};

        std::cout << "2.1)  " << std::boolalpha << (a == a) << std::endl;
        std::cout << "2.2)  " << std::boolalpha << (a == b) << std::endl;
        std::cout << "2.3)  " << std::boolalpha << (a == c) << std::endl;
        std::cout << "2.4)  " << std::boolalpha << (a != a) << std::endl;
        std::cout << "2.5)  " << std::boolalpha << (a != b) << std::endl;
        std::cout << "2.6)  " << std::boolalpha << (a != c) << std::endl;

        Set<double> d = {1.5, 3.4};
        Set<double> e = {1.5, 3.5, 2.5};
        Set<double> f = {3.5, 1.5};

        std::cout << "2.7)  " << std::boolalpha << (d == e) << std::endl;
        std::cout << "2.8)  " << std::boolalpha << (d == f) << std::endl;
        std::cout << "2.9)  " << std::boolalpha << (d != e) << std::endl;
        std::cout << "2.10) " << std::boolalpha << (d != f) << std::endl;
    }

    // operator<=, operator>=
    {
        Set<int> a = {1, 3};
        Set<int> b = {1, 3, 2};
        Set<int> c = {3, 2};
        Set<int> g = {3, 1};

        std::cout << "3.1)  " << std::boolalpha << (a <= g) << std::endl;
        std::cout << "3.2)  " << std::boolalpha << (a >= g) << std::endl;
        std::cout << "3.3)  " << std::boolalpha << (a <= b) << std::endl;
        std::cout << "3.4)  " << std::boolalpha << (a >= b) << std::endl;
        std::cout << "3.5)  " << std::boolalpha << (a <= c) << std::endl;
        std::cout << "3.6)  " << std::boolalpha << (a >= c) << std::endl;
        std::cout << "3.7)  " << std::boolalpha << (b <= c) << std::endl;
        std::cout << "3.8)  " << std::boolalpha << (b >= c) << std::endl;

        Set<double> d = {1.5, 3.5};
        Set<double> e = {1.5, 3.5, 2.4};
        Set<double> f = {3.5, 2.5};

        std::cout << "3.9) " << std::boolalpha << (d <= e) << std::endl;
        std::cout << "3.10) " << std::boolalpha << (d >= e) << std::endl;
        std::cout << "3.11) " << std::boolalpha << (d <= f) << std::endl;
        std::cout << "3.12) " << std::boolalpha << (d >= f) << std::endl;
        std::cout << "3.13) " << std::boolalpha << (e <= f) << std::endl;
        std::cout << "3.14) " << std::boolalpha << (e >= f) << std::endl;
    }

    // operator&, operator|, IsDisjointWith
    {
        Set<int> a = {1, 3};
        Set<int> b = {1, 3, 2};
        Set<int> c = {3, 2};
        Set<int> g = {4, 5};

        std::cout << "4.1)  " << (a & a) << std::endl;
        std::cout << "4.2)  " << (a & b) << std::endl;
        std::cout << "4.3)  " << (a & c) << std::endl;
        std::cout << "4.4)  " << (a | a) << std::endl;
        std::cout << "4.5)  " << (a | b) << std::endl;
        std::cout << "4.6)  " << (a | c) << std::endl;
        std::cout << "4.7)  " << std::boolalpha << a.IsDisjointWith(b) << std::endl;
        std::cout << "4.8)  " << std::boolalpha << a.IsDisjointWith(g) << std::endl;

        Set<double> d = {1.5, 3.5};
        Set<double> e = {1.5, 3.5, 2.4};
        Set<double> f = {3.5, 2.5};
        Set<double> h = {4.5, 5.5};

        std::cout << "4.9)  " << (d & e) << std::endl;
        std::cout << "4.10) " << (d & f) << std::endl;
        std::cout << "4.11) " << (d | e) << std::endl;
        std::cout << "4.12) " << (d | f) << std::endl;
        std::cout << "4.13) " << (d | e | f) << std::endl;
        std::cout << "4.14) " << std::boolalpha << d.IsDisjointWith(e) << std::endl;
        std::cout << "4.15) " << std::boolalpha << d.IsDisjointWith(h) << std::endl;
    }
}

void Test2()
{ /* HIDDEN */
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

// [YOUR CODE WILL BE PLACED HERE]
#include <algorithm>

template <typename T>
void Set<T>::Swap(Set<T> &other)
{
    std::swap(*this, other);
    return;
}

template <typename T>
void Set<T>::Clear()
{
    repr_.clear();
}

template <typename T>
bool Set<T>::IsDisjointWith(const Set<T> &other) const
{
    for (int i = 0; i < repr_.size(); i++)
    {
        if (other.Contains(repr_.at(i)))
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator<=(const Set<T> &lhs, const Set<T> &rhs)
{
    for (int i = 0; i < lhs.Values().size(); i++)
    {
        if (!rhs.Contains(lhs.Values().at(i)))
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator>=(const Set<T> &lhs, const Set<T> &rhs)
{
    return rhs <= lhs;
}

template <typename T>
bool operator==(const Set<T> &lhs, const Set<T> &rhs)
{
    if (lhs.Size() != rhs.Size())
    {
        return false;
    }
    else
    {
        return rhs >= lhs && lhs >= rhs;
    }
}

template <typename T>
bool operator!= (const Set<T> &lhs, const Set<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
Set<T> operator&(const Set<T> &lhs, const Set<T> &rhs)
{
    Set<T> result;
    for (int i = 0; i < lhs.Values().size(); i++)
    {
        if (rhs.Contains(lhs.Values().at(i)))
        {
            result.Add(lhs.Values().at(i));
        }
    }
    return result;
}

template <typename T>
Set<T> operator|(const Set<T> &lhs, const Set<T> &rhs)
{
    Set<T> result;
    for (int i = 0; i < lhs.Values().size(); i++)
    {
        result.Add(lhs.Values().at(i));
    }
    for (int i = 0; i < rhs.Values().size(); i++)
    {
        result.Add(rhs.Values().at(i));
    }
    return result;
}
