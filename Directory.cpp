#include "Directory.h"
#include "File.h"
#include <iostream>
#include <algorithm>

Directory::Directory(const std::string& name)
    : FileSystemNode(name, NodeType::DIRECTORY) {
}

bool Directory::addChild(std::shared_ptr<FileSystemNode> child) {
    if (!child) {
        return false;
    }

    // check if child with same name already exists
    if (findChild(child->getName())) {
        return false;
    }

    // set parent relationship
    if (child->getType() == NodeType::DIRECTORY) {
        auto dir = std::static_pointer_cast<Directory>(child);
        dir->setParent(shared_from_this());
    } else {
        child->setParent(shared_from_this());
    }

    children_.push_back(child);
    return true;
}

bool Directory::removeChild(const std::string& name) {
    auto it = std::find_if(children_.begin(), children_.end(),
        [&name](const std::shared_ptr<FileSystemNode>& node) {
            return node->getName() == name;
        });

    if (it != children_.end()) {
        children_.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<FileSystemNode> Directory::findChild(const std::string& name) const {
    auto it = std::find_if(children_.begin(), children_.end(),
        [&name](const std::shared_ptr<FileSystemNode>& node) {
            return node->getName() == name;
        });

    return (it != children_.end()) ? *it : nullptr;
}

std::shared_ptr<Directory> Directory::findDirectory(const std::string& name) const {
    auto child = findChild(name);
    if (child && child->getType() == NodeType::DIRECTORY) {
        return std::static_pointer_cast<Directory>(child);
    }
    return nullptr;
}

size_t Directory::getSize() const {
    size_t totalSize = 0;
    for (const auto& child : children_) {
        totalSize += child->getSize();
    }
    return totalSize;
}

void Directory::print() const {
    std::cout << "Directory: " << name_ << " (" << children_.size()
              << " items, total size: " << getSize() << " bytes)" << std::endl;
}

void Directory::listContents() const {
    if (children_.empty()) {
        std::cout << "Directory is empty" << std::endl;
        return;
    }

    for (const auto& child : children_) {
        if (child->getType() == NodeType::DIRECTORY) {
            std::cout << "[DIR]  " << child->getName() << std::endl;
        } else {
            std::cout << "[FILE] " << child->getName() << " (" << child->getSize() << " bytes)" << std::endl;
        }
    }
}
