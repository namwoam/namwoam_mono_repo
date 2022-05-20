#include <string>
#include <iostream>
class ITypewriter
{
public:
    virtual ~ITypewriter() {}

    virtual void Put(char c) = 0;
    virtual void Put(const char *s) = 0;
    virtual void Put(std::string s) = 0;

    virtual std::string ToString() const = 0;
    virtual size_t Size() const = 0;

    virtual void Backspace() = 0;
    virtual void Delete() = 0;

    virtual void ToggleMode() = 0;

    virtual void Left() = 0;
    virtual void Right() = 0;

    virtual void Home() = 0;
    virtual void End() = 0;

    virtual void ClearAll() = 0;
    virtual void ClearToEndOfLine() = 0;
};

// [YOUR CODE WILL BE PLACED HERE]
#define insertMode '_'
#define replaceMode '|'

class Typewriter : public ITypewriter
{
public:
    ~Typewriter() {}

    void Put(char c)
    {
        if (currentMode == insertMode || (currentMode == replaceMode && cursorPosition == data.length() - 1))
        {
            data.insert(cursorPosition, std::string(1, c));
            cursorPosition += 1;
        }
        else
        {
            cursorPosition += 1;
            data[cursorPosition] = currentMode;
            data[cursorPosition - 1] = c;
        }
    }
    void Put(const char *s)
    {
        return Put(std::string(s));
    }
    void Put(std::string s)
    {
        if (s.length() == 0)
        {
            return;
        }
        if (currentMode == insertMode || (currentMode == replaceMode && cursorPosition == data.length() - 1))
        {
            data.insert(cursorPosition, s);
            cursorPosition += s.length();
        }
        if (currentMode == replaceMode)
        {
            data.insert(cursorPosition, s);
            cursorPosition += s.length();
            data.erase(cursorPosition + 1, s.length());
        }
    }

    std::string ToString() const
    {
        return data;
    }
    size_t Size() const
    {
        return data.size() - 1;
    }

    void Backspace()
    {
        if (cursorPosition != 0)
        {
            data.erase(cursorPosition - 1, 1);
            cursorPosition -= 1;
        }
    }
    void Delete()
    {
        if (cursorPosition != data.size() - 1)
        {
            data.erase(cursorPosition + 1, 1);
        }
    }

    void ToggleMode()
    {
        if (currentMode == insertMode)
        {
            currentMode = replaceMode;
        }
        else if (currentMode == replaceMode)
        {
            currentMode = insertMode;
        }
        data[cursorPosition] = currentMode;
    }

    void Left()
    {
        if (cursorPosition != 0)
        {
            data[cursorPosition] = data[cursorPosition - 1];
            cursorPosition -= 1;
            data[cursorPosition] = currentMode;
        }
    }
    void Right()
    {
        if (cursorPosition != data.size() - 1)
        {
            data[cursorPosition] = data[cursorPosition + 1];
            cursorPosition += 1;
            data[cursorPosition] = currentMode;
        }
    }

    void Home()
    {
        data.erase(cursorPosition, 1);
        data.insert(data.begin(), currentMode);
        cursorPosition = 0;
    }
    void End()
    {
        data.erase(cursorPosition, 1);
        data.append(std::string(1, currentMode));
        cursorPosition = data.size() - 1;
    }

    void ClearAll()
    {
        data = std::string(1, currentMode);
        cursorPosition = 0;
    }
    void ClearToEndOfLine()
    {
        data.erase(cursorPosition + 1, std::string::npos);
    }

private:
    std::string data = "_";
    char currentMode = insertMode;
    size_t cursorPosition = 0;
};

// [YOUR CODE WILL BE PLACED HERE]

#include <algorithm>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test
#include <iostream>
#include <vector>

void Test1();  // Sample1
void Test2();  // ToString, Put
void Test3();  // ToString, Put, Size
void Test4();  // ToString, Put, Size, Backspace
void Test5();  // ToString, Put, Size, Left, Right
void Test6();  // ToString, Put, Size, Left, Right, Home, End
void Test7();  // ToString, Put, Size, Left, Right, Home, Backspace, Delete
void Test8();  // ToString, Put, Size, Left, Right, Home, ClearAll, ClearToEnfOfLine
void Test9();  // ToString, Put, Size, Left, Right, Home, ToggleMode
void Test10(); // All

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = {Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10};
    f[id - 1]();
}

namespace Feis
{
}

void Test1()
{
    Typewriter t;
    ITypewriter &tw = t;

    std::cout << "01) " << tw.ToString() << std::endl;

    tw.Put('H');
    std::cout << "02) " << tw.ToString() << std::endl;

    std::cout << "03) " << tw.Size() << std::endl;

    tw.Put("ello");
    std::cout << "04) " << tw.ToString() << std::endl;

    std::cout << "05) " << tw.Size() << std::endl;

    tw.Put(std::string(" world!"));
    std::cout << "06) " << tw.ToString() << std::endl;

    std::cout << "07) " << tw.Size() << std::endl;

    tw.Backspace();
    std::cout << "08) " << tw.ToString() << std::endl;

    tw.Left();
    std::cout << "09) " << tw.ToString() << std::endl;

    for (size_t i = 1; i <= 9; ++i)
    {
        tw.Left();
    }
    std::cout << "10) " << tw.ToString() << std::endl;

    tw.ToggleMode();
    std::cout << "11) " << tw.ToString() << std::endl;

    tw.Put('a');
    std::cout << "12) " << tw.ToString() << std::endl;

    tw.Put("ppy");
    std::cout << "13) " << tw.ToString() << std::endl;

    tw.Put(std::string("!!!"));
    std::cout << "14) " << tw.ToString() << std::endl;

    tw.ClearToEndOfLine();
    std::cout << "15) " << tw.ToString() << std::endl;

    tw.Home();
    std::cout << "16) " << tw.ToString() << std::endl;

    tw.Left();
    std::cout << "17) " << tw.ToString() << std::endl;

    tw.Delete();
    std::cout << "18) " << tw.ToString() << std::endl;

    tw.ToggleMode();
    std::cout << "19) " << tw.ToString() << std::endl;

    tw.Put("Be ");
    std::cout << "20) " << tw.ToString() << std::endl;

    tw.Right();
    std::cout << "21) " << tw.ToString() << std::endl;

    tw.Delete();
    std::cout << "22) " << tw.ToString() << std::endl;

    tw.ClearAll();
    std::cout << "23) " << tw.ToString() << std::endl;

    tw.Put("Be happy");
    std::cout << "24) " << tw.ToString() << std::endl;

    tw.Home();
    std::cout << "25) " << tw.ToString() << std::endl;

    tw.End();
    std::cout << "26) " << tw.ToString() << std::endl;
}

void Test2() {}
void Test3() {}
void Test4() {}
void Test5() {}
void Test6() {}
void Test7() {}
void Test8() {}
void Test9() {}
void Test10() {}