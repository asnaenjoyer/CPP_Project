#pragma once
#include <string>

class Category 
{
private:
    unsigned int id;
    std::string name;

public:
    Category(unsigned int id, const std::string& name)
        : id(id), name(name) {}

    unsigned int getId() const { return id; }
    const std::string& getName() const { return name; }
};