#pragma once

#include <string>
#include <memory>

class Instrument {
public:
    Instrument(const std::string& name);
    virtual ~Instrument() = default;

    virtual double getPrice() const = 0;  // Pure virtual method for pricing
    const std::string& getName() const;

protected:
    std::string name_;
};