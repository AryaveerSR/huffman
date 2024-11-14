#include <stdio.h>

#include "str.h"
#include "log.h"
#include "css.h"

int main(void)
{
    log_init();
    str_init();

    char *source = "* {   display: block; }  html {   width: 600px;  background: #ffffff; }   .inner#bye {   background: #ffff00; }  span#name {   background: red;   color: white; }";

    struct Stylesheet styles = css_parse(source);

    stylesheet_print(&styles);

    stylesheet_free(&styles);
    str_free();
}
