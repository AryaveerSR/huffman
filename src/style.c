#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "log.h"
#include "style.h"

void stylesheet_push(struct Stylesheet *stylesheet, struct Rule *rule)
{
    rule->next = stylesheet->rules;
    stylesheet->rules = rule;
}

void stylesheet_free(struct Stylesheet *stylesheet)
{
    struct Rule *rule = stylesheet->rules;

    while (rule != NULL)
    {
        struct Rule *next = rule->next;

        rule_free(rule);

        rule = next;
    }
}

struct Rule *rule_new(void)
{
    struct Rule *ptr = malloc(sizeof(struct Rule));

    if (ptr == NULL)
    {
        panic("Out of memory.");
    }

    ptr->selectors = NULL;
    ptr->declarations = NULL;
    ptr->next = NULL;

    return ptr;
}

void rule_free(struct Rule *rule)
{
    struct Selector *selector = rule->selectors;

    while (selector != NULL)
    {
        struct Selector *next = selector->next;

        selector_free(selector);

        selector = next;
    }

    struct Declaration *declaration = rule->declarations;

    while (declaration != NULL)
    {
        struct Declaration *next = declaration->next;

        declaration_free(declaration);

        declaration = next;
    }

    free(rule);
}

bool specificity_compare(struct Specificity *a, struct Specificity *b)
{
    if (a->id > b->id)
    {
        return true;
    }
    else if (a->id < b->id)
    {
        return false;
    }
    else if (a->class > b->class)
    {
        return true;
    }
    else if (a->class < b->class)
    {
        return false;
    }
    else if (a->tags > b->tags)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void rule_push_selector(struct Rule *rule, struct Selector *selector)
{
    struct Selector **ref = &rule->selectors;

    while ((*ref != NULL) && (specificity_compare(&((*ref)->specificity), &selector->specificity)))
    {
        ref = &((*ref)->next);
    }

    selector->next = *ref;
    *ref = selector;
}

void rule_push_declaration(struct Rule *rule, struct Declaration *declaration)
{
    declaration->next = rule->declarations;
    rule->declarations = declaration;
}

struct Selector *selector_new(enum SelectorType type)
{
    struct Selector *ptr = malloc(sizeof(struct Selector));

    if (ptr == NULL)
    {
        panic("Out of memory.");
    }

    ptr->type = type;

    ptr->specificity.id = 0;
    ptr->specificity.class = 0;
    ptr->specificity.tags = 0;

    switch (type)
    {
    case SELECTOR_SIMPLE:
        ptr->as.simple.id = NULL;
        ptr->as.simple.tag = NULL;
        ptr->as.simple.classes = NULL;
        break;

    default:
        panic("Unknown selector type: %d.", type);
    }

    return ptr;
}

void selector_free(struct Selector *selector)
{
    switch (selector->type)
    {
    case SELECTOR_SIMPLE:
    {
        struct Class *class = selector->as.simple.classes;

        while (class != NULL)
        {
            struct Class *next = class->next;

            free(class);

            class = next;
        }
        break;
    }

    default:
        panic("Unknown selector type: %d.", selector->type);
    }

    free(selector);
}

void selector_push_class(struct Selector *selector, char *class)
{
    struct Class *ptr = malloc(sizeof(struct Class));

    if (ptr == NULL)
    {
        panic("Out of memory.");
    }

    ptr->name = class;
    ptr->next = selector->as.simple.classes;

    selector->as.simple.classes = ptr;
}

struct Declaration *declaration_new(char *name, struct Value value)
{
    struct Declaration *ptr = malloc(sizeof(struct Declaration));

    if (ptr == NULL)
    {
        panic("Out of memory.");
    }

    ptr->name = name;
    ptr->value = value;

    return ptr;
}

void declaration_free(struct Declaration *declaration)
{
    free(declaration);
}

void stylesheet_print(struct Stylesheet *stylesheet)
{
    struct Rule *rule = stylesheet->rules;

    while (rule != NULL)
    {
        rule_print(rule);
        rule = rule->next;
    }
}

void rule_print(struct Rule *rule)
{
    puts("(Rule)\nSelectors:");

    struct Selector *selector = rule->selectors;

    while (selector != NULL)
    {
        selector_print(selector);
        selector = selector->next;
    }
    puts("Declarations:");

    struct Declaration *declaration = rule->declarations;

    while (declaration != NULL)
    {
        declaration_print(declaration);
        declaration = declaration->next;
    }
}

void selector_print(struct Selector *selector)
{
    switch (selector->type)
    {
    case SELECTOR_SIMPLE:
    {
        puts("((Simple selector))");

        if (selector->as.simple.tag != NULL)
        {
            printf("- Tag: %s.\n", selector->as.simple.tag);
        }

        if (selector->as.simple.id != NULL)
        {
            printf("- ID: %s.\n", selector->as.simple.id);
        }

        struct Class *class = selector->as.simple.classes;

        while (class != NULL)
        {
            printf("- Class: %s.\n", class->name);
            class = class->next;
        }

        break;
    }

    default:
        panic("Unknown selector type: %d.", selector->type);
    }
}

void declaration_print(struct Declaration *declaration)
{
    printf("- %s: ", declaration->name);
    value_print(&declaration->value);
    printf("\n");
}

void value_print(struct Value *value)
{
    switch (value->type)
    {
    case VALUE_COLOR:
        printf("rgba(%d,%d,%d,%d)", value->as.color.r, value->as.color.g, value->as.color.b, value->as.color.a);
        break;

    case VALUE_KEYWORD:
        printf("%s", value->as.keyword);
        break;

    case VALUE_LENGTH:
        printf("%f", value->as.length.magnitude);

        switch (value->as.length.unit)
        {
        case UNIT_PX:
            printf("px");
            break;

        default:
            panic("Unknown unit: %d.", value->as.length.unit);
        }

        break;

    default:
        panic("Unknown value type: %d.", value->type);
    }
}
