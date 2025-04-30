#include <stdio.h>

enum type {pair, string, vector};

typedef struct values *SCM;

struct value{
    enum type type;
    union 
    {
        struct {SCM car, cdr;} pair;
        struct {int length; char *elts;} string;
        struct {int length; SCM *elts;} vector;
    } value;
};

#define POINER_P(x) (((int)(x) & 7) == 0)
#define INTEGER_P(x) (!POINER_P(x))

#define GET_INTEGER(x) ((int)(x) >> 3)
#define MAKE_INTEGER(x) ((SCM) (((x) << 3) | 1))