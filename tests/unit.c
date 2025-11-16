#include "greatest.h"
#include "unit.h"

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(header_suite);
    RUN_SUITE(basic_id_suite);

    GREATEST_MAIN_END();
}