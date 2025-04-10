#include <iostream>
#include <fstream>
#include <string>

std::streampos getFileSize(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 1; 
    }

    file.seekg(0, file.end);
    std::streampos fileSize = file.tellg();
    return fileSize;
}

int getNumberOfWordsInFile(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 1; 
    }

    std::string word;
    int wordCount = 0;

    while (file >> word) {
        ++wordCount;
    }

    return wordCount;
}

int getNumberOfLines(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 1; 
    }

    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        ++count;
    }
    
    return count;
}

bool isOptionValid(std::string option)
{
    if (option.length() != 2 || option[0] != '-')
        return false;   
    return true;       
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <-l | -w | -c | -m> <filename>" << std::endl;
        return 1;
    }

    std::string arg = argv[1];
    if (argc == 2) {
        std::string filename = argv[1];
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << "\n";
            return 1;
        }

        std::cout << getNumberOfLines(filename) << " ";
        std::cout << getNumberOfWordsInFile(filename) << " ";
        std::cout << getFileSize(filename) << " ";
        std::cout << filename;
        return 0;
    } else if (argc == 3) {
        if (!isOptionValid(arg)) {
            std::cerr << "Error: Invalid option " << arg << "\n";
            return 1;
        }

        std::string filename = argv[2];
        if (arg == "-c")
            std::cout << getFileSize(filename) << " " << filename;
        else if (arg == "-w")
            std::cout << getNumberOfWordsInFile(filename) << " " << filename;
        else if (arg == "-l")
            std::cout << getNumberOfLines(filename) << " " << filename;
        else if (arg == "-m")
            std::cout << getFileSize(filename) << " " << filename;
        else {
            std::cerr << "Error: Unknown option " << arg << "\n";
            return 1;
        }
        return 0;
    }

    return 0;
}