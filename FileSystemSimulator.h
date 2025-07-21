#ifndef FILESYSTEM_SIMULATOR_H
#define FILESYSTEM_SIMULATOR_H

#include "Directory.h"
#include "File.h"
#include <memory>
#include <string>
#include <vector>

class FileSystemSimulator {
public:
    FileSystemSimulator();

    // command interface
    void run();

    // file system commands
    bool mkdir(const std::string& dirName);
    bool touch(const std::string& fileName);
    void ls() const;
    bool cd(const std::string& path);
    std::string pwd() const;
    bool rm(const std::string& name);

    // helper methods
    void help() const;

private:
    std::shared_ptr<Directory> root_;
    std::shared_ptr<Directory> currentDir_;

    // helper methods
    std::vector<std::string> splitPath(const std::string& path) const;
    std::shared_ptr<Directory> navigateToPath(const std::string& path) const;
    std::string getCurrentPath() const;
    bool isValidName(const std::string& name) const;
    void processCommand(const std::string& command);
    std::vector<std::string> parseCommand(const std::string& input) const;
};

#endif // FILESYSTEM_SIMULATOR_H
