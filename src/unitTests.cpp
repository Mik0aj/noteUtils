#include <utility>
#include "catch2/catch_all.hpp"
#include "src/StringManipulators.h"


TEST_CASE("strtoupper and lower benchmark") {
    std::string title{
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam ut mi sed tortor euismod suscipit eget vel lectus. Nunc in bibendum justo, a tempus odio. Aenean sit amet congue nibh, at accumsan leo. In a feugiat turpis, vehicula luctus arcu. Phasellus consequat bibendum magna, a congue mi auctor eu. Suspendisse faucibus nec orci sit amet ultrices. Nunc malesuada et est at pulvinar. Vestibulum eget ornare massa, nec pulvinar metus. Vestibulum ornare neque nec justo semper, commodo dapibus quam facilisis. Curabitur eu libero in erat ultricies accumsan ac in nibh. Pellentesque a pulvinar tellus. Fusce feugiat orci lorem. Proin vitae nunc.\n"
    };
    auto DELIMETER{" "};

    BENCHMARK("strToLowerFirstUpper") {
                                          std::function<std::string(std::string)> func{strToLowerFirstUpper};
                                          std::vector<std::string> recieved{
                                                  wordSplitter(" " + title + " ", DELIMETER, func)};
                                      };
    BENCHMARK("strToUpperFirstLower") {
                                          std::function<std::string(std::string)> func{strToUpperFirstLower};
                                          std::vector<std::string> recieved{
                                                  wordSplitter(" " + title + " ", DELIMETER, func)};
                                      };
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
    }SECTION("To strToUpperFirstLower") {
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

//TEST_CASE("File Name generator") {
//    static const std::string title{" Some multi Worded tiTle  "};
//    SECTION("To strToUpper") {
//        REQUIRE(generateFileName(title) == "someMultiWordedTitle");
//    }
//}

