#ifndef NOTEUTILS_STRINGMANIPULATORS_H
#define NOTEUTILS_STRINGMANIPULATORS_H

#include <string>
#include <vector>

std::vector<std::string> wordSplitter(std::string string, const std::string &delimeter);

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

std::string strToUpper(std::string s);

std::string strToLower(std::string s);

std::string strToLowerFirstUpper(std::string s);

std::string strToUpperFirstLower(std::string s);

#endif //NOTEUTILS_STRINGMANIPULATORS_H
