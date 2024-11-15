#include <stdio.h>

#include "str.h"
#include "log.h"
#include "css.h"

void try_source(char *source)
{
    struct Stylesheet styles = css_parse(source);

    stylesheet_print(&styles);
    stylesheet_free(&styles);
}

int main(void)
{
    log_init();
    str_init();

    try_source("* {   display: block; } html {   width: 600px;  background: #ffffff; }");
    try_source(".inner#bye {   background: #ffff00; }");
    try_source("span#name , p.class {   background: red;   color: white; }");

    str_free();
}
