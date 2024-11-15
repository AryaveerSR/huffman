#include <ctype.h>
#include <string.h>

#include "log.h"
#include "html.h"
#include "str.h"

/**
 * A basic HTML parser that turns an input string into the DOM representation in `dom.h`.
 */

/**
 * Global state for the parser.
 *
 * `source` is the input stream (stays constant).
 * `current_idx` is the current position while parsing.
 */
struct HTMLParser
{
    char *source;
    unsigned int current_idx;
};

static struct HTMLParser hp;

// Forward declarations.
static struct Node *html_parse_node(void);

/**
 * Utility function that advances the parser and returns the next character. *
 *
 * `current_idx` always has the index of the next character that *will* be consumed.
 *
 * Since the source is null-terminated, the case of end of input is handled by the callee
 * by matching for '\0'.
 *
 * @returns Next character from the source.
 */
static char html_advance(void)
{
    hp.current_idx += 1;
    return hp.source[hp.current_idx - 1];
}

/**
 * @returns Next character without advancing the parser.
 */
static char html_peek(void)
{
    return hp.source[hp.current_idx];
}

/**
 * @returns The nth next character without advancing the parser.
 *
 * n starts from 0, thus `html_peek_nth(0)` is the same as `html_peek()`.
 */
static char html_peek_nth(unsigned int n)
{
    return hp.source[hp.current_idx + n];
}

/**
 * Advances the parser and panics if the character is not what we expect.
 *
 * @param ch The character expected to be next.
 */
static void html_expect(char ch)
{
    char next = html_advance();

    if (next != ch)
    {
        panic("Expected %c found %c.", ch, next);
    }
}

/**
 * Consumes all whitespace until the next non-whitespace character.
 */
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

/**
 * Consumes all characters that are valid as an identifier and returns an interned string.
 */
static char *html_consume_identifier(void)
{
    unsigned int start_idx = hp.current_idx;

    while (isalnum(html_peek()) || (html_peek() == '-'))
    {
        html_advance();
    }

    char *identifier = str_intern(hp.source + start_idx, hp.current_idx - start_idx);

    trace("Consumed identifier %s.", identifier);

    return identifier;
}

/**
 * Parses loose text as a text node.
 * It is up to the callee to trim the preceding whitespaces by calling `html_consume_whitespace()`.
 *
 * todo!(): Trim following whitespace.
 */
static struct Node *html_parse_text(void)
{
    unsigned int start_idx = hp.current_idx;

    while ((html_peek() != '<') && (html_peek() != '\0'))
    {
        html_advance();
    }

    char *text = str_intern(hp.source + start_idx, hp.current_idx - start_idx);

    trace("Parsed text \"%s\".", text);

    return node_new_text(text);
}

/**
 * Parses a HTML element as an element node.
 * This consumes the starting tag, children and the closing tag for the element.
 */
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

        unsigned int start_idx = hp.current_idx;

        while (html_peek() != '"')
        {
            html_advance();
        }

        char *attr_value = str_intern(hp.source + start_idx, hp.current_idx - start_idx);

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

/**
 * Parses a HTML node.
 *
 * Calls either `html_parse_element()` or `html_parse_text()` based on the next character.
 */
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

/**
 * Parses a source string into a DOM tree.
 *
 * @param source Null-terminated source string.
 *
 * @returns Source parsed into a DOM tree.
 */
struct Node *html_parse(char *source)
{
    hp.source = source;
    hp.current_idx = 0;

    return html_parse_node();
}
