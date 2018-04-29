#ifndef INC_1_DEFS_H
#define INC_1_DEFS_H

#include <string>

//TODO constexpr ?
namespace ansi {
    static const std::string ESC = "\33";
    static const std::string FONT_RESET = ESC + "[m";
    static const std::string FONT_BOLD = ESC + "[1m";
    static const std::string CLEAR_SCREEN = ESC + "[2J";
    static const std::string RESET_CURSOR = ESC + "[H";
    static const std::string SUPRESS_LOCAL_ECHO = ESC + "[12h";
    static const std::string ENTER = "\r\n";
}

namespace keys {
    static const std::string ESC = "\33";
    static const std::string
            ARROW_UP = ESC + "[A",
            ARROW_DOWN = ESC + "[B",
            ENTER = {char(13), char(0)};
}

namespace outs {
    static const std::string
            EMPTY = "",
            A = "A",
            B1 = "B1",
            B2 = "B2";
}

namespace tnet {
    static const std::string
            IAC{char(255)},
            SE{char(240)},
            SB{char(250)},
            WILL{char(251)},
            WONT{char(252)},
            DO{char(253)},
            DONT{char(254)};

    static const std::string
            ECHO{char(1)},
            SUPRESS_GO_AHEAD{char(3)},
            LINEMODE{char(34)},
            SUPRESS_LOCAL_ECHO{char(45)};

    static const std::string LINEMODE_MODE{char(1)};
    static const std::string LINEMODE_MODE_EDIT{char(1)};

    static const std::string DEFAULT_NEGOTIATION_MESSAGE  // TODO ensure everything's right
            = IAC + DO + LINEMODE
              + IAC + WILL + LINEMODE
              //            + IAC + SB + LINEMODE + LINEMODE_MODE + LINEMODE_MODE_EDIT + IAC + SE
              + IAC + DO + ECHO
              + IAC + WILL + ECHO
              + IAC + DO + SUPRESS_LOCAL_ECHO
              + IAC + WILL + SUPRESS_LOCAL_ECHO;
}

#endif //INC_1_DEFS_H
