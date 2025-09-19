#include "instrument.h"

Instrument::Instrument(const std::string& name) : name_(name) {}

const std::string& Instrument::getName() const {
    return name_;
}