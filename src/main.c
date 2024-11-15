#include <stdio.h>

#include "str.h"
#include "log.h"
#include "css.h"

int main(void)
{
    log_init();
    str_init();

    char *source = "* {   display: block; }  span {   display: inline; }  html {   width: 600px;   padding: 10px;   border-width: 1px;   margin: auto;   background: #ffffff; }  head {   display: none; }  .outer {   background: #00ccff;   border-color: #666666;   border-width: 2px;   margin: 50px;   padding: 50px; }  .inner {   border-color: #cc0000;   border-width: 4px;   height: 100px;   margin-bottom: 20px;   width: 500px; }  .inner#bye {   background: #ffff00; }  span#name {   background: red;   color: white; }";

    struct Stylesheet styles = css_parse(source);

    stylesheet_print(&styles);

    stylesheet_free(&styles);
    str_free();
}
