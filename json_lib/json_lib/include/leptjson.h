//  leptjson.hpp
//  Created by gan on 2021/1/11.
#ifndef leptjson_hpp
#define leptjson_hpp

#include <stdio.h>
#include <string>

typedef enum {LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING,
    LEPT_ARRAY, LEPT_OBJECT
} lept_type;
typedef struct lept_value lept_value;
typedef struct lept_member lept_member;

struct lept_value{
    lept_type type;
    // input cannot be number and string together and data in union share the memory.
    union{
        double n;                                     // value of number.
        struct { char* s; size_t len; }str;           // value of string.
        struct { lept_value* e; size_t len; }array;   // value of array.
        struct { lept_member* m; size_t len; } object; // value of object.
    } u;
};

struct lept_member{
    char* k; size_t klen;   // member key string, key string length.
    lept_value v;       // member value.
};

typedef struct{
    const char* json;
    std::string str;
} lept_context;


enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE = 1,
    LEPT_PARSE_ROOT_NOT_SINGULAR = 2,
    LEPT_PARSE_INVALID_VALUE = 3,
    LEPT_PARSE_MISS_QUOTATION_MARK=4,
    LEPT_PARSE_INVALID_STRING_ESCAPE = 5,
    LEPT_PARSE_INVALID_STRING_UNESCAPE=6,
    LEPT_PARSE_INVALID_UNICODE_HEX=7,
    LEPT_PARSE_INVALID_UNICODE_SURROGATE=8
};

void lept_parse_whitespace(lept_context* c);

int lept_parse_literal(lept_context* c, lept_value* v, lept_type type, const char* json, const char* delimeter="\0");

int lept_parse_number(lept_context* c, lept_value* v, const char* delimeter="\0");

int lept_parse_string(lept_context* c, lept_value* v, const char* delimeter="\0");

int lept_parse_array(lept_context* c, lept_value* v, const char* delimeter="\0");
lept_value* lept_get_array_element(const lept_value* v, size_t index);

int lept_parse_object(lept_context* c, lept_value* v, const char* delimeter="\0");
lept_member* lept_get_object_element(const lept_value* v, size_t index);

char* lept_stringify_literal(const lept_value* v, char* s, size_t& len, const char* delimeter="\0");

char* lept_stringify_number(const lept_value* v, char* s, size_t& len, const char* delimeter="\0");

char* lept_stringify_string(const lept_value* v, char* s, size_t& len, const char* delimeter="\0");

char* lept_stringify_array(const lept_value* v, char* s, size_t& len, const char* delimeter="\0");

char* lept_stringify_object(const lept_value* v, char* s, size_t& len, const char* delimeter="\0");

void lept_free(lept_value* v);

lept_type lept_get_type(const lept_value* v);

double lept_get_number(const lept_value* v);

char* lept_get_string(const lept_value* v);

#endif /* leptjson_hpp */
