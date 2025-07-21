#include "FileSystemSimulator.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

FileSystemSimulator::FileSystemSimulator() {
    root_ = std::make_shared<Directory>("root");
    currentDir_ = root_;
}

void FileSystemSimulator::run() {
    std::cout << "=== File System Simulator ===" << std::endl;
    std::cout << "Type 'help' for available commands or 'exit' to quit." << std::endl;

    std::string input;
    while (true) {
        std::cout << getCurrentPath() << " $ ";
        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input == "exit" || input == "quit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        processCommand(input);
    }
}

bool FileSystemSimulator::mkdir(const std::string& dirName) {
    if (!isValidName(dirName)) {
        std::cout << "Invalid directory name: " << dirName << std::endl;
        return false;
    }

    if (currentDir_->findChild(dirName)) {
        std::cout << "Directory '" << dirName << "' already exists" << std::endl;
        return false;
    }

    auto newDir = std::make_shared<Directory>(dirName);
    if (currentDir_->addChild(newDir)) {
        std::cout << "Directory '" << dirName << "' created" << std::endl;
        return true;
    }

    std::cout << "Failed to create directory '" << dirName << "'" << std::endl;
    return false;
}

bool FileSystemSimulator::touch(const std::string& fileName) {
    if (!isValidName(fileName)) {
        std::cout << "Invalid file name: " << fileName << std::endl;
        return false;
    }

    if (currentDir_->findChild(fileName)) {
        std::cout << "File '" << fileName << "' already exists" << std::endl;
        return false;
    }

    auto newFile = std::make_shared<File>(fileName, "");
    if (currentDir_->addChild(newFile)) {
        std::cout << "File '" << fileName << "' created" << std::endl;
        return true;
    }

    std::cout << "Failed to create file '" << fileName << "'" << std::endl;
    return false;
}

void FileSystemSimulator::ls() const {
    currentDir_->listContents();
}

bool FileSystemSimulator::cd(const std::string& path) {
    if (path == "..") {
        auto parent = currentDir_->getParent();
        if (parent) {
            currentDir_ = parent;
            return true;
        } else {
            std::cout << "Already at root directory" << std::endl;
            return false;
        }
    }

    if (path == "/" || path == "~") {
        currentDir_ = root_;
        return true;
    }

    auto targetDir = navigateToPath(path);
    if (targetDir) {
        currentDir_ = targetDir;
        return true;
    }

    std::cout << "Directory not found: " << path << std::endl;
    return false;
}

std::string FileSystemSimulator::pwd() const {
    return getCurrentPath();
}

bool FileSystemSimulator::rm(const std::string& name) {
    if (!isValidName(name)) {
        std::cout << "Invalid name: " << name << std::endl;
        return false;
    }

    auto child = currentDir_->findChild(name);
    if (!child) {
        std::cout << "File or directory not found: " << name << std::endl;
        return false;
    }

    if (currentDir_->removeChild(name)) {
        std::cout << "Removed '" << name << "'" << std::endl;
        return true;
    }

    std::cout << "Failed to remove '" << name << "'" << std::endl;
    return false;
}

void FileSystemSimulator::help() const {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  mkdir <name>  - Create a new directory" << std::endl;
    std::cout << "  touch <name>  - Create a new empty file" << std::endl;
    std::cout << "  ls            - List contents of current directory" << std::endl;
    std::cout << "  cd <path>     - Change directory (.., /, or directory name)" << std::endl;
    std::cout << "  pwd           - Print current working directory" << std::endl;
    std::cout << "  rm <name>     - Remove file or directory" << std::endl;
    std::cout << "  help          - Show this help message" << std::endl;
    std::cout << "  exit/quit     - Exit the simulator" << std::endl;
}

std::vector<std::string> FileSystemSimulator::splitPath(const std::string& path) const {
    std::vector<std::string> parts;
    std::stringstream ss(path);
    std::string part;

    while (std::getline(ss, part, '/')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }

    return parts;
}

std::shared_ptr<Directory> FileSystemSimulator::navigateToPath(const std::string& path) const {
    if (path.empty()) {
        return currentDir_;
    }

    std::shared_ptr<Directory> targetDir;

    if (path[0] == '/') {
        // absolute path
        targetDir = root_;
    } else {
        // relative path
        targetDir = currentDir_;
    }

    auto parts = splitPath(path);
    for (const auto& part : parts) {
        if (part == "..") {
            auto parent = targetDir->getParent();
            if (parent) {
                targetDir = parent;
            }
        } else {
            targetDir = targetDir->findDirectory(part);
            if (!targetDir) {
                return nullptr;
            }
        }
    }

    return targetDir;
}

std::string FileSystemSimulator::getCurrentPath() const {
    std::vector<std::string> pathParts;
    auto current = currentDir_;

    while (current && current != root_) {
        pathParts.push_back(current->getName());
        current = current->getParent();
    }

    if (pathParts.empty()) {
        return "/";
    }

    std::reverse(pathParts.begin(), pathParts.end());

    std::string path = "/";
    for (size_t i = 0; i < pathParts.size(); ++i) {
        if (i > 0) path += "/";
        path += pathParts[i];
    }

    return path;
}

bool FileSystemSimulator::isValidName(const std::string& name) const {
    if (name.empty() || name == "." || name == "..") {
        return false;
    }

    // check for invalid characters (simplified check)
    for (char c : name) {
        if (c == '/' || c == '\\' || c == ':' || c == '*' ||
            c == '?' || c == '"' || c == '<' || c == '>' || c == '|') {
            return false;
        }
    }

    return true;
}

void FileSystemSimulator::processCommand(const std::string& command) {
    auto tokens = parseCommand(command);
    if (tokens.empty()) {
        return;
    }

    std::string cmd = tokens[0];

    if (cmd == "mkdir") {
        if (tokens.size() != 2) {
            std::cout << "Usage: mkdir <directory_name>" << std::endl;
        } else {
            mkdir(tokens[1]);
        }
    } else if (cmd == "touch") {
        if (tokens.size() != 2) {
            std::cout << "Usage: touch <file_name>" << std::endl;
        } else {
            touch(tokens[1]);
        }
    } else if (cmd == "ls") {
        ls();
    } else if (cmd == "cd") {
        if (tokens.size() != 2) {
            std::cout << "Usage: cd <directory_path>" << std::endl;
        } else {
            cd(tokens[1]);
        }
    } else if (cmd == "pwd") {
        std::cout << pwd() << std::endl;
    } else if (cmd == "rm") {
        if (tokens.size() != 2) {
            std::cout << "Usage: rm <file_or_directory_name>" << std::endl;
        } else {
            rm(tokens[1]);
        }
    } else if (cmd == "help") {
        help();
    } else if (cmd.empty()) {
        // do nothing for empty commands
    } else {
        std::cout << "Unknown command: " << cmd << std::endl;
        std::cout << "Type 'help' for available commands." << std::endl;
    }
}

std::vector<std::string> FileSystemSimulator::parseCommand(const std::string& input) const {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
