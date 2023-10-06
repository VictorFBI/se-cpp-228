#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    if (static_cast<int>(height) >= slices_amount || static_cast<int>(width) >= slices_amount) {
        return true;
    } else {
        return false;
    }
}