#ifndef INC_1_EXAMPLE_DATA_H
#define INC_1_EXAMPLE_DATA_H


#include <list>
#include "menu.h"

class exampleData : public menu {
private:
    menu_t myData {
            {0, new submenu_t{
                    {0, new entry("Opcja A")},
                    {1, new entry("Opcja B")},
                    {2, new entry("Koniec")}
            }},
            {1, new submenu_t{
                    {0, new entry("Opcja B1")},
                    {1, new entry("Opcja B2")},
                    {2, new entry("Wstecz")}
            }}
    };
public:
    exampleData() : content(myData) {
        using bind_t = std::tuple<int, int, std::function<void()>>;
        bind_t actions[] = {
                {0, 0, []{}},
                {0, 1, []{submenu = 1;}},
                {0, 2, []{}},
                {1, 0, []{}},
                {1, 1, []{}},
                {1, 2, []{submenu = 0;}}
        };
        for (bind_t &b : actions) {
            content[b.get(0)][b.get(1)].setAction(b.get(2));
        }
    }
};


#endif //INC_1_EXAMPLE_DATA_H
