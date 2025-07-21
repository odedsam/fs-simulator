#ifndef FILE_H
#define FILE_H

#include "FileSystemNode.h"

class File : public FileSystemNode {
public:
    File(const std::string& name, const std::string& content = "");

    // getters
    const std::string& getContent() const { return content_; }
    size_t getSize() const override { return content_.size(); }

    // setters
    void setContent(const std::string& content) { content_ = content; }

    // override virtual methods
    void print() const override;

private:
    std::string content_;
};

#endif // FILE_H
