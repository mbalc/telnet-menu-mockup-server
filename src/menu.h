#ifndef INC_1_SCREEN_H
#define INC_1_SCREEN_H

#include <map>
#include "entry.h"

class menu {
    using submenu_t = std::map<int, entry>;
    using menu_t = std::map<int, submenu_t>;
private:
    menu_t content;
    int highlight = 0, choice = 0;
public:
    menu(const menu_t &content);

    std::string getContent(int highlight);
};


#endif //INC_1_SCREEN_H
