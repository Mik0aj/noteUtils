#ifndef NOTEUTILS_STRINGMANIPULATORS_H
#define NOTEUTILS_STRINGMANIPULATORS_H

#include <string>
#include <vector>

std::vector<std::string> wordSplitter(std::string string, const std::string &delimeter);

template<typename Func>
std::vector<std::string> wordSplitter(std::string string, const std::string &delimeter, Func f);

std::string strToUpper(std::string s);

std::string strToLower(std::string s);

std::string strToLowerFirstUpper(std::string s);

std::string strToUpperFirstLower(std::string s);

#endif //NOTEUTILS_STRINGMANIPULATORS_H
