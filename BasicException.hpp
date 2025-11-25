#ifndef BASICEXCEPTION_HPP
#define BASICEXCEPTION_HPP

// Very lightweight custom exception hierarchy without using any standard exception classes or std::string.
// Stores a const char* message and exposes it via what().

class BasicException {
protected:
    const char* message;
public:
    explicit BasicException(const char* msg = "BasicException") : message(msg) {}
    const char* what() const { return message; }
};

// Specialized exception types if needed later.
class SimulationException : public BasicException {
public:
    explicit SimulationException(const char* msg) : BasicException(msg) {}
};

class CapacityExceededException : public BasicException {
public:
    explicit CapacityExceededException(const char* msg) : BasicException(msg) {}
};

#endif
