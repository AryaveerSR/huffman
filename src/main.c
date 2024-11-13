#include <stdio.h>

#include "str.h"
#include "log.h"
#include "html.h"

int main(void)
{
    log_init();
    str_init();

    char *source = "<html><body><h1>Title</h1><div id=\"main\" class=\"test\"><p>Hello <em>world</em>!</p></div></body></html>";

    struct Node *tree = html_parse(source);

    node_print(tree);

    node_free(tree);
    str_free();
}
