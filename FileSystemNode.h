#ifndef FILESYSTEMNODE_H
#define FILESYSTEMNODE_H

#include <string>
#include <memory>

class Directory; // forward declaration

enum class NodeType {
    FILE,
    DIRECTORY
};

class FileSystemNode {
public:
    FileSystemNode(const std::string& name, NodeType type);
    virtual ~FileSystemNode() = default;

    // getters
    const std::string& getName() const { return name_; }
    NodeType getType() const { return type_; }
    std::shared_ptr<Directory> getParent() const { return parent_.lock(); }

    // setters
    void setParent(std::shared_ptr<Directory> parent) { parent_ = parent; }

    // virtual methods to be overridden
    virtual size_t getSize() const = 0;
    virtual void print() const = 0;

protected:
    std::string name_;
    NodeType type_;
    std::weak_ptr<Directory> parent_; // use weak_ptr to avoid circular references
};

#endif // FILESYSTEMNODE_H
