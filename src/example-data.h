#ifndef INC_1_EXAMPLE_DATA_H
#define INC_1_EXAMPLE_DATA_H


#include <list>
#include "menu.h"

class exampleData : public menu {
private:
    const menu_t myData = {
            {0, {
                        {0, entry("Opcja A")},
                        {1, entry("Opcja B")},
                        {2, entry("Koniec")}
                }},
            {1, {
                        {0, entry("Opcja B1")},
                        {1, entry("Opcja B2")},
                        {2, entry("Wstecz")}
                }}
    };
public:
    exampleData(std::string &input) {
        content = myData;
        using bind_t = std::tuple<int, int, std::function<void()>>;
        bind_t actions[] = {
                {0, 0, [] {}},
                {0, 1, [&] {
                    highlight = 0;
                    submenu = 1;
                }},
                {0, 2, [&] { input = ""; }}, // input.length()==0 breaks out of main loop
                {1, 0, [] {}},
                {1, 1, [] {}},
                {1, 2, [&] {
                    highlight = 0;
                    submenu = 0;
                }}
        };
        for (bind_t &b : actions) {
            content.at(std::get<0>(b)).at(std::get<1>(b)).setAction(std::get<2>(b));
        }
    }
};


#endif //INC_1_EXAMPLE_DATA_H
