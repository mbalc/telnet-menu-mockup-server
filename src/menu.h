#ifndef INC_1_SCREEN_H
#define INC_1_SCREEN_H

#include <map>
#include "entry.h"

class menu {
    using submenu_t = std::map<int, entry>;
    using menu_t = std::map<int, submenu_t>;
protected:
    menu_t content;
    int highlight = 0, submenu = 0;
public:
    menu() = default;

    menu(const menu_t &content);

    std::string getContent();

    void execute();

    void move(int difference);
};


#endif //INC_1_SCREEN_H
