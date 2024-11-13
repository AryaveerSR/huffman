#include <assert.h>
#include <string.h>

#include "log.h"
#include "html.h"
#include "str.h"

int main(void)
{
    log_init();
    str_init();

    char *source = "<html><body><h1>Title</h1><div id=\"main\" class=\"test\"><p>Hello <em>world</em>!</p></div></body></html>";
    struct Node *tree = html_parse(source);

    assert(tree->type == NODE_ELEMENT);
    assert(strcmp(tree->as.element.tag, "html") == 0);

    struct Node *body = tree->as.element.children;

    assert(body->type == NODE_ELEMENT);
    assert(strcmp(body->as.element.tag, "body") == 0);

    struct Node *h1 = body->as.element.children;

    assert(h1->type == NODE_ELEMENT);
    assert(strcmp(h1->as.element.tag, "h1") == 0);
    assert(h1->as.element.children->type == NODE_TEXT);
    assert(strcmp(h1->as.element.children->as.text, "Title") == 0);

    struct Node *div = h1->next;

    assert(div->type == NODE_ELEMENT);
    assert(strcmp(div->as.element.tag, "div") == 0);
    assert(strcmp(htable_get(&div->as.element.attrs, "id"), "main") == 0);
    assert(strcmp(htable_get(&div->as.element.attrs, "class"), "test") == 0);

    node_print(tree);

    node_free(tree);
    str_free();
}