#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FileSystemNode.h"
#include <vector>
#include <memory>

class File;

class Directory : public FileSystemNode, public std::enable_shared_from_this<Directory> {
public:
    Directory(const std::string& name);

    // directory operations
    bool addChild(std::shared_ptr<FileSystemNode> child);
    bool removeChild(const std::string& name);
    std::shared_ptr<FileSystemNode> findChild(const std::string& name) const;
    std::shared_ptr<Directory> findDirectory(const std::string& name) const;

    // getters
    const std::vector<std::shared_ptr<FileSystemNode>>& getChildren() const { return children_; }
    size_t getSize() const override;

    // override virtual methods
    void print() const override;

    // list directory contents
    void listContents() const;

private:
    std::vector<std::shared_ptr<FileSystemNode>> children_;
};

#endif // DIRECTORY_H
