//
// Created by Adithiya Venkatakrishnan on 16/12/2024.
//

#include "strings.h"

#include <memory/memory.h>

#include "modules.h"

int strlen(const char* str) {
    int i = 0;
    while (str[i] != 0x00) i++;
    return i;
}

void* strcpy(void* dst, const char* src) {
    u8 *d = dst;
    const u8 *s = (u8*)src;

    while (*s) {
        *d++ = *s++;
    }

    return d;
}

int strcmp(char* s1, char* s2) {
    u32 t = max(strlen(s1), strlen(s2)) + 1;

    return strncmp(s1, s2, t);
}

int strncmp(char* s1, char* s2, u32 t) {
    u8* c1 = (u8*)s1;
    u8* c2 = (u8*)s2;
    int i = 0;
    while (c1[i] != 0x00 && c2[i] != 0x00 && i < t) {
        if (c1[i] == c2[i]) {
            i++;
            continue;
        };
        if (c1[i] < c2[i]) return -1;
        if (c1[i] > c2[i]) return 1;
        i++;
    }
    if (c1[i] == 0x00 && c2[i] == 0x00) return 0;
    if (c1[i] == 0x00) return -1;
    if (c2[i] == 0x00) return 1;
    return -1;
}

char* strdup(const char* str) {
    u32 len = strlen(str);

    char* new_str = malloc(len + 1);
    strcpy(new_str, str);

    return new_str;
}

char* olds;

/// All credit goes to the Berkeley Software Distribution (BSD) for this function
/// because without them, I may have gone insane.
char* strtok(char* str, const char* sep) {
    static char* last;
    return strtok_r(str, sep, &last);
}

/// All credit goes to the Berkeley Software Distribution (BSD) for this function
/// because without them, I may have gone insane.
char* strtok_r(char* s, const char* delim, char** last) {
    const char* spanp;
    int c, sc;
    char* tok;

    if (s == null && (s = *last) == null)
        return (null);
    /*
     * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
     */
    cont:
        c = *s++;
    for (spanp = delim; (sc = *spanp++) != 0;) {
        if (c == sc)
            goto cont;
    }

    if (c == 0) {		/* no non-delimiter characters */
        *last = null;
        return (null);
    }
    tok = s - 1;

    /*
     * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
     * Note that delim must have one NUL; we stop if we see that, too.
     */
    for (;;) {
        c = *s++;
        spanp = delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0)
                    s = null;
                else
                    s[-1] = '\0';
                *last = s;
                return (tok);
            }
        } while (sc != 0);
    }
    /* NOTREACHED */
}

StrtokA strtok_a(char* s, const char* delim) {
    static char* last; // last is static so it can be used in multiple calls

    int size = 2, count = 0;
    char** ret = malloc(sizeof(char*) * 2);

    char* str = strdup(s);

    for (char* word = strtok_r(str, delim, &last);
         word;
         word = strtok_r(null, delim, &last)) {
        ret[count] = word;
        count++;
        if (count == size) {
            size += 2;
            ret = realloc(ret, sizeof(char*) * size);
        }
    }

    free(str, strlen(str)+1);

    return (StrtokA){ret, count};
}