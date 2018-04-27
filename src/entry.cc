#include "entry.h"
#include <utility>

entry::entry(const std::string &content) : content(content) {}

std::string entry::getContent() const {
    return this->content;
}

std::string entry::getHighlight() const {
    return this->getContent() + "  <<--";
}

void entry::execute() {
    action();
}

void entry::setAction(const std::function<void()> &action) {
    entry::action = action;
}
