#include "FileOrganizer.h"

#include <iostream>

int main() {

    std::string folderPath;

    std::cout << "Enter folder path: ";
    std::getline(std::cin, folderPath);

    FileOrganizer organizer(folderPath);

    organizer.organizeFiles();

    return 0;
}
