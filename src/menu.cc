#include "menu.h"

menu::menu(const menu_t &content) : content(content) {}

std::string menu::getContent(int highlight) {
    std::string output = "";
    for (const auto &i : content[choice]) {
        if (i.first == highlight) output += i.second.getHighlight();
        else output += i.second.getContent();
    }


}

