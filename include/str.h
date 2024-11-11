#ifndef STR_H
#define STR_H

#define STR(string) (str_intern(string, sizeof(string) - 1))

void str_init(void);
void str_free(void);

char *str_intern(char *ptr, unsigned int length);

#endif
