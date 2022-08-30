//
// Created by mikoaj on 29.08.22.
//
#include <iostream>
#include <fstream>
#include <ctime>
#include <getopt.h>
#include <sstream>
#include <vector>

static const char *const TEST_PATH = "../testing/noteMakerTest";
static const char *const METADATA_TAG = "tags";
static const char *const METADATA_ABSOLUTE_PATH = "absolute_path";
static const char *const METADATA_TITLE = "title";
static const char *const METADATA_DATE = "created";

static struct option long_options[] = {
        /*   NAME       ARGUMENT           FLAG  SHORTNAME */
        {"name", required_argument, NULL, 'n'},
        {"tags", required_argument, NULL, 't'},
        {NULL, 0,                   NULL, 0}
};

std::vector<std::string> splitStringOnDelimeter(std::string string, std::string delimeter) {
    std::vector<std::string> words{string.size()};
    size_t pos{0};
    while ((pos = string.find(delimeter)) != std::string::npos) {
        const auto word{string.substr(0, pos)};
        words.push_back(word);
        string.erase(0, pos + delimeter.length());
    }
    return words;
}

std::string generateFileName(std::string name) {

}

std::string formatTags(std::string tags) {
    //return string looking like this [ space after TAG_ONE TAG_TWO space before ]
}

int main(int argc, char *argv[]) {
    std::time_t current = std::time(nullptr);
    int c;
    std::string name{};
    std::string fileName{};
    std::string tags{};
    int option_index = 0;
    while ((c = getopt_long(argc, argv, "n:t:",
                            long_options, &option_index)) != -1) {
        switch (c) {
            case 'n':
                printf("option n with value '%s'\n", optarg);
                name = optarg;
                fileName = generateFileName(optarg);
                break;
            case 't':
                printf("option t with value '%s'\n", optarg);
                tags = optarg;
                break;
            case '?':
                break;
            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc) {
            printf("%s ", argv[optind++]);
        }
        printf("\n");
    }
    std::ofstream note{TEST_PATH};
    note << "---\n"
         << METADATA_TITLE << ": " << "\n"
         << METADATA_TAG << ": " << "\n"
         << METADATA_DATE << ": " << std::asctime(std::localtime(&current))
         << "---\n";
    return 0;
}