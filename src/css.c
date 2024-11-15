#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "css.h"
#include "str.h"
#include "log.h"

struct CSSParser
{
    char *source;

    unsigned int start_idx;
    unsigned int current_idx;
};

static struct CSSParser cp;

static char css_advance(void)
{
    cp.current_idx += 1;
    return cp.source[cp.current_idx - 1];
}

static char css_peek(void)
{
    return cp.source[cp.current_idx];
}

static void css_expect(char ch)
{
    char next = css_advance();

    if (next != ch)
    {
        panic("Expected %c found %c.", ch, next);
    }
}

static void css_consume_whitespace(void)
{
    while (true)
    {
        switch (css_peek())
        {
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            css_advance();
            continue;

        default:
            return;
        }
    }
}

static char *css_consume_identifier(void)
{
    cp.start_idx = cp.current_idx;

    while (isalnum(css_peek()) || (css_peek() == '-'))
    {
        css_advance();
    }

    char *identifier = str_intern((char *)(cp.source + cp.start_idx), cp.current_idx - cp.start_idx);

    trace("Consumed identifier %s.", identifier);

    return identifier;
}

static uint8_t css_consume_hex_pair(void)
{
    uint8_t high_char = (uint8_t)css_advance();
    uint8_t low_char = (uint8_t)css_advance();

    uint8_t high = (high_char & 0xF) + (high_char >> 6) | ((high_char >> 3) & 0x8);
    uint8_t low = (low_char & 0xF) + (low_char >> 6) | ((low_char >> 3) & 0x8);

    return (uint8_t)((high << 4) | low);
}

static struct Selector *css_parse_selector(void)
{
    struct Selector *selector = selector_new(SELECTOR_SIMPLE);

    if (css_peek() == '*')
    {
        css_advance();
        css_consume_whitespace();
    }

    if (isalnum(css_peek()))
    {
        selector->as.simple.tag = css_consume_identifier();
        selector->specificity.tags = 1;
    }

    while ((css_peek() != ',') && (css_peek() != '{'))
    {
        if (css_peek() == '#')
        {
            css_advance();

            selector->as.simple.id = css_consume_identifier();
            selector->specificity.id = 1;
        }

        if (css_peek() == '.')
        {
            css_advance();

            selector_push_class(selector, css_consume_identifier());
            selector->specificity.class += 1;
        }

        css_consume_whitespace();
    }

    return selector;
}

static struct Value css_parse_length(void)
{
    char *end;
    float magnitude = strtof(cp.source + cp.current_idx, &end);

    cp.current_idx += end - (cp.source + cp.current_idx);

    char *unit = css_consume_identifier();

    struct Value value = {.type = VALUE_LENGTH, .as = {.length = {.magnitude = magnitude}}};

    if (strcmp(unit, "px") == 0)
    {
        value.as.length.unit = UNIT_PX;
    }
    else
    {
        panic("Unknown length unit: %.*s.", 16, cp.source + cp.current_idx);
    }

    return value;
}

static struct Value css_parse_hex_color(void)
{
    css_expect('#');

    uint8_t r = css_consume_hex_pair();
    uint8_t g = css_consume_hex_pair();
    uint8_t b = css_consume_hex_pair();

    return (struct Value){.type = VALUE_COLOR, .as = {.color = {.r = r, .g = g, .b = b, .a = 255}}};
}

static struct Value css_parse_value(void)
{
    if (isdigit(css_peek()))
    {
        return css_parse_length();
    }

    if (css_peek() == '#')
    {
        return css_parse_hex_color();
    }

    return (struct Value){.type = VALUE_KEYWORD, .as = {.keyword = css_consume_identifier()}};
}

static struct Declaration *css_parse_declaration(void)
{
    char *name = css_consume_identifier();

    css_consume_whitespace();
    css_expect(':');
    css_consume_whitespace();

    struct Value value = css_parse_value();

    css_expect(';');

    return declaration_new(name, value);
}

static struct Rule *css_parse_rule(void)
{
    struct Rule *rule = rule_new();

    while (css_peek() != '{')
    {
        rule_push_selector(rule, css_parse_selector());
        css_consume_whitespace();

        if (css_peek() == ',')
        {
            css_advance();
            css_consume_whitespace();
        }
    }

    css_advance();
    css_consume_whitespace();

    while (css_peek() != '}')
    {
        rule_push_declaration(rule, css_parse_declaration());
        css_consume_whitespace();
    }

    css_advance();
    return rule;
}

struct Stylesheet css_parse(char *source)
{
    cp.source = source;
    cp.start_idx = 0;
    cp.current_idx = 0;

    struct Stylesheet stylesheet = {.rules = NULL};

    css_consume_whitespace();

    while (css_peek() != '\0')
    {
        stylesheet_push(&stylesheet, css_parse_rule());
        css_consume_whitespace();
    }

    return stylesheet;
}
