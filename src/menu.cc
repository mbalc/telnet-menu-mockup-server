#include "menu.h"

menu::menu(const menu_t &content) : content(content) {}

std::string menu::getContent() {
    std::string output;
    for (const auto &i : content[submenu]) {
        if (i.first == highlight) output += i.second.getHighlight();
        else output += i.second.getContent();
        output += '\n';
    }
}

void menu::execute() {
//    content[submenu][highlight].execute();
}

void menu::move(int difference) {
    int newCandidate = highlight + difference;
    submenu_t &currentSubmenu = content[submenu];
    newCandidate = std::min (newCandidate, currentSubmenu.rbegin()->first);  // don't exceed boundary key values
    newCandidate = std::max (newCandidate, currentSubmenu.begin()->first);
    highlight = newCandidate;
}
