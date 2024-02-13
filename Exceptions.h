#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class DuplicateNameException : public std::runtime_error {
public:
    DuplicateNameException(const std::string& name)
        : std::runtime_error("Duplicate name error: " + name) {}
};

#endif // EXCEPTIONS_H