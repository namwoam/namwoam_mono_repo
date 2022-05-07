#include <initializer_list>
#include <iostream>
#include <random> // For Test

template <typename T, size_t kMaximumSize = 100000>
class BoundedSizeDynamicArray
{
public:
    // constructs the bounded size dynamic array
    BoundedSizeDynamicArray() = default;
    BoundedSizeDynamicArray(std::initializer_list<T> l);

    // access specified element
    T &operator[](size_t pos);
    const T &operator[](size_t pos) const;

    // TODO: access the first element
    T &Front();
    const T &Front() const;

    // TODO: access the last element
    T &Back();
    const T &Back() const;

    // changes the number of elements stored
    void Resize(size_t n);

    // TODO: inserts an element to the beginning
    void PushFront(const T &val);

    // TODO: removes the first element
    void PopFront();

    // adds an element to the end
    void PushBack(const T &val);

    // removes the last element
    void PopBack();

    // TODO: inserts an element in the middle
    void PushMiddle(const T &val);

    // TODO: removes an element in the middle
    void PopMiddle();

    // TODO: clears the contents
    void Clear();

    // TODO: checks whether the container is empty
    bool Empty() const;

    // returns the number of elements
    size_t Size() const;

    // returns the maximum possible number of elements
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
void Test2(); // Front, Back
void Test3(); // PushFront, PopFront
void Test4(); // PushMiddle, PopMiddle
void Test5(); // Clear, Empty
void Test6(); // All
void Test7(); // PushFront, PopFront
void Test8(); // PushMiddle, PopMiddle
void Test9(); // All

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    void (*f[])() = {Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9};
    int id;
    std::cin >> id;
    f[id - 1]();
}

void Test1()
{
    BoundedSizeDynamicArray<int> a = {3, 7, 1, 5, 2};
    const BoundedSizeDynamicArray<int> b = a;

    std::cout << "a.Front():  " << a.Front() << std::endl;
    std::cout << "a.Back():   " << a.Back() << std::endl;

    std::cout << "b.Front():  " << b.Front() << std::endl;
    std::cout << "b.Back():   " << b.Back() << std::endl;

    std::cout << a << std::endl;

    for (int i = 1; i <= 5; i++)
    {
        a.PopBack();
        std::cout << a << std::endl;
    }

    for (int i = 1; i <= 5; i++)
    {
        a.PushFront(i);
        std::cout << a << std::endl;
    }

    std::cout << std::boolalpha << "a.Empty():  " << a.Empty() << std::endl;

    for (int i = 1; i <= 5; i++)
    {
        a.PopFront();
        std::cout << a << std::endl;
    }

    for (int i = 1; i <= 5; i++)
    {
        a.PushMiddle(i);
        std::cout << a << std::endl;
    }

    for (int i = 1; i <= 5; i++)
    {
        a.PopMiddle();
        std::cout << a << std::endl;
    }

    std::cout << std::boolalpha << "a.Empty():  " << a.Empty() << std::endl;

    for (int i = 1; i <= 7; i++)
    {
        a.PushBack(i * 7 % 5);
    }
    std::cout << a << std::endl;

    a.Clear();
    std::cout << a << std::endl;

    for (int i = 1; i <= 10; i++)
    {
        a.PushBack(i * 9 % 5);
    }

    std::cout << a << std::endl;
    BoundedSizeDynamicArray<int> c;
    std::cout << std::boolalpha << "c.Empty():  " << c.Empty() << std::endl;
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
T &BoundedSizeDynamicArray<T, kMaximumSize>::Front()
{
    return elems_[0];
}

template <typename T, size_t kMaximumSize>
const T &BoundedSizeDynamicArray<T, kMaximumSize>::Front() const
{
    return elems_[0];
}
template <typename T, size_t kMaximumSize>
T &BoundedSizeDynamicArray<T, kMaximumSize>::Back()
{
    return elems_[size_ - 1];
}
template <typename T, size_t kMaximumSize>
const T &BoundedSizeDynamicArray<T, kMaximumSize>::Back() const
{
    return elems_[size_ - 1];
}
template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PushFront(const T &val)
{
    BoundedSizeDynamicArray<T, kMaximumSize>::PushBack(BoundedSizeDynamicArray<T, kMaximumSize>::Back());
    for (int i = size_; i > 0; i--)
    {
        elems_[i] = elems_[i - 1];
    }
    elems_[0] = val;
}
template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PopFront()
{
    for (int i = 0; i < (int)size_ - 1; i++)
    {
        elems_[i] = elems_[i + 1];
    }
    BoundedSizeDynamicArray<T, kMaximumSize>::PopBack();
}
template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Clear()
{
    size_ = 0;
}
template <typename T, size_t kMaximumSize>
bool BoundedSizeDynamicArray<T, kMaximumSize>::Empty() const
{
    return (size_ == 0);
}
template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PushMiddle(const T &val)
{
    int ptr = (size_ + 1) / 2;
    BoundedSizeDynamicArray<T, kMaximumSize>::PushBack(BoundedSizeDynamicArray<T, kMaximumSize>::Back());
    for (int i = size_; i > ptr; i--)
    {
        elems_[i] = elems_[i - 1];
    }
    elems_[ptr] = val;
}

template <typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PopMiddle()
{
    int ptr = (size_) / 2;
    for (int i = ptr; i < size_ - 1; i++)
    {
        elems_[i] = elems_[i + 1];
    }
    BoundedSizeDynamicArray<T, kMaximumSize>::PopBack();
}
