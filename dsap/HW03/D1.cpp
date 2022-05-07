#include <iostream>
#include <string>
#include <cassert>

class WordleLiteResult
{
public:
    WordleLiteResult(
        const std::string &answer,
        const std::string &guess);

    char operator[](size_t pos) const;

    constexpr size_t Size() const;

private:
    // sizeof(unsigned long) == 4 on PDOGS
    unsigned long data_;
};

class WordleLite
{
public:
    static const size_t kSize = 5;
    WordleLite(std::string ans) : ans_{ans} {}
    WordleLiteResult Guess(std::string guess) const
    {
        assert(kSize == ans_.size());
        assert(kSize == guess.size());
        return WordleLiteResult(ans_, guess);
    }

private:
    std::string ans_;
};

std::ostream &operator<<(std::ostream &os, const WordleLiteResult &res)
{
    for (size_t i = 0; i < res.Size(); ++i)
    {
        os << res[i];
    }
    return os;
}

int main()
{

    /*
    WordleLiteResult r("THOSE", "TSKOE");
    std::cout << r[0] << std::endl;     // 印出 'G'
    std::cout << r[1] << std::endl;     // 印出 'Y'
    std::cout << r[2] << std::endl;     // 印出 '_'
    std::cout << r.Size() << std::endl; // 印出 '5'
    */
    std::string answer, guess;
    std::cin >> answer;
    WordleLite w{answer};
    while (std::cin >> guess)
    {
        std::cout << w.Guess(guess) << std::endl;
    }
}

// [YOUR CODE WILL BE PLACED HERE]
WordleLiteResult::WordleLiteResult(const std::string &answer, const std::string &guess)
{
    data_ = 0;
    for (int i = 0; i < answer.size(); i++)
    {
        data_ *= 10;
        if (answer[i] == guess[i])
        {
            // G
            data_ += 1;
        }
        else if (answer.find_first_of(guess[i]) != std::string::npos)
        {
            // Y
            data_ += 2;
        }
        else
        {
            // _
            data_ += 3;
        }
    }
}

char WordleLiteResult::operator[](size_t pos) const
{
    unsigned long data = data_;
    for (int i = 0; i < WordleLiteResult::Size() - pos - 1; i++)
    {
        data /= 10;
    }
    int result = data % 10;
    if (result == 1)
    {
        return 'G';
    }
    else if (result == 2)
    {
        return 'Y';
    }
    else if (result == 3)
    {
        return '_';
    }
    else
    {
        return '$';
    }
}

constexpr size_t WordleLiteResult::Size() const
{
    return 5;
}