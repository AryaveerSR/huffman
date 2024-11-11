#include <assert.h>

#include "str.h"
#include "log.h"

int main(void)
{
    log_init();

    str_init();

    char *hello_1 = STR("Hello");
    char *hello_2 = str_intern("Hello world!", 5);

    assert(hello_1 == hello_2);
    assert(hello_1 != STR("Hi"));

    str_free();
}