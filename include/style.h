#ifndef STYLE_H
#define STYLE_H

#include <stdint.h>

struct Selector
{
    enum
    {
        SELECTOR_SIMPLE,
    } type;

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
            } classes;
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

#endif
