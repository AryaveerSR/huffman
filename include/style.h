#ifndef STYLE_H
#define STYLE_H

#include <stdint.h>

enum SelectorType
{
    SELECTOR_SIMPLE,
};

struct Specificity
{
    unsigned int id;
    unsigned int class;
    unsigned int tags;
};

struct Selector
{
    enum SelectorType type;
    struct Specificity specificity;

    union
    {
        struct
        {
            char *tag;
            char *id;

            struct Class
            {
                char *name;
                struct Class *next;
            } *classes;
        } simple;
    } as;

    struct Selector *next;
};

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Value
{
    enum ValueType
    {
        VALUE_KEYWORD,
        VALUE_COLOR,
        VALUE_LENGTH,
    } type;

    union
    {
        char *keyword;
        struct Color color;

        struct
        {
            float magnitude;

            enum Unit
            {
                UNIT_PX
            } unit;
        } length;
    } as;
};

struct Declaration
{
    char *name;
    struct Value value;

    struct Declaration *next;
};

struct Rule
{
    struct Selector *selectors;
    struct Declaration *declarations;

    struct Rule *next;
};

struct Stylesheet
{
    struct Rule *rules;
};

void stylesheet_push(struct Stylesheet *stylesheet, struct Rule *rule);
void stylesheet_free(struct Stylesheet *stylesheet);

struct Rule *rule_new(void);
void rule_free(struct Rule *rule);
void rule_push_selector(struct Rule *rule, struct Selector *selector);
void rule_push_declaration(struct Rule *rule, struct Declaration *declaration);

struct Selector *selector_new(enum SelectorType type);
void selector_free(struct Selector *selector);
void selector_push_class(struct Selector *selector, char *class);

struct Declaration *declaration_new(char *name, struct Value value);
void declaration_free(struct Declaration *declaration);

void stylesheet_print(struct Stylesheet *stylesheet);
void rule_print(struct Rule *rule);
void selector_print(struct Selector *selector);
void declaration_print(struct Declaration *declaration);
void value_print(struct Value *value);

#endif
