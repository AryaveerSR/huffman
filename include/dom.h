#ifndef DOM_H
#define DOM_H

#include "hashtable.h"

struct Node
{
    struct Node *next;

    enum NodeType
    {
        NODE_TEXT,
        NODE_ELEMENT,
    } type;

    union
    {
        char *text;

        struct ElementNode
        {
            char *tag;
            struct Node *children;
            struct Hashtable attrs;
        } element;
    } as;
};

struct Node *node_alloc(struct Node node);
struct Node *node_new_text(char *text);
struct Node *node_new_element(char *tag);

void node_free(struct Node *node);

void node_push_child(struct Node *parent, struct Node *child);

void node_print(struct Node *node);

#endif
