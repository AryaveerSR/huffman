#include <stdio.h>
#include <stdlib.h>

#include "dom.h"
#include "log.h"

struct Node *node_alloc(struct Node node)
{
    struct Node *ptr = malloc(sizeof(struct Node));

    if (ptr == NULL)
    {
        panic("Out of memory.");
    }

    *ptr = node;
    return ptr;
}

struct Node *node_new_text(char *text)
{
    struct Node node;

    node.type = NODE_TEXT;
    node.next = NULL;

    node.as.text = text;

    return node_alloc(node);
}

struct Node *node_new_element(char *tag)
{
    struct Node node;

    node.type = NODE_ELEMENT;
    node.next = NULL;

    node.as.element.tag = tag;
    node.as.element.children = NULL;
    htable_init(&node.as.element.attrs);

    return node_alloc(node);
}

void node_free(struct Node *node)
{
    if (node->type == NODE_ELEMENT)
    {
        struct Node *next_child = node->as.element.children;

        while (next_child != NULL)
        {
            struct Node *current_child = next_child;
            next_child = next_child->next;

            node_free(current_child);
        }

        htable_free(&node->as.element.attrs);
    }

    free(node);
}

void node_push_child(struct Node *parent, struct Node *child)
{
    if (parent->type == NODE_TEXT)
    {
        panic("Text nodes cannot have children.");
    }

    struct Node **front_child = &parent->as.element.children;

    while (*front_child != NULL)
    {
        front_child = &((*front_child)->next);
    }

    *front_child = child;
}

static void node_print_internal(struct Node *node, unsigned int indent)
{
    for (unsigned int i = 0; i < indent; i++)
    {
        printf("  ");
    }

    printf("+ ");

    switch (node->type)
    {
    case NODE_TEXT:
        printf("NODE_TEXT: \"%s\"\n", node->as.text);
        break;

    case NODE_ELEMENT:
        printf("NODE_ELEMENT: %s ", node->as.element.tag);
        htable_print(&node->as.element.attrs);
        printf("\n");

        struct Node *next_child = node->as.element.children;

        while (next_child != NULL)
        {
            node_print_internal(next_child, indent + 1);
            next_child = next_child->next;
        }

        break;

    default:
        panic("Unknown node of type: %d.", node->type);
    }
}

void node_print(struct Node *node)
{
    node_print_internal(node, 0);
}
