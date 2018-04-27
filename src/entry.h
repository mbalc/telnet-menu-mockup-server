#ifndef INC_1_ENTRY_H
#define INC_1_ENTRY_H

#include <string>
#include <functional>

class entry {
private:
    std::string content;
    std::function<void()> action;
public:
    entry(const std::string &content);
    std::string getContent() const;
    std::string getHighlight() const;
    void setAction(const std::function<void()> &action);
    void execute();
};


#endif //INC_1_ENTRY_H
