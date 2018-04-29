#include "menu.h"

menu::menu(const menu_t &content) : content(content) {}

std::string menu::getContent() {
    std::string output;
    for (const auto &i : content[submenu]) {
        if (i.first == highlight) output += i.second.getHighlight();
        else output += i.second.getContent();
    }
}
