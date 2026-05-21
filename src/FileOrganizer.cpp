#include "FileOrganizer.h"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

FileOrganizer::FileOrganizer(const std::string& directory)
    : targetDirectory(directory) {
    initializeExtensions();
}

void FileOrganizer::initializeExtensions() {
    extensionMap[".jpg"] = "Images";
    extensionMap[".png"] = "Images";
    extensionMap[".jpeg"] = "Images";

    extensionMap[".mp4"] = "Videos";
    extensionMap[".mkv"] = "Videos";

    extensionMap[".pdf"] = "PDFs";

    extensionMap[".mp3"] = "Music";

    extensionMap[".txt"] = "Documents";
    extensionMap[".docx"] = "Documents";
}

std::string FileOrganizer::getCategory(const std::string& extension) {
    if (extensionMap.find(extension) != extensionMap.end()) {
        return extensionMap[extension];
    }

    return "Others";
}

void FileOrganizer::organizeFiles() {

    try {

        for (const auto& entry : fs::directory_iterator(targetDirectory)) {

            if (entry.is_regular_file()) {

                std::string extension = entry.path().extension().string();

                std::string category = getCategory(extension);

                fs::path categoryFolder = fs::path(targetDirectory) / category;

                if (!fs::exists(categoryFolder)) {
                    fs::create_directory(categoryFolder);
                }

                fs::path destination = categoryFolder / entry.path().filename();

                int counter = 1;

                while (fs::exists(destination)) {
                    std::string newFileName =
                        entry.path().stem().string() +
                        "_" + std::to_string(counter) +
                        extension;

                    destination = categoryFolder / newFileName;
                    counter++;
                }

                fs::rename(entry.path(), destination);

                std::cout << "Moved: "
                          << entry.path().filename()
                          << " -> "
                          << category
                          << std::endl;
            }
        }
}
