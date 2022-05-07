#include <algorithm>
#include <ostream>
class PocketCube
{
public:
    char data[24] = {
        'W',
        'W',
        'W',
        'W',
        'O',
        'O',
        'O',
        'O',
        'G',
        'G',
        'G',
        'G',
        'R',
        'R',
        'R',
        'R',
        'B',
        'B',
        'B',
        'B',
        'Y',
        'Y',
        'Y',
        'Y',
    };
    PocketCube &RotateFront()
    {
        // face
        std::swap(data[9], data[11]);
        std::swap(data[8], data[9]);
        std::swap(data[8], data[10]);
        // ring
        std::swap(data[2], data[12]);
        std::swap(data[3], data[14]);
        std::swap(data[2], data[7]);
        std::swap(data[3], data[5]);
        std::swap(data[7], data[21]);
        std::swap(data[5], data[20]);
        return *this;
    }
    PocketCube &RotateRight()
    {
        // face
        std::swap(data[13], data[15]);
        std::swap(data[12], data[13]);
        std::swap(data[12], data[14]);
        // ring
        std::swap(data[3], data[16]);
        std::swap(data[1], data[18]);
        std::swap(data[3], data[11]);
        std::swap(data[1], data[9]);
        std::swap(data[11], data[23]);
        std::swap(data[9], data[21]);
        return *this;
    }
    PocketCube &RotateDown()
    {
        // face
        std::swap(data[21], data[23]);
        std::swap(data[20], data[21]);
        std::swap(data[20], data[22]);
        // ring
        std::swap(data[10], data[14]);
        std::swap(data[11], data[15]);
        std::swap(data[6], data[10]);
        std::swap(data[7], data[11]);
        std::swap(data[6], data[18]);
        std::swap(data[7], data[19]);
        return *this;
    }
};

std::ostream &operator<<(std::ostream &os, PocketCube &p)
{
    os << "--" << p.data[0] << p.data[1] << "----" << '\n';
    os << "--" << p.data[2] << p.data[3] << "----" << '\n';
    os << p.data[4] << p.data[5] << p.data[8] << p.data[9] << p.data[12] << p.data[13] << p.data[16] << p.data[17] << '\n';
    os << p.data[6] << p.data[7] << p.data[10] << p.data[11] << p.data[14] << p.data[15] << p.data[18] << p.data[19] << '\n';
    os << "--" << p.data[20] << p.data[21] << "----" << '\n';
    os << "--" << p.data[22] << p.data[23] << "----" << '\n';
    return os;
}

#include <iostream>
#include <random> // For Test
#include <vector> // For Test

void Test1(); // Sample1
void Test2(); // All
void Test3(); // RotateRight, RotateDown
void Test4(); // 重複其中一種旋轉
void Test5(); // 同時有多個
void Test6(); // All
void Test7(); // RotateRight, RotateDown
void Test8(); // 重複其中一種旋轉
void Test9(); // 同時有多個

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = {Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9};
    f[id - 1]();
}

void Test1()
{

    PocketCube a, b, c, d;

    std::cout << a << std::endl;

    std::cout << a.RotateFront() << std::endl;
    
    std::cout << a << std::endl;

    std::cout << b << std::endl;
    std::cout << b.RotateDown() << std::endl;
    std::cout << b << std::endl;

    std::cout << c << std::endl;
    std::cout << c.RotateRight() << std::endl;
    std::cout << c << std::endl;

    std::cout << d.RotateFront().RotateRight().RotateDown().RotateRight() << std::endl;
    std::cout << PocketCube().RotateFront().RotateFront().RotateFront().RotateFront() << std::endl;
    
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
