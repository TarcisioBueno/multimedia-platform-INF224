#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class DuplicateNameException : public std::exception {
public:
    const char* what() const throw() {
        return "An object with this name already exists.";
    }
};

class ObjectNotFoundException : public std::exception {
public:
    const char* what() const throw() {
        return "The requested object was not found.";
    }
};

class InvalidClassNameException : public std::exception {
public:
    const char* what() const throw() {
        return "The provided class name is not recognized.";
    }
};

class InvalidParameterException : public std::exception {
public:
    const char* what() const throw() {
        return "The provided parameter is invalid.";
    }
};

class FileIOException : public std::exception {
public:
    const char* what() const throw() {
        return "There was an error with file input or output.";
    }
};

#endif // EXCEPTIONS_H