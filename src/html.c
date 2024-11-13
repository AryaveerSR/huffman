#include <ctype.h>
#include <string.h>

#include "log.h"
#include "html.h"
#include "str.h"

struct HTMLParser
{
    char *source;

    unsigned int start_idx;
    unsigned int current_idx;
};

static struct HTMLParser hp;

// Forward declarations.
static struct Node *html_parse_node(void);

static char html_advance(void)
{
    hp.current_idx += 1;
    return hp.source[hp.current_idx - 1];
}

static char html_peek(void)
{
    return hp.source[hp.current_idx];
}

static char html_peek_nth(unsigned int n)
{
    return hp.source[hp.current_idx + n];
}

static void html_expect(char ch)
{
    char next = html_advance();

    if (next != ch)
    {
        panic("Expected %c found %c.", ch, next);
    }
}

static void html_consume_whitespace(void)
{
    while (true)
    {
        switch (html_peek())
        {
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            html_advance();
            continue;

        default:
            return;
        }
    }
}

static char *html_consume_identifier(void)
{
    hp.start_idx = hp.current_idx;

    while (isalnum(html_peek()) || (html_peek() == '-'))
    {
        html_advance();
    }

    char *identifier = str_intern(hp.source + hp.start_idx, hp.current_idx - hp.start_idx);

    trace("Consumed identifier %s.", identifier);

    return identifier;
}

static struct Node *html_parse_text(void)
{
    hp.start_idx = hp.current_idx;

    while ((html_peek() != '<') && (html_peek() != '\0'))
    {
        html_advance();
    }

    char *text = str_intern(hp.source + hp.start_idx, hp.current_idx - hp.start_idx);

    trace("Parsed text \"%s\".", text);

    return node_new_text(text);
}

static struct Node *html_parse_element(void)
{
    html_expect('<');

    char *tag = html_consume_identifier();

    trace("Parsing %s tag.", tag);

    html_consume_whitespace();

    struct Node *element = node_new_element(tag);

    while (html_peek() != '>')
    {
        char *attr_name = html_consume_identifier();

        html_expect('=');
        html_expect('"');

        hp.start_idx = hp.current_idx;

        while (html_peek() != '"')
        {
            html_advance();
        }

        char *attr_value = str_intern(hp.source + hp.start_idx, hp.current_idx - hp.start_idx);

        html_expect('"');
        html_consume_whitespace();

        trace("Found attribute %s=\"%s\"", attr_name, attr_value);

        htable_insert(&element->as.element.attrs, attr_name, attr_value);
    }

    html_expect('>');

    while ((html_peek() != '<') || (html_peek_nth(1) != '/'))
    {
        trace("Parsing child node.");

        node_push_child(element, html_parse_node());
    }

    html_expect('<');
    html_expect('/');

    if (strncmp(hp.source + hp.current_idx, tag, strlen(tag)) != 0)
    {
        panic("Expected closing tag for %s, found %.*s", tag, hp.source + hp.current_idx);
    }

    hp.current_idx += strlen(tag);

    html_expect('>');

    return element;
}

static struct Node *html_parse_node(void)
{
    html_consume_whitespace();

    if (html_peek() == '<')
    {
        return html_parse_element();
    }
    else
    {
        return html_parse_text();
    }
}

struct Node *html_parse(char *source)
{
    hp.source = source;
    hp.start_idx = 0;
    hp.current_idx = 0;

    return html_parse_node();
}
