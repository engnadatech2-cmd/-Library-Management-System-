#include "Member.h"
#include <iostream>

void Member::print() const {
    std::cout << "[" << id << "] " << name
              << " <" << email << ">\n";
}
