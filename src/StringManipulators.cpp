#include "src/StringManipulators.h"


std::vector<std::string> wordSplitter(std::string string, const std::string &delimeter) {
    std::vector<std::string> words{};
    size_t pos{0};
    auto start = string.find_first_not_of(delimeter);
    auto finish = string.find_last_not_of(delimeter) + delimeter.length();
    string = string.substr(start, finish - start) + delimeter;
    while ((pos = string.find(delimeter)) != std::string::npos) {
        const auto word{string.substr(0, pos)};
        words.push_back(word);
        string.erase(0, pos + delimeter.length());
    }
    return words;
}

template<typename Func>
std::vector<std::string> wordSplitter(std::string string, const std::string &delimeter, Func f) {
    std::vector<std::string> words{};
    size_t pos{0};
    auto start = string.find_first_not_of(delimeter);
    auto finish = string.find_last_not_of(delimeter) + delimeter.length();
    string = string.substr(start, finish - start) + delimeter;
    while ((pos = string.find(delimeter)) != std::string::npos) {
        const auto word{string.substr(0, pos)};
        words.push_back(f(word));
        string.erase(0, pos + delimeter.length());
    }
    return words;
}

std::string strToUpper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return toupper(c); }
    );
    return s;
}

std::string strToLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return tolower(c); }
    );
    return s;
}

std::string strToLowerFirstUpper(std::string s) {
    auto first{true};
    std::transform(s.begin(), s.end(), s.begin(),
                   [first](unsigned char c) mutable {
                       auto val{(first) ? toupper(c) : tolower(c)};

                       first = false;
                       return val;
                   }
    );
    return s;
}

std::string strToUpperFirstLower(std::string s) {
    auto first{true};
    std::transform(s.begin(), s.end(), s.begin(),
                   [first](unsigned char c)mutable {
                       auto val{(first) ? tolower(c) : toupper(c)};
                       first = false;
                       return val;
                   }
    );
    return s;
}