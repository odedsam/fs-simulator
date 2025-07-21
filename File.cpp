#include "File.h"
#include <iostream>

File::File(const std::string& name, const std::string& content)
    : FileSystemNode(name, NodeType::FILE), content_(content) {
}

void File::print() const {
    std::cout << "File: " << name_ << " (size: " << content_.size() << " bytes)" << std::endl;
}
