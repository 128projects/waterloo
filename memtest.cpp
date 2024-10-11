#include <stdint.h>

bool xanmem_test() {
    volatile uint32_t* test_address = (uint32_t*) 0x100000;
    uint32_t test_value = 0xDEADBEEF;

    *test_address = test_value;

    if (*test_address == test_value) {
        return true;
    }
    return false;
}
