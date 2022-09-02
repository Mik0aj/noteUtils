#include <iostream>
#include <fstream>
#include <ctime>
#include <getopt.h>
#include <numeric>
#include "src/StringManipulators.h"

static const char *const TEST_PATH = "../testing/";
static const char *const METADATA_TAG = "tags";
static const char *const METADATA_ABSOLUTE_PATH = "absolute_path";
static const char *const METADATA_TITLE = "title";
static const char *const METADATA_DATE = "created";

std::string generateFileName(std::string title) {
    auto words{wordSplitter(std::move(title), " ")};
    std::string name{};
    words.at(0) = strToLower(words.at(0));
    for (auto mIter = std::next(words.begin()); mIter != words.end(); ++mIter)
        *mIter = strToLowerFirstUpper(*mIter);
    return std::accumulate(std::next(words.begin()), words.end(), words[0]);
}

std::string formatTitle(std::string title) {
    auto words{wordSplitter(std::move(title), " ")};
    std::string name{};
    words.at(0) = strToLowerFirstUpper(words.at(0) + " ");
    for (auto mIter = std::next(words.begin()); mIter != words.end(); ++mIter)
        *mIter = strToLower(*mIter + " ");
    return std::accumulate(std::next(words.begin()), words.end(), words[0]);
}

std::string formatTags(std::string tags) {
    std::vector<std::string> words{wordSplitter(std::move(tags), " ", strToLowerFirstUpper)};
    for (auto &word: words) word + " ";
    return std::accumulate(std::next(words.begin()), words.end(), words[0]);
}

static struct option long_options[] = {
        /*   NAME       ARGUMENT           FLAG  SHORTNAME */
        {"name", required_argument, NULL, 'n'},
        {"tags", required_argument, NULL, 't'},
        {NULL, 0,                   NULL, 0}
};

int main(int argc, char *argv[]) {
    std::time_t current = std::time(nullptr);
    int c;
    std::string title{};
    std::string tags{};
    int option_index = 0;
    while ((c = getopt_long(argc, argv, "n:t:",
                            long_options, &option_index)) != -1) {
        switch (c) {
            case 'n':
                title = optarg;
                break;
            case 't':
                tags = optarg;
                break;
            case '?':
                break;
            default:
                std::cout << "?? getopt returned character code 0" << c << " ??\n";
        }
    }
    if (optind < argc) {
        std::cout << "non-option ARGV-elements: " << "\n";
        while (optind < argc) {
            std::cout << "%s " << argv[optind++] << "\n";
        }
    }
    std::ofstream note{TEST_PATH + generateFileName(title) + ".md"};
    note << "---\n"
         << METADATA_TITLE << ": " << formatTitle(title) << "\n"
         << METADATA_TAG << ": [ " << formatTags(tags) << " ]\n"
         << METADATA_DATE << ": " << std::asctime(std::localtime(&current))
         << "---\n";
    return 0;
}