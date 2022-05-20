#include <iostream>
#include <utility>
#include <vector>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

template<typename T>
struct IQueue {
    virtual ~IQueue() {}
    virtual bool Empty() const = 0;
    virtual void Enqueue(const T&) = 0;
    virtual T Dequeue() = 0;
    virtual const T& Peek() const = 0;
};

template<typename T>
struct ListNode {
    ListNode(T val) : val{std::move(val)}, next{nullptr} {}
    T val;
    ListNode* next;
};

template<typename T>
class LinkedQueue: public IQueue<T> {
    public:
        using ElemType = T;
        LinkedQueue();
        LinkedQueue(const LinkedQueue&);
        LinkedQueue& operator=(const LinkedQueue&);
        ~LinkedQueue();
        bool Empty() const;
        void Enqueue(const T&);
        T Dequeue();
        const T& Peek() const;
    private:
        ListNode<T>* node_;
};

template<typename T>
class ArrayQueue : public IQueue<T> {
    public:
        using ElemType = T;
        ArrayQueue();
        bool Empty() const;
        void Enqueue(const T&);
        T Dequeue();
        const T& Peek() const;
    private:
        std::vector<T> data_;
        int a_;
        int b_;
};

template<typename TQueue,
         typename = std::enable_if<
            std::is_base_of<
                IQueue<typename TQueue::ElemType>, TQueue>::value>>
std::ostream& operator<<(std::ostream& os, const TQueue& p) {
    TQueue q = p;
    bool isFirst = true;
    os << '[';
    while (!q.Empty()) {
        if (isFirst) {
            isFirst = false;
        } else {
            os << ", ";
        }
        os << q.Dequeue();
    }
    os << ']';
    return os;
}

void Test1(); // Sample1
void Test2(); // LinkedQueue
void Test3(); // LinkedQueue [Large Element]
void Test4(); // ArrayQueue
void Test5(); // ArrayQueue [Large Element]
void Test6(); // ArrayQueue and LinkedQueue

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6 };
    f[id-1]();
}

void Test1() {
    LinkedQueue<int> q1;
    std::cout << "01) " << q1 << std::endl;

    q1.Enqueue(3);
    std::cout << "02) " << q1 << std::endl;

    q1.Enqueue(5);
    std::cout << "03) " << q1 << std::endl;

    q1.Enqueue(7);
    std::cout << "04) " << q1 << std::endl;

    std::cout << "05) " << q1.Dequeue() << std::endl;

    std::cout << "06) " << q1.Peek() << std::endl;

    q1.Enqueue(9);
    std::cout << "07) " << q1 << std::endl;

    ArrayQueue<int> q2;
    std::cout << "08) " << q2 << std::endl;

    q2.Enqueue(3);
    std::cout << "09) " << q2 << std::endl;

    q2.Enqueue(5);
    std::cout << "10) " << q2 << std::endl;

    q2.Enqueue(7);
    std::cout << "11) " << q2 << std::endl;

    std::cout << "12) " << q2.Dequeue() << std::endl;

    std::cout << "13) " << q2.Peek() << std::endl;

    q2.Enqueue(9);
    std::cout << "14) " << q2 << std::endl;
}

namespace Feis {
}

void Test2() {
}
void Test3() {
}
void Test4() {
}
void Test5() {
}
void Test6() {
}

// [YOUR CODE WILL BE PLACED HERE]


