#define CATCH_CONFIG_MAIN

#include "catch2/catch_all.hpp"

std::string generateFileName(std::string name) {
    return "20";
}

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
                   [](unsigned char c) { return std::toupper(c); }
    );
    return s;
}

std::string strToLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); }
    );
    return s;
}

std::string strToLowerFirstUpper(std::string s) {
    std::transform(s.begin()++, s.end(), s.begin()++,
                   [](unsigned char c) { return std::tolower(c); }
    );
    *s.begin() = toupper(*s.begin());
    return s;
}
std::string strToUpperFirstLower(std::string s) {
    std::transform(s.begin()++, s.end(), s.begin()++,
                   [](unsigned char c) { return std::toupper(c); }
    );
    *s.begin() = tolower(*s.begin());
    return s;
}

TEST_CASE("Testing Word Splitter") {
    std::string title{"Some multi Worded tiTle"};
    auto DELIMETER{" "};
    std::vector<std::string> expected{{"Some"},
                                      {"multi"},
                                      {"Worded"},
                                      {"tiTle"}};
    SECTION("Word split, all words") {
        std::vector<std::string> recieved{wordSplitter(title, DELIMETER)};
        REQUIRE(expected.at(0) == recieved.at(0));
        REQUIRE(expected.at(1) == recieved.at(1));
        REQUIRE(expected.at(2) == recieved.at(2));
        REQUIRE(expected.at(3) == recieved.at(3));
    }SECTION("Word split, all words space in front") {
        std::vector<std::string> recieved{wordSplitter(" " + title, DELIMETER)};
        REQUIRE(expected.at(0) == recieved.at(0));
        REQUIRE(expected.at(1) == recieved.at(1));
        REQUIRE(expected.at(2) == recieved.at(2));
        REQUIRE(expected.at(3) == recieved.at(3));
    }SECTION("Word split, all words space behind") {
        std::vector<std::string> recieved{wordSplitter(title + " ", DELIMETER)};
        REQUIRE(expected.at(0) == recieved.at(0));
        REQUIRE(expected.at(1) == recieved.at(1));
        REQUIRE(expected.at(2) == recieved.at(2));
        REQUIRE(expected.at(3) == recieved.at(3));
    }SECTION("Word split, all words space behind and front") {
        std::vector<std::string> recieved{wordSplitter(" " + title + " ", DELIMETER)};
        REQUIRE(expected.at(0) == recieved.at(0));
        REQUIRE(expected.at(1) == recieved.at(1));
        REQUIRE(expected.at(2) == recieved.at(2));
        REQUIRE(expected.at(3) == recieved.at(3));
    }
}

TEST_CASE("Word Splitter with passed function") {
    static const std::string title{" Some multi Worded tiTle  "};
    auto DELIMETER{" "};
    SECTION("To strToUpper") {
        std::function<std::string(std::string)> func{strToUpper};
        std::vector<std::string> expected{{"SOME"},
                                          {"MULTI"},
                                          {"WORDED"},
                                          {"TITLE"}};
        std::vector<std::string> recieved{wordSplitter(" " + title + " ", DELIMETER, func)};
        REQUIRE(expected.at(0) == recieved.at(0));
        REQUIRE(expected.at(1) == recieved.at(1));
        REQUIRE(expected.at(2) == recieved.at(2));
        REQUIRE(expected.at(3) == recieved.at(3));
    }SECTION("To strToLower") {
        std::function<std::string(std::string)> func{strToLower};
        std::vector<std::string> expected{{"some"},
                                          {"multi"},
                                          {"worded"},
                                          {"title"}};
        std::vector<std::string> recieved{wordSplitter(" " + title + " ", DELIMETER, func)};
        REQUIRE(expected.at(0) == recieved.at(0));
        REQUIRE(expected.at(1) == recieved.at(1));
        REQUIRE(expected.at(2) == recieved.at(2));
        REQUIRE(expected.at(3) == recieved.at(3));
    }SECTION("To strToLowerFirstUpper") {
        std::function<std::string(std::string)> func{strToLowerFirstUpper};
        std::vector<std::string> expected{{"Some"},
                                          {"Multi"},
                                          {"Worded"},
                                          {"Title"}};
        std::vector<std::string> recieved{wordSplitter(" " + title + " ", DELIMETER, func)};
        REQUIRE(expected.at(0) == recieved.at(0));
        REQUIRE(expected.at(1) == recieved.at(1));
        REQUIRE(expected.at(2) == recieved.at(2));
        REQUIRE(expected.at(3) == recieved.at(3));
    }
    SECTION("To strToUpperFirstLower") {
        std::function<std::string(std::string)> func{strToUpperFirstLower};
        std::vector<std::string> expected{{"sOME"},
                                          {"mULTI"},
                                          {"wORDED"},
                                          {"tITLE"}};
        std::vector<std::string> recieved{wordSplitter(" " + title + " ", DELIMETER, func)};
        REQUIRE(expected.at(0) == recieved.at(0));
        REQUIRE(expected.at(1) == recieved.at(1));
        REQUIRE(expected.at(2) == recieved.at(2));
        REQUIRE(expected.at(3) == recieved.at(3));
    }
}

