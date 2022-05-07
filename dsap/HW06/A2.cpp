#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

template <typename TKey, typename TValue>
struct KeyValuePair
{
    TKey key;
    TValue value;
};

// 模板參數 TKey 的合理型態會支援：
// - 值初始化：歸零 (T{})
// - 複製語意：複製建構與賦值(=)
// - 同型態間的比較運算：==, !=, >, >=, <, <=
// 符合以上要求的可能型態有：int, double, std::string, ...

// 模板參數 TValue 的合理型態會支援：
// - 值初始化：歸零 (T{})
// - 複製語意：複製建構與賦值 (=)
// 符合以上要求的可能型態有：int, double, std::string, ...
template <typename TKey, typename TValue>
class Dictionary
{
public:
    Dictionary() = default;
    Dictionary(std::initializer_list<KeyValuePair<TKey, TValue>> l) : repr_{l} {}

    TValue &operator[](const TKey &key);
    TValue &operator[](TKey &&key);

    size_t Size() const { return repr_.size(); }

    // TODO: remove key from this dictionary
    void Delete(const TKey &key);

    // TODO: check whether key is existed.
    bool Contains(const TKey &key) const;

    // TODO: clear content
    void Clear();

    // TODO: swap content
    void Swap(Dictionary<TKey, TValue> &other);

    // TODO: return all keys
    std::vector<TKey> Keys() const;

    // TODO: return all values
    std::vector<TValue> Values() const;

    const std::vector<KeyValuePair<TKey, TValue>> &KeyValuePairs() const { return repr_; }

private:
    std::vector<KeyValuePair<TKey, TValue>> repr_;
};

// TODO: return a new dictionary with the merged keys and values of lhs and rhs. The values of rhs take priority when lhs and rhs share keys.
template <typename TKey, typename TValue>
Dictionary<TKey, TValue> operator|(const Dictionary<TKey, TValue> &lhs, const Dictionary<TKey, TValue> &rhs);

template <typename TKey, typename TValue>
TValue &Dictionary<TKey, TValue>::operator[](const TKey &key)
{
    for (auto p = std::begin(repr_); p != std::end(repr_); ++p)
    {
        if (p->key == key)
        {
            return p->value;
        }
    }
    repr_.push_back({key, TValue{}});
    return repr_.back().value;
}

template <typename TKey, typename TValue>
TValue &Dictionary<TKey, TValue>::operator[](TKey &&key)
{
    for (auto p = std::begin(repr_); p != std::end(repr_); ++p)
    {
        if (p->key == key)
        {
            return p->value;
        }
    }
    repr_.push_back({std::move(key), TValue{}});
    return repr_.back().value;
}

template <typename T>
std::vector<T> Sorted(std::vector<T> &&target)
{
    std::sort(std::begin(target), std::end(target));
    return std::move(target);
}

template <typename TKey, typename TValue>
std::ostream &operator<<(std::ostream &os, const KeyValuePair<TKey, TValue> &kvp)
{
    return os << kvp.key << ": " << kvp.value;
}

template <typename TKey, typename TValue>
std::ostream &operator<<(std::ostream &os, const Dictionary<TKey, TValue> &dict)
{
    os << '{';
    if (dict.Size() > 0)
    {
        auto kvps = dict.KeyValuePairs();
        std::sort(std::begin(kvps), std::end(kvps), [](const auto &a, const auto &b)
                  { return a.key < b.key; });
        os << kvps[0];
        for (size_t i = 1; i < kvps.size(); ++i)
        {
            os << ", " << kvps[i];
        }
    }
    os << '}';
    return os;
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
    os << ']';
    return os;
}

void Test1(); // Sample1
void Test2(); // Contains
void Test3(); // Delete
void Test4(); // Swap, Clear
void Test5(); // Keys, Values
void Test6(); // operator|
void Test7(); // All

int main()
{
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
    // Contains
    {
        Dictionary<std::string, int> a = {{"Mary", 100}, {"John", 50}};

        std::cout << "1.1) " << std::boolalpha << a.Contains("Mary") << std::endl;
        std::cout << "1.2) " << std::boolalpha << a.Contains("Joe") << std::endl;
    }

    // Delete
    {
        Dictionary<std::string, int> a = {{"Mary", 100}, {"John", 50}};

        std::cout << "2.1) " << a << std::endl;

        a.Delete("Mary");
        std::cout << "2.2) " << a << std::endl;

        a.Delete("Joe");
        std::cout << "2.3) " << a << std::endl;
    }

    // Clear, Swap
    {
        Dictionary<std::string, int> a = {{"Mary", 100}, {"John", 50}};
        Dictionary<std::string, int> b = {{"Joe", 60}};

        std::cout << "3.1) " << a << std::endl;
        std::cout << "3.2) " << b << std::endl;

        a.Swap(b);
        std::cout << "3.3) " << a << std::endl;
        std::cout << "3.4) " << b << std::endl;

        a.Clear();
        std::cout << "3.5) " << a << std::endl;
    }

    // Keys, Values
    {
        Dictionary<std::string, int> a = {{"Mary", 100}, {"John", 50}};
        Dictionary<std::string, int> b = {{"Joe", 60}};

        std::cout << "4.1) " << Sorted(a.Keys()) << std::endl;
        std::cout << "4.2) " << Sorted(b.Keys()) << std::endl;

        std::cout << "4.3) " << Sorted(a.Values()) << std::endl;
        std::cout << "4.4) " << Sorted(b.Values()) << std::endl;
    }

    // operator|
    {
        Dictionary<std::string, int> a = {{"Mary", 100}, {"John", 50}};
        Dictionary<std::string, int> b = {{"Joe", 60}, {"Mary", 80}};

        std::cout << "5.1) " << (a | b) << std::endl;
        std::cout << "5.2) " << (b | a) << std::endl;
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
void Test7()
{ /* HIDDEN */
}

// [YOUR CODE WILL BE PLACED HERE]
#include <algorithm>
template <typename TKey, typename TValue>
void Dictionary<TKey, TValue>::Delete(const TKey &key)
{
    for (auto i = repr_.begin(); i != repr_.end(); i++)
    {
        if (i->key == key)
        {
            repr_.erase(i);
            return;
        }
    }
}
template <typename TKey, typename TValue>
bool Dictionary<TKey, TValue>::Contains(const TKey &key) const
{
    for (auto i = repr_.begin(); i != repr_.end(); i++)
    {
        if (i->key == key)
        {
            return true;
        }
    }
    return false;
}
template <typename TKey, typename TValue>
void Dictionary<TKey, TValue>::Clear()
{
    repr_.clear();
}

template <typename TKey, typename TValue>
void Dictionary<TKey, TValue>::Swap(Dictionary<TKey, TValue> &other)
{
    std::swap(*this, other);
}
template <typename TKey, typename TValue>
std::vector<TValue> Dictionary<TKey, TValue>::Values() const
{
    std::vector<TValue> result;
    for (auto i = repr_.begin(); i != repr_.end(); i++)
    {
        result.push_back(i->value);
    }
    return result;
}

template <typename TKey, typename TValue>
std::vector<TKey> Dictionary<TKey, TValue>::Keys() const
{
    std::vector<TKey> result;
    for (auto i = repr_.begin(); i != repr_.end(); i++)
    {
        result.push_back(i->key);
    }
    return result;
}

template <typename TKey, typename TValue>
Dictionary<TKey, TValue> operator|(const Dictionary<TKey, TValue> &lhs, const Dictionary<TKey, TValue> &rhs)
{
    Dictionary<TKey, TValue> result;
    auto kvpsL = lhs.KeyValuePairs(), kvpsR = rhs.KeyValuePairs();
    for (auto i = kvpsR.begin(); i != kvpsR.end(); i++)
    {
        result[i->key] = i->value;
    }
    for (auto i = kvpsL.begin(); i != kvpsL.end(); i++)
    {
        if (!result.Contains(i->key))
        {
            result[i->key] = i->value;
        }
    }
    return result;
}
