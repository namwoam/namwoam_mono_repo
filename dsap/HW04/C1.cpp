#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

template <typename T>
class Vector
{
public:
    // constructors
    Vector() = default;
    Vector(std::initializer_list<T> l);
    explicit Vector(size_t count);
    Vector(Vector<T> &&rhs);
    Vector(const Vector<T> &rhs);
    Vector<T> &operator=(const Vector<T> &rhs);
    Vector<T> &operator=(Vector<T> &&rhs);
    ~Vector();

    bool operator==(const Vector<T> &rhs);
    bool operator!=(const Vector<T> &rhs);

    T &operator[](size_t pos);
    const T &operator[](size_t pos) const;
    T &At(size_t pos);
    const T &At(size_t pos) const;

    T &Front();
    const T &Front() const;
    T &Back();
    const T &Back() const;

    void Resize(size_t count);

    void PushBack(const T &val);
    void PushBack(T &&val);
    void PopBack();

    void PushFront(const T &val);
    void PushFront(T &&val);
    void PopFront();

    void Insert(size_t pos, const T &val);
    void Insert(size_t pos, T &&val);
    void Erase(size_t pos);

    void Fill(const T &v);
    void Assign(size_t count, const T &val);
    void Clear();
    void Remove(const T &val);
    void Swap(Vector<T> &other);

    size_t Size() const { return size_; }

    size_t Capacity() const { return capacity_; }

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    T *elems_ = nullptr;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &v)
{
    if (v.Size() == 0)
        return os << "[]";
    os << '[' << v[0];
    for (size_t i = 1; i < v.Size(); i++)
    {
        os << ", " << v[i];
    }
    return os << ']';
}

void Test1();  // Sample1
void Test2();  // Back, Clear
void Test3();  // PushFront, PopFront
void Test4();  // Insert, Erase
void Test5();  // Remove, Fill
void Test6();  // Swap, Assign
void Test7();  // All
void Test8();  // PushFront, PopFront
void Test9();  // Insert, Erase
void Test10(); // Remove, Fill
void Test11(); // Swap, Assign
void Test12(); // All

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = {
        Test1, Test2, Test3, Test4, Test5,
        Test6, Test7, Test8, Test9, Test10,
        Test11, Test12};
    f[id - 1]();
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> l)
{
    size_ = l.size();
    capacity_ = size_;
    elems_ = new T[capacity_];

    int i = 0;
    for (const T &v : l)
    {
        elems_[i] = v;
        ++i;
    }
}

template <typename T>
Vector<T>::Vector(size_t count)
{
    size_ = count;
    capacity_ = size_;
    elems_ = new T[capacity_]{};
}

template <typename T>
Vector<T>::Vector(const Vector<T> &rhs)
{
    size_ = rhs.size_;
    capacity_ = size_;
    elems_ = new T[capacity_];

    for (size_t i = 0; i < size_; i++)
    {
        elems_[i] = rhs.elems_[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector<T> &&rhs)
{
    elems_ = rhs.elems_;
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;

    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.elems_ = nullptr;
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] elems_;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    Resize(rhs.size_);
    for (size_t i = 0; i < size_; i++)
    {
        elems_[i] = rhs.elems_[i];
    }
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&rhs)
{
    delete[] elems_;

    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    elems_ = rhs.elems_;

    rhs.capacity_ = 0;
    rhs.size_ = 0;
    rhs.elems_ = nullptr;

    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T> &rhs)
{
    if (this == &rhs)
    {
        return true;
    }
    if (size_ != rhs.size_)
    {
        return false;
    }
    for (size_t i = 0; i < size_; i++)
    {
        if (elems_[i] != rhs.elems_[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T> &rhs)
{
    return !(*this == rhs);
}

template <typename T>
void Vector<T>::Resize(size_t count)
{
    if (count <= capacity_)
    {
        for (size_t i = size_; i < count; i++)
        {
            elems_[i] = T{};
        }
        size_ = count;
        return;
    }

    capacity_ = std::max(count, 2 * (capacity_ + 1));

    T *newElems = new T[capacity_]{};
    for (size_t i = 0; i < size_; i++)
    {
        newElems[i] = elems_[i];
    }
    delete[] elems_;
    elems_ = newElems;
    size_ = count;
}

template <typename T>
void Vector<T>::PushBack(const T &val)
{
    Resize(Size() + 1);
    operator[](Size() - 1) = val;
}

template <typename T>
void Vector<T>::PushBack(T &&val)
{
    Resize(Size() + 1);
    operator[](Size() - 1) = std::move(val);
}

template <typename T>
void Vector<T>::PopBack()
{
    Resize(size_ - 1);
}

template <typename T>
T &Vector<T>::operator[](size_t pos)
{
    return elems_[pos];
}

template <typename T>
const T &Vector<T>::operator[](size_t pos) const
{
    return elems_[pos];
}

template <typename T>
T &Vector<T>::At(size_t pos)
{
    if (pos >= size_)
    {
        throw std::out_of_range{std::to_string(pos) + " >= " + std::to_string(size_)};
    }
    return elems_[pos];
}

template <typename T>
const T &Vector<T>::At(size_t pos) const
{
    return const_cast<Vector *>(this)->At(pos);
}

template <typename T>
T &Vector<T>::Front()
{
    if (size_ == 0)
    {
        throw std::out_of_range{"empty"};
    }
    return elems_[0];
}

template <typename T>
const T &Vector<T>::Front() const
{
    if (size_ == 0)
    {
        throw std::out_of_range{"empty"};
    }
    return elems_[0];
}

void Test1()
{
    // At, Front, Back
    {
        Vector<int> a = {3, 9, 1, 7, 5};
        const Vector<int> &b = a;

        std::cout << a.At(0) << std::endl;
        std::cout << a.Front() << std::endl;
        std::cout << a.Back() << std::endl;
        std::cout << b.At(0) << std::endl;
        std::cout << b.Front() << std::endl;
        std::cout << b.Back() << std::endl;

        try
        {
            std::cout << a.At(5) << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "ERROR: out_of_range: " << e.what() << std::endl;
        }

        Vector<int> c;
        try
        {
            std::cout << c.Front() << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "ERROR: out_of_range: " << e.what() << std::endl;
        }

        try
        {
            std::cout << c.Back() << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "ERROR: out_of_range: " << e.what() << std::endl;
        }
    }

    // PushFront, PopFront, PopBack
    {
        Vector<int> a;
        std::cout << a << std::endl;

        for (size_t i = 1; i <= 3; i++)
        {
            a.PushFront(i);
            std::cout << a << std::endl;
        }

        for (size_t i = 1; i <= 3; i++)
        {
            a.PopBack();
            std::cout << a << std::endl;
        }

        for (size_t i = 1; i <= 3; i++)
        {
            a.PushFront(std::move(i));
            std::cout << a << std::endl;
        }

        for (size_t i = 1; i <= 3; i++)
        {
            a.PopFront();
            std::cout << a << std::endl;
        }
    }

    Vector<int> values{0, 3, 1, 4, 1, 4, 2, 0, 5, 3};

    // Insert & Erase
    {
        Vector<int> d;
        for (size_t i = 0; i < 10; i++)
        {
            try
            {
                int k = values.At(i);
                d.Insert(k, k);
            }
            catch (const std::out_of_range &e)
            {
                std::cout << "ERROR: out_of_range: " << e.what() << std::endl;
            }
            std::cout << d << std::endl;
        }

        for (size_t i = 0; i < 10; i++)
        {
            try
            {
                d.Erase(values.At(i));
            }
            catch (const std::out_of_range &e)
            {
                std::cout << "ERROR: out_of_range: " << e.what() << std::endl;
            }
            std::cout << d << std::endl;
        }

        for (size_t i = 0; i < 10; i++)
        {
            try
            {
                int k = values.At(i);
                d.Insert(k, values[i]);
            }
            catch (const std::out_of_range &e)
            {
                std::cout << "ERROR: out_of_range: " << e.what() << std::endl;
            }
            std::cout << d << std::endl;
        }
    }

    // Remove, Fill, Clear
    {
        Vector<int> d = {3, 9, 1, 2, 9, 1, 7};

        std::cout << d << std::endl;
        d.Remove(9);
        std::cout << d << std::endl;
        d.Fill(9);
        std::cout << d << std::endl;
        d.Clear();
        std::cout << d << std::endl;

        Vector<Vector<int>> a = {{3, 9}, {0, 8}};
        std::cout << a << std::endl;
        a.Remove({3, 9});
        std::cout << a << std::endl;
    }

    // Swap
    {
        Vector<int> a = {3, 9, 1, 2};
        Vector<int> b = {7, 6, 5};

        std::cout << a << std::endl;
        std::cout << b << std::endl;
        a.Swap(b);
        std::cout << a << std::endl;
        std::cout << b << std::endl;
    }

    // Assign
    {
        Vector<int> a = {3, 9, 1, 2};
        std::cout << a << std::endl;

        a.Assign(7, 1);
        std::cout << a << std::endl;
    }
}

namespace Feis
{ /* HIDDEN */
}

void Test2()
{
    Vector<int> a = {1, 2, 3, 4, 5};
    Vector<int> b = {10, 9};
    a.Swap(b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    return;
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
void Test10()
{ /* HIDDEN */
}
void Test11()
{ /* HIDDEN */
}
void Test12()
{ /* HIDDEN */
}

#include <string>

template <typename T>
T &Vector<T>::Back()
{
    if (size_ == 0)
    {
        throw std::out_of_range("empty");
    }
    else
    {
        return elems_[size_ - 1];
    }
}

template <typename T>
const T &Vector<T>::Back() const
{
    if (size_ == 0)
    {
        throw std::out_of_range("empty");
    }
    else
    {
        return elems_[size_ - 1];
    }
}

template <typename T>
void Vector<T>::Clear()
{
    Vector<T>::Resize(0);
}

template <typename T>
void Vector<T>::PushFront(const T &val)
{
    Vector<T>::Resize(size_ + 1);
    for (int i = size_ - 1; i > 0; i--)
    {
        elems_[i] = elems_[i - 1];
    }
    elems_[0] = val;
}

template <typename T>
void Vector<T>::PushFront(T &&val)
{
    Vector<T>::Resize(size_ + 1);
    for (int i = size_ - 1; i > 0; i--)
    {
        elems_[i] = elems_[i - 1];
    }
    elems_[0] = val;
}

template <typename T>
void Vector<T>::PopFront()
{
    if (size_ == 0)
    {
        throw std::out_of_range("empty");
    }
    else
    {
        for (int i = 0; i < size_ - 1; i++)
        {
            elems_[i] = elems_[i + 1];
        }
        Vector<T>::PopBack();
    }
}

template <typename T>
void Vector<T>::Fill(const T &val)
{
    for (int i = 0; i < size_; i++)
    {
        elems_[i] = val;
    }
}

template <typename T>
void Vector<T>::Assign(size_t count, const T &val)
{
    Vector<T>::Resize(count);
    Vector<T>::Fill(val);
}

template <typename T>
void Vector<T>::Swap(Vector<T> &smallVector)
{
    std::swap(*this, smallVector);
}

template <typename T>
void Vector<T>::Insert(size_t pos, const T &val)
{
    if (pos > size_)
    {
        std::string errorMessage = std::to_string(pos) + " > " + std::to_string(size_);
        throw std::out_of_range(errorMessage);
    }
    Vector<T>::PushBack(T{});
    for (int i = size_ - 1; i > pos; i--)
    {
        elems_[i] = elems_[i - 1];
    }
    elems_[pos] = val;
}

template <typename T>
void Vector<T>::Insert(size_t pos, T &&val)
{
    if (pos > size_)
    {
        std::string errorMessage = std::to_string(pos) + " > " + std::to_string(size_);
        throw std::out_of_range(errorMessage);
    }
    Vector<T>::PushBack(T{});
    for (int i = size_ - 1; i > pos; i--)
    {
        elems_[i] = elems_[i - 1];
    }
    elems_[pos] = val;
}

template <typename T>
void Vector<T>::Erase(size_t pos)
{
    if (pos >= size_)
    {
        std::string errorMessage = std::to_string(pos) + " >= " + std::to_string(size_);
        throw std::out_of_range(errorMessage);
    }
    else
    {
        for (int i = pos; i < size_ - 1; i++)
        {
            elems_[i] = elems_[i + 1];
        }
        Vector<T>::PopBack();
    }
}

template <typename T>
void Vector<T>::Remove(const T &val)
{
    bool flag = false;
    for (int i = 0; i < size_; i++)
    {
        if (elems_[i] == val)
        {
            flag = true;
            Vector<T>::Erase(i);
            break;
        }
    }
    if (flag == true)
    {
        return Vector<T>::Remove(val);
    }
    else
    {
        return;
    }
}