#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <filesystem>
#include <set>


typedef std::multimap<std::string, std::string> FileInfo;

void splitTags(FileInfo &data) {
    const std::string delimeter{" "};
    const auto val{data.find("tags")->second};
    const auto tagsStart{val.find('[') + 1};
    const auto tagsEnd{val.find(']') - 2};
    auto tagsAsOneWord{val.substr(tagsStart, tagsEnd)};
    size_t pos{0};
    data.erase("tags");
    while ((pos = tagsAsOneWord.find(delimeter)) != std::string::npos) {
        const auto tag{tagsAsOneWord.substr(0, pos)};
        if (!tag.empty()) { data.insert({"tags", tag}); }
        tagsAsOneWord.erase(0, pos + delimeter.length());
    }
}

FileInfo metadataGetter(const std::string &pathToFile) {
    std::ifstream file(pathToFile);
    FileInfo data{};
    int metadata{0};
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            metadata += (line == "---") ? 1 : 0;
            if (metadata == 1 && line != "---") {
                const auto alloc{line.find(':')};
                const auto key = line.substr(0, alloc);
                const auto value = line.substr(alloc + 1, line.size() - alloc);
                data.insert({key, value});
            } else if (metadata == 2) {
                if (data.contains("tags")) {
                    splitTags(data);
                    data.insert({"absolute_path", pathToFile});
                }
                file.close();
                return data;
            }
        }
    }
    file.close();
    return data;
}

std::set<std::string> getUniqueTags(const std::map<std::string, FileInfo> &data) {
    std::set<std::string> uniqueTags{};
    for (auto &[key, data]: data) {
        for (auto &[key, data]: data) {
            if (key == "tags") {
                uniqueTags.insert(data);
            }
        }
    }
    return uniqueTags;
}

std::multimap<std::string, FileInfo> mapFilesToTags(const std::map<std::string, FileInfo> &filesInfo) {
    std::multimap<std::string, FileInfo> filesBelongingToTag{};
    for (const auto &[name, fileInfo]: filesInfo) {
        auto range{fileInfo.equal_range("tags")};
        for (auto i = range.first; i != range.second; ++i) {
            filesBelongingToTag.insert({i->second, fileInfo});
        }
    }
    return filesBelongingToTag;
}

int main(int argc, char *argv[]) {
    std::string pathToFolder{argv[1]};
    std::ofstream readme{pathToFolder + "README.md"};
    std::ofstream tags{pathToFolder + ".metadata/tags.md"};
    std::ifstream intro(pathToFolder + ".metadata/intro");
    std::ifstream outro(pathToFolder + ".metadata/outro");

    std::map<std::string, FileInfo> filesInfo{};
    for (const auto &entry: std::filesystem::recursive_directory_iterator(pathToFolder)) {
        const auto pathEnding{entry.path().string()};
        if (pathEnding.rfind(".md") != std::string::npos) {
            const auto metadata = metadataGetter(pathEnding);
            if (!metadata.empty()) {
                filesInfo.insert({pathEnding, metadata});
            }
        }
    }
    for (std::string line; getline(intro, line);) {
        readme << line << '\n';
    }
    for (auto &tag: getUniqueTags(filesInfo)) {
        readme << "* " << "[" << tag << "](.metadata/tags.md#" << tag << ")" << std::endl;
    }
    const auto tagAndFiles{mapFilesToTags(filesInfo)};
    for (const auto &tag: getUniqueTags(filesInfo)) {
        auto ret{tagAndFiles.equal_range(tag)};
        tags << "#### " << tag << "\n";
        for (auto it = ret.first; it != ret.second; ++it) {
            auto title{it->second.find("title")};
            auto relativePath{it->second.find("absolute_path")->second};
            tags << "* " << "[" << title->second << "](../"
                 << relativePath.substr(pathToFolder.size(), relativePath.size() - pathToFolder.size()) << "#top)"
                 << std::endl;
        }
    }
    for (std::string line; getline(outro, line);) {
        readme << line << '\n';
    }

//    for (auto [tag, fileInfo]: mapFilesToTags(filesInfo)) {
//        if(fileInfo.find("title")!=fileInfo.end()){
//            std::cout << tag << ' ' << fileInfo.find("title")->second << std::endl;
//        }
//    }
    intro.close();
    outro.close();
    return 0;
}
