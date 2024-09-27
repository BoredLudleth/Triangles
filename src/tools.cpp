#include "tools.hpp"

bool cmp(float a, float b) {
    return fabs(a - b) < epsilon;
}
