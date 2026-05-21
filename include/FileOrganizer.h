#ifndef FILE_ORGANIZER_H
#define FILE_ORGANIZER_H

#include <string>
#include <map>

class FileOrganizer {
private:
    std::string targetDirectory;
    std::map<std::string, std::string> extensionMap;

public:
    FileOrganizer(const std::string& directory);

    void initializeExtensions();
    void organizeFiles();
    std::string getCategory(const std::string& extension);
};

#endif
