#include "entry.h"
#include "defs.h"
#include <utility>

entry::entry(const std::string &content) : content(content) {}

std::string entry::getContent() const {
    return content;
}

std::string entry::getHighlight() const {
    return " " + ansi::FONT_BOLD + getContent() + ansi::FONT_RESET + "  <<-";
}

void entry::execute() {
    action();
}

void entry::setAction(const std::function<void()> &action) {
    entry::action = action;
}
