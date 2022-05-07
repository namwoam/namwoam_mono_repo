#include <initializer_list>
#include <iostream>
#include <random> // For Test

template <typename T, size_t kMaximumSize = 100000>
class BoundedSizeDynamicArray
{
public:
    BoundedSizeDynamicArray() = default;
    BoundedSizeDynamicArray(std::initializer_list<T> l);

    T &operator[](size_t pos);
    const T &operator[](size_t pos) const;

    void Resize(size_t n);

    void PushBack(const T &val);
    void PopBack();

    void Fill(const T &val);
    void Erase(size_t pos);
    void Insert(size_t pos, const T &val);
    void Remove(const T &val);
    void Swap(BoundedSizeDynamicArray<T, kMaximumSize> &other);

    size_t Size() const;
    size_t Capacity() const;

private:
    size_t size_ = 0;
    T elems_[kMaximumSize];
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const BoundedSizeDynamicArray<T> &v)
{
    os << '[';
    if (v.Size() > 0)
    {
        os << v[0];
        for (size_t i = 1; i < v.Size(); i++)
        {
            os << ", " << v[i];
        }
    }
    return os << ']';
}

void Test1(); // Sample1
void Test2(); // Erase, Insert
void Test3(); // Remove, Fill
void Test4(); // Swap
void Test5(); // All
void Test6(); // Erase, Insert
void Test7(); // Remove, Fill
void Test8(); // Swap
void Test9(); // All

int main()
{
    void (*f[])() = {Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9};
    int id;
    std::cin >> id;
    f[id - 1]();
}

void Test1()
{
    BoundedSizeDynamicArray<int> a = {3, 7, 2, 1, 5};

    a.Insert(0, 9);
    std::cout << a << std::endl;

    a.Insert(6, 7);
    std::cout << a << std::endl;

    a.Insert(3, -5);
    std::cout << a << std::endl;

    a.Erase(0);
    std::cout << a << std::endl;

    a.Erase(6);
    std::cout << a << std::endl;

    a.Erase(3);
    std::cout << a << std::endl;

    a.Remove(7);
    std::cout << a << std::endl;

    a.Fill(10);
    std::cout << a << std::endl;

    BoundedSizeDynamicArray<int> c = {3, 7, 9};
    std::cout << c << std::endl;

    a.Swap(c);
    std::cout << a << std::endl;
    std::cout << c << std::endl;

    a.Swap(c);
    std::cout << a << std::endl;
    std::cout << c << std::endl;
}

void Test2()
{
    BoundedSizeDynamicArray<int> a = {5, 5, 5, 5, 5};
    a.Remove(5);
    std::cout << a << std::endl;
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
void Test8()
{ /* HIDDEN */
}
void Test9()
{ /* HIDDEN */
}

template <typename T, size_t kMaximumSize>
BoundedSizeDynamicArray<T, kMaximumSize>::BoundedSizeDynamicArray(std::initializer_list<T> l)
{
    size_ = 0;
    for (const T &e : l)
    {
        elems_[size_] = e;
        ++size_;
    }
}

template <typename T, size_t kMaximumSize>
T &BoundedSizeDynamicArray<T, kMaximumSize>::operator[](size_t pos)
{
    return elems_[pos];
}

template <typename T, size_t kMaximumSize>
const T &BoundedSizeDynamicArray<T, kMaximumSize>::operator[](size_t pos) const
{
    return elems_[pos];
}

template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Resize(size_t n)
{
    for (size_t i = size_; i < n; ++i)
    {
        elems_[i] = T{}; // Zero out the newly added element
    }
    size_ = n;
}

template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PushBack(const T &val)
{
    ++size_;
    elems_[size_ - 1] = val;
}

template <typename T, size_t kMaximumSize>
size_t BoundedSizeDynamicArray<T, kMaximumSize>::Size() const
{
    return size_;
}

template <typename T, size_t kMaximumSize>
size_t BoundedSizeDynamicArray<T, kMaximumSize>::Capacity() const
{
    return kMaximumSize;
}

template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PopBack()
{
    --size_;
}

// [YOUR CODE WILL BE PLACED HERE]

template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Fill(const T &val)
{
    for (int i = 0; i < size_; i++)
    {
        elems_[i] = val;
    }
}

template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Erase(size_t pos)
{
    for (int i = pos; i < size_; i++)
    {
        elems_[i] = elems_[i + 1];
    }
    BoundedSizeDynamicArray<T, kMaximumSize>::PopBack();
}

template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Insert(size_t pos, const T &val)
{
    BoundedSizeDynamicArray<T, kMaximumSize>::PushBack(T{});
    for (int i = size_ - 1; i > pos; i--)
    {
        elems_[i] = elems_[i - 1];
    }
    elems_[pos] = val;
}

template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Remove(const T &val)
{
    bool flag = false;
    for (int i = 0; i < size_; i++)
    {
        if (elems_[i] == val)
        {
            flag = true;
            BoundedSizeDynamicArray<T, kMaximumSize>::Erase(i);
        }
    }
    if (flag == true)
    {
        return BoundedSizeDynamicArray<T, kMaximumSize>::Remove(val);
    }
    else
    {
        return;
    }
}
template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Swap(BoundedSizeDynamicArray<T, kMaximumSize> &otherLarge)
{
    T cache = T{};
    if (size_ > otherLarge.size_)
    {
        return otherLarge.Swap((*this));
    }
    else
    {
        // std::cout << "small" << *this << std::endl;
        // std::cout << "large" << otherLarge << std::endl;
        for (int i = 0; i < size_; i++)
        {
            cache = elems_[i];
            elems_[i] = otherLarge.elems_[i];
            otherLarge.elems_[i] = cache;
        }
        int largeSize = otherLarge.size_;
        int smallSize = size_;
        for (int i = smallSize; i < largeSize; i++)
        {
            cache = otherLarge[smallSize];
            BoundedSizeDynamicArray<T, kMaximumSize>::PushBack(cache);
            otherLarge.Erase(smallSize);
        }
    }
}
