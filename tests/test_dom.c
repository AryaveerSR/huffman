#include <assert.h>

#include "log.h"
#include "dom.h"

int main(void)
{
    log_init();

    struct Node *parent = node_new_element("body");

    struct Node *child_a = node_new_text("Hello world!");
    struct Node *child_b = node_new_text("Hello world! x2");

    node_push_child(parent, child_a);
    node_push_child(parent, child_b);

    node_print(parent);

    node_free(parent);
}