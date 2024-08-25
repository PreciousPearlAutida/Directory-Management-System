#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

void displayMainMenu();
void displayFileMenu();
void listAllFiles(const fs::path& path);
void listFilesByExtension(const fs::path& path, const std::string& ext);
void listFilesByName(const fs::path& path, const std::string& name);
void createDirectory(const fs::path& path);
void changeWorkingDirectory(fs::path& currentPath);

int main() {
    fs::path currentPath = fs::current_path();
    int choice = 0;

    while (true) {
        displayMainMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                displayFileMenu();
                int fileChoice;
                std::cin >> fileChoice;
                if (fileChoice == 1) {
                    listAllFiles(currentPath);
                } else if (fileChoice == 2) {
                    std::string ext;
                    std::cout << "Enter file extension (e.g., .txt): ";
                    std::cin >> ext;
                    listFilesByExtension(currentPath, ext);
                } else if (fileChoice == 3) {
                    std::string name;
                    std::cout << "Enter file name (e.g., file1): ";
                    std::cin >> name;
                    listFilesByName(currentPath, name);
                }
                break;
            case 2:
                createDirectory(currentPath);
                break;
            case 3:
                changeWorkingDirectory(currentPath);
                break;
            case 4:
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
        std::cout << "Press any key to continue...\n";
        std::cin.ignore();
        std::cin.get();
    }
}

void displayMainMenu() {
    std::cout << "\n          MAIN MENU         \n";
    std::cout << "-----------------------------\n";
    std::cout << "\n";
    std::cout << "1. Display List of Files\n";
    std::cout << "2. Create New Directory\n";
    std::cout << "3. Change the Working Directory\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter the Number: ";
}

void displayFileMenu() {
    std::cout << "\n      LIST FILE DETAIL     \n";
    std::cout << "-----------------------------\n";
     std::cout << "\n";
    std::cout << "1. List All Files\n";
    std::cout << "2. List Files by Extension\n";
    std::cout << "3. List Files by Name\n";
    std::cout << "Enter the Number: ";
}

void listAllFiles(const fs::path& path) {
    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename());
        }
    }
    std::cout << "\nList of All (*.*) Files:\n";
    for (const auto& file : files) {
        std::cout << file.string() << "\n";
    }
    std::cout << "\nTotal Files: " << files.size() << "\n";
}

void listFilesByExtension(const fs::path& path, const std::string& ext) {
    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ext) {
            files.push_back(entry.path().filename());
        }
    }
    std::cout << "\nList of " << ext << " Files:\n";
    for (const auto& file : files) {
        std::cout << file.string() << "\n";
    }
    std::cout << "\nTotal Files: " << files.size() << "\n";
}

void listFilesByName(const fs::path& path, const std::string& name) {
    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().filename().string().find(name) != std::string::npos) {
            files.push_back(entry.path().filename());
        }
    }
    std::cout << "\nList of Files with name containing \"" << name << "\":\n";
    for (const auto& file : files) {
        std::cout << file.string() << "\n";
    }
    std::cout << "\nTotal Files: " << files.size() << "\n";
}

void createDirectory(const fs::path& path) {
    std::string dirName;
    std::cout << "Enter the Directory name: ";
    std::cin >> dirName;
    fs::path newDir = path / dirName;
    if (fs::create_directory(newDir)) {
        std::cout << "\nNewFolder Directory Successfully Created\n";
    } else {
        std::cout << "\nDirectory Creation Failed\n";
    }
}

void changeWorkingDirectory(fs::path& currentPath) {
    int choice;
    std::cout << "\nCurrent Directory: " << currentPath << "\n";
    std::cout << "             Change Directory\n";
    std::cout << "------------------------------------------\n";
    std::cout << "\n";
    std::cout << "1. Step by Step Backward\n";
    std::cout << "2. Go to Root Directory\n";
    std::cout << "3. Forward Directory\n";
    std::cout << "Enter the Number: ";
    std::cin >> choice;
    if (choice == 1) {
        currentPath = currentPath.parent_path();
    } else if (choice == 2) {
        currentPath = currentPath.root_path();
    } else if (choice == 3) {
        std::string dirName;
        std::cout << "Please Enter the Directory Name: ";
        std::cin >> dirName;
        currentPath /= dirName;
    }
    std::cout << "\nCurrent Directory: " << currentPath << "\n";
}
