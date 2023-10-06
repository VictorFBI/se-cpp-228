#include "is_leap.h"

bool IsLeap(int year) {
    const int h = 100;
    const int fh = 400;
    if ((static_cast<int>(year) % 4 == 0 && static_cast<int>(year) % h != 0) || static_cast<int>(year) % fh == 0) {
        return true;
    } else {
        return false;
    }
}
