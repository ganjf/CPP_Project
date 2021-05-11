//
//  leptjson.cpp
//  Created by gan on 2021/1/11.
#include <iostream>
#include <stdlib.h>
#include "leptjson.h"
#include "assert.h"
#include <regex>

using namespace std;

#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch) ((ch) >= '1' && (ch) <= '9')

void lept_parse_whitespace(lept_context* c){
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == 'r'){
        p ++;
    }
    c->json = p;
}


// Parse Literal: null = "null", false = "false", true = "true"
int lept_parse_literal(lept_context* c, lept_value* v, lept_type type, const char* json, const char* delimeter){
    const char* p = c->json;
    for(; *json!='\0'; json++, c->json++){
        if (*c->json == '\0' || *c->json != *json)
            return LEPT_PARSE_INVALID_VALUE;
    }
    lept_parse_whitespace(c);
    if (*c->json == *delimeter){
        v->type = type;
        return LEPT_PARSE_OK;
    }else{
        c->json = p;
        return LEPT_PARSE_INVALID_VALUE;
    }
}


// Parse Number: int or float
int lept_parse_number(lept_context* c, lept_value* v, const char* delimeter){
    char* p1 = NULL;
    double ret;
    const char* p = c->json;
    ret = strtod(c->json, &p1);
    if (p1 == c->json)
        return LEPT_PARSE_INVALID_VALUE;
    c->json = p1;
    lept_parse_whitespace(c);
    if (*c->json == *delimeter){
        v->type = LEPT_NUMBER;
        v->u.n = ret;
        return LEPT_PARSE_OK;
    }else{
        c->json = p;
        return LEPT_PARSE_INVALID_VALUE;
    }
}


// Parse String.
// Decoding Unicode.
const char* lept_parse_hex4(const char* p, unsigned& u){
    u = 0;
    for (int i=0; i<4; i++){
        char ch = *p++;
        if (ch >='0' && ch <= '9') u += (ch - '0') * pow(16, 3-i);
        else if (ch >= 'A' && ch <= 'F') u += (ch - 'A' + 10) * pow(16, 3-i);
        else if (ch >= 'a' && ch <= 'f') u += (ch - 'a' + 10) * pow(16, 3-i);
        else return NULL;
    }
    return p;
}

// Encoding UTF-8 from Unicode.
void lept_encode_utf8(lept_context* c, unsigned& u){
    if (u <= 0x7F)
        c->str.push_back(static_cast<char>(u & 0xFF)); // 0xxxxxxx
    else if (u <= 0x7FF) {
        c->str.push_back(static_cast<char>(0xC0 | ((u >> 6) & 0xFF))); // 110xxxxx
        c->str.push_back(static_cast<char>(0x80 | ( u & 0x3F))); // 10xxxxxx
    }
    else if (u <= 0xFFFF) {
        c->str.push_back(static_cast<char>(0xE0 | ((u >> 12) & 0xFF))); // 1110xxx
        c->str.push_back(static_cast<char>(0x80 | ((u >> 6) & 0x3F))); // 10xxxxxx
        c->str.push_back(static_cast<char>(0x80 | ( u & 0x3F))); // 10xxxxxx
    }
    else {
        assert(u <= 0x10FFFF);
        c->str.push_back(static_cast<char>(0xF0 | ((u >> 18) & 0xFF))); // 11110xxx
        c->str.push_back(static_cast<char>(0x80 | ((u >> 12) & 0x3F))); // 10xxxxxx
        c->str.push_back(static_cast<char>(0x80 | ((u >> 6) & 0x3F))); // 10xxxxxx
        c->str.push_back(static_cast<char>(0x80 | ( u & 0x3F))); // 10xxxxxx
    }
}

void lept_set_string(lept_value* v, const char* s, size_t len){
    assert(v != NULL && (s != NULL || len == 0));
    v->u.str.s = (char*)malloc(len + 1);
    memcpy(v->u.str.s, s, len);
    v->u.str.s[len] = '\0';
    v->u.str.len = len;
    v->type = LEPT_STRING;
}

// parsed string saved at c.str (string class);
int lept_parse_string_raw(lept_context* c, const char* delimeter){
    const char* p = c->json;
    unsigned u, u2;
        // If string doesn't start with '"', return quotation missing.
    if (*c->json++ == '\"'){
        c->str.clear();
    }else{
        return LEPT_PARSE_MISS_QUOTATION_MARK;
    }
    while (true){
        char ch = *c->json++;
        switch (ch) {
            case '\"':
                lept_parse_whitespace(c);
                if (*c->json == *delimeter){
                    return LEPT_PARSE_OK;
                }else{
                    c->json = p;
                    return LEPT_PARSE_INVALID_VALUE;
                }
            case '\\':
                    // escape character.
                switch (*c->json++) {
                    case '\"': c->str.push_back('\"'); break;
                    case '\\': c->str.push_back('\\'); break;
                    case '/': c->str.push_back('/'); break;
                    case 'b': c->str.push_back('\b'); break;
                    case 'f': c->str.push_back('\f'); break;
                    case 'n': c->str.push_back('\n'); break;
                    case 'r': c->str.push_back('\r'); break;
                    case 't': c->str.push_back('\t'); break;
                    case 'u':
                        if (!(c->json = lept_parse_hex4(c->json, u)))
                            return LEPT_PARSE_INVALID_UNICODE_HEX;
                            // If the code point of Unicode locates between U+D800 and U+DBFF,
                            // Json will use surrogate pair (U+DC00 - U+DFFF) to contribute code point.
                            // codepoint = 0x10000 + (H − 0xD800) × 0x400 + (L − 0xDC00)
                        if (u >= 0xD800 && u <= 0xDBFF) { /* surrogate pair */
                            if (*c->json++ != '\\')
                                return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
                            if (*c->json++ != 'u')
                                return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
                            if (!(c->json = lept_parse_hex4(p, u2)))
                                return LEPT_PARSE_INVALID_UNICODE_HEX;
                            if (u2 < 0xDC00 || u2 > 0xDFFF)
                                return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
                            u = (((u - 0xD800) << 10) | (u2 - 0xDC00)) + 0x10000;
                        }
                        lept_encode_utf8(c, u);
                        break;
                    default: return LEPT_PARSE_INVALID_STRING_ESCAPE;
                }
                break;
            case '\0':
                return LEPT_PARSE_MISS_QUOTATION_MARK;
            default:
                // illegal character.
                if (static_cast<unsigned>(ch) < 0x20)
                    return LEPT_PARSE_INVALID_STRING_UNESCAPE;
                c->str.push_back(ch); break;
        }
    }
}

int lept_parse_string(lept_context* c, lept_value* v, const char* delimeter){
    int ret;
    ret = lept_parse_string_raw(c, delimeter);
    if (ret == LEPT_PARSE_OK){
        lept_set_string(v, c->str.c_str(), c->str.size());
    }
    return ret;
}


// Parse Array.
lept_value* lept_get_array_element(const lept_value* v, size_t index){
    assert (v != NULL && v->type == LEPT_ARRAY);
    assert (index < v->u.array.len);
    return &(v->u.array.e)[index];
}

void lept_extend_array(lept_value* array_v, lept_value* item_v){
    array_v->u.array.len ++;
    array_v->u.array.e = (lept_value*)realloc(array_v->u.array.e, array_v->u.array.len * sizeof(lept_value));
    memcpy((lept_value*)array_v->u.array.e + (array_v->u.array.len-1), item_v, sizeof(lept_value));
}

int lept_parse_array(lept_context* c, lept_value* v, const char* delimeter){
    v->type = LEPT_ARRAY;
    v->u.array.len = 0;
    v->u.array.e = NULL;
    int ret;
    const char* p = c->json;
    lept_value temp;
    
    if (*c->json++ != '['){
        return LEPT_PARSE_MISS_QUOTATION_MARK;
    }
    while (*c->json != '\0'){
        char ch = *c->json;
        if (ch == '\"'){
            if ((ret = lept_parse_string(c, &temp, ",")) == LEPT_PARSE_OK or (ret = lept_parse_string(c, &temp, "]")) == LEPT_PARSE_OK){
                lept_extend_array(v, &temp);
            }else{
                return ret;
            }
        }else if (ch >= '0' && ch <='9'){
            if ((ret = lept_parse_number(c, &temp, ",")) == LEPT_PARSE_OK or (ret = lept_parse_number(c, &temp, "]")) == LEPT_PARSE_OK){
                lept_extend_array(v, &temp);
            }else{
                return ret;
            }
        }else if (ch == '['){
            if ((ret = lept_parse_array(c, &temp, ",")) == LEPT_PARSE_OK or (ret = lept_parse_array(c, &temp, "]")) == LEPT_PARSE_OK){
                lept_extend_array(v, &temp);
            }else{
                return ret;
            }
        }else if (ch == '{'){
            if ((ret = lept_parse_object(c, &temp, ",")) == LEPT_PARSE_OK or (ret = lept_parse_object(c, &temp, "]")) == LEPT_PARSE_OK){
                lept_extend_array(v, &temp);
            }else{
                return ret;
            }
        }
        else if (ch == ',' or ch == ' '){
            c->json ++;
        }else if (ch == 'n'){
            if ((ret = lept_parse_literal(c, &temp, LEPT_NULL, "null", ",")) == LEPT_PARSE_OK or (ret = lept_parse_literal(c, &temp, LEPT_NULL, "null", "]")) == LEPT_PARSE_OK){
                lept_extend_array(v, &temp);
            }else{
                return ret;
            }
        }else if (ch == 't'){
            if ((ret = lept_parse_literal(c, &temp, LEPT_TRUE, "true", ",")) == LEPT_PARSE_OK or (ret = lept_parse_literal(c, &temp, LEPT_TRUE, "true", "]")) == LEPT_PARSE_OK){
                lept_extend_array(v, &temp);
            }else{
                return ret;
            }
        }else if (ch == 'f'){
            if ((ret = lept_parse_literal(c, &temp, LEPT_FALSE, "false", ",")) == LEPT_PARSE_OK or (ret = lept_parse_literal(c, &temp, LEPT_FALSE, "false", "]")) == LEPT_PARSE_OK){
                lept_extend_array(v, &temp);
            }else{
                return ret;
            }
        }else if (ch == ']'){
            c->json ++;
            lept_parse_whitespace(c);
            if (*c->json == *delimeter){
                return LEPT_PARSE_OK;
            }else{
                c->json = p;
                return LEPT_PARSE_INVALID_VALUE;
            }
        }else{
            c->json = p;
            return LEPT_PARSE_INVALID_VALUE;
        }
    }
    return LEPT_PARSE_INVALID_VALUE;
}


// Parse Object.
lept_member* lept_get_object_element(const lept_value* v, size_t index){
    assert (v != NULL && v->type == LEPT_OBJECT);
    assert (index < v->u.object.len);
    return &(v->u.object.m)[index];
}

void lept_extend_object(lept_value* object_v, lept_member* item_v){
    object_v->u.object.len ++;
    object_v->u.object.m =(lept_member*)realloc(object_v->u.object.m, object_v->u.object.len * sizeof(lept_member));
    memcpy((lept_member*)object_v->u.object.m + (object_v->u.object.len-1), item_v, sizeof(lept_member));
}

int lept_parse_object_key(lept_context* c, lept_member* m){
    int ret;
    ret = lept_parse_string_raw(c, ":");
    if (ret == LEPT_PARSE_OK){
        c->json ++;
        size_t len = c->str.size();
        m->k = (char*)malloc(len + 1);
        memcpy(m->k, c->str.c_str(), len);
        *(m->k + len)= '\0';
        m->klen = len;
    }
    return ret;
}

int lept_parse_object_value(lept_context* c, lept_member* m){
    int ret;
    if (*c->json == '\"'){
        if ((ret = lept_parse_string(c, &m->v, ",")) == LEPT_PARSE_OK or (ret = lept_parse_string(c, &m->v, "}")) == LEPT_PARSE_OK){;}
        return ret;
    }else if (*c->json >= '0' && *c->json <= '9'){
        if ((ret = lept_parse_number(c, &m->v, ",")) == LEPT_PARSE_OK or (ret = lept_parse_number(c, &m->v, "}")) == LEPT_PARSE_OK){;}
        return ret;
    }else if (*c->json == '['){
        if ((ret = lept_parse_array(c, &m->v, ",")) == LEPT_PARSE_OK or (ret = lept_parse_array(c, &m->v, "}")) == LEPT_PARSE_OK){;}
        return ret;
    }else if (*c->json == 'n'){
        if ((ret = lept_parse_literal(c, &m->v, LEPT_NULL, "null", ",")) == LEPT_PARSE_OK or (ret = lept_parse_literal(c, &m->v, LEPT_NULL, "null", "}")) == LEPT_PARSE_OK){;}
        return ret;
    }else if (*c->json == 't'){
        if ((ret = lept_parse_literal(c, &m->v, LEPT_TRUE, "true", ",")) == LEPT_PARSE_OK or (ret = lept_parse_literal(c, &m->v, LEPT_TRUE, "true", "}")) == LEPT_PARSE_OK){;}
        return ret;
    }else if (*c->json == 'f'){
        if ((ret = lept_parse_literal(c, &m->v, LEPT_FALSE, "false", ",")) == LEPT_PARSE_OK or (ret = lept_parse_literal(c, &m->v, LEPT_FALSE, "false", "]")) == LEPT_PARSE_OK){;}
        return ret;
    }else if (*c->json == '{'){
        if ((ret = lept_parse_object(c, &m->v, ",")) == LEPT_PARSE_OK or (ret = lept_parse_object(c, &m->v, "}")) == LEPT_PARSE_OK){;}
        return ret;
    }else{
        return LEPT_PARSE_INVALID_VALUE;
    }
}

int lept_parse_object(lept_context* c, lept_value* v, const char* delimeter){
    v->type = LEPT_OBJECT;
    v->u.object.len = 0;
    v->u.object.m = NULL;
    int ret;
    const char* p = c->json;
    lept_member temp;
    
    if (*c->json++ != '{'){
        return LEPT_PARSE_MISS_QUOTATION_MARK;
    }
    while (*c->json != '\0'){
        if (*c->json == ' ' or *c->json == ','){
            c->json ++;
        }else if (*c->json == '\"'){
            if ((ret = lept_parse_object_key(c, &temp)) != LEPT_PARSE_OK){
                return ret;
            }
            lept_parse_whitespace(c);
            if ((ret = lept_parse_object_value(c, &temp)) != LEPT_PARSE_OK){
                return ret;
            }
            lept_extend_object(v, &temp);
        }else if (*c->json == '}'){
            c->json ++;
            lept_parse_whitespace(c);
            if (*c->json++ == *delimeter){
                return LEPT_PARSE_OK;
            }else{
                c->json = p;
                return LEPT_PARSE_INVALID_VALUE;
            }
        }else{
            c->json = p;
            return LEPT_PARSE_INVALID_VALUE;
        }
    }
    return LEPT_PARSE_INVALID_VALUE;
}


char* lept_stringify_extend(string& p, char*s, size_t& len, const char* delimeter){
    if (*delimeter == '\0'){
        s = (char*)realloc(s, len + p.size() + 1);
        memcpy(s+len, p.c_str(), p.size());
        len += p.size();
        s[len] = *delimeter;
    }else{
        s = (char*)realloc(s, len + p.size() + 2);
        memcpy(s+len, p.c_str(), p.size());
        len += p.size();
        s[len++] = *delimeter;
        s[len] = '\0';
    }
    return s;
}

// Stringify Literial.
char* lept_stringify_literal(const lept_value* v, char* s, size_t& len, const char* delimeter){
    string p;
    if (v->type == LEPT_NULL){
        p = "null";
    }else if (v->type == LEPT_TRUE){
        p = "true";
    }else if (v->type == LEPT_FALSE){
        p = "flase";
    }else{
        return s;
    }
    s = lept_stringify_extend(p, s, len, delimeter);
    return s;
}
        
// Stringify Number.
char* lept_stringify_number(const lept_value* v, char* s, size_t& len, const char* delimeter){
    string p = to_string(v->u.n);
    regex pattern1("0+?$"); // If number is float or double, remove the extra zero at the end.
    regex pattern2("[.]$"); // If number is int, remove decimal.
    p = regex_replace(p, pattern1, "");
    p = regex_replace(p, pattern2, "");
    s = lept_stringify_extend(p, s, len, delimeter);
    return s;
}

// Stringify String.
char* lept_stringify_string(const lept_value* v, char* s, size_t& len, const char* delimeter){
    string p(v->u.str.s);
    p = "\"" + p + "\"";
    s = lept_stringify_extend(p, s, len, delimeter);
    return s;
}

// Stringify Array.
char* lept_stringify_array(const lept_value* v, char* s, size_t& len, const char* delimeter){
    char* s2 = (char*)malloc(1);
    s2[0] = '\0';
    size_t size = 0;
    for (size_t i=0; i<v->u.array.len; i++){
        lept_value& temp = v->u.array.e[i];
        if (temp.type == LEPT_NULL or temp.type == LEPT_TRUE or temp.type == LEPT_FALSE){
            s2 = lept_stringify_literal(&temp, s2, size, ",");
        }else if (temp.type == LEPT_NUMBER){
            s2 = lept_stringify_number(&temp, s2, size, ",");
        }else if (temp.type == LEPT_STRING){
            s2 = lept_stringify_string(&temp, s2, size, ",");
        }else if (temp.type == LEPT_ARRAY){
            s2 = lept_stringify_array(&temp, s2, size, ",");
        }else if (temp.type == LEPT_OBJECT){
            s2 = lept_stringify_object(&temp, s2, size, ",");
        }
    }
    string p = s2;
    p = "[" + p.substr(0, p.size()-1) + "]";
    s = lept_stringify_extend(p, s, len, delimeter);
    free(s2);
    return s;
}

// Stringify Object.
char* lept_stringify_object(const lept_value* v, char* s, size_t& len, const char* delimeter){
    char* s2 = (char*)malloc(1);
    s2[0] = '\0';
    size_t size = 0;
    for (size_t i=0; i<v->u.object.len; i++){
        lept_member& temp = v->u.object.m[i];
        s2 = (char*)realloc(s2, size + temp.klen + 4);
        memcpy(s2+size+1, temp.k, temp.klen);
        s2[size] = '\"';
        size = size + temp.klen + 3;
        s2[size] = '\0'; s2[size-1] = ':'; s2[size-2] = '\"';
        
        if (temp.v.type == LEPT_NULL or temp.v.type == LEPT_TRUE or temp.v.type == LEPT_FALSE){
            s2 = lept_stringify_literal(&temp.v, s2, size, ",");
        }else if (temp.v.type == LEPT_NUMBER){
            s2 = lept_stringify_number(&temp.v, s2, size, ",");
        }else if (temp.v.type == LEPT_STRING){
            s2 = lept_stringify_string(&temp.v, s2, size, ",");
        }else if (temp.v.type == LEPT_ARRAY){
            s2 = lept_stringify_array(&temp.v, s2, size, ",");
        }else if (temp.v.type == LEPT_OBJECT){
            s2 = lept_stringify_object(&temp.v, s2, size, ",");
        }
    }
    string p = s2;
    p = "{" + p.substr(0, p.size()-1) + "}";
    s = lept_stringify_extend(p, s, len, delimeter);
    free(s2);
    return s;
}


void lept_free(lept_value* v){
    assert(v != NULL);
    if (v->type == LEPT_NUMBER){
        v->u.n = 0;
    }else if (v->type == LEPT_STRING){
        free(v->u.str.s);
        v->u.str.len = 0;
        v->u.str.s = NULL; // Avoid occuring wild pointer.
    }else if (v->type == LEPT_ARRAY){
        for (int i=static_cast<int>(v->u.array.len-1); i>=0; i--){
            lept_free(&v->u.array.e[i]);
        }
        free(v->u.array.e);
        v->u.array.len = 0;
        v->u.array.e = NULL;
    }else if (v->type == LEPT_OBJECT){
        for (int i=static_cast<int>(v->u.object.len-1); i>=0; i--){
            free(v->u.object.m[i].k);
            v->u.object.m[i].klen = 0;
            lept_free(&v->u.object.m[i].v);
        }
        free(v->u.object.m);
        v->u.object.len = 0;
        v->u.object.m = NULL;
    }else{
        ; // null, true and false;
    }
    v->type = LEPT_NULL;
    return;
}

lept_type lept_get_type(const lept_value* v){
    assert(v != NULL);
    return v->type;
}

double lept_get_number(const lept_value* v){
    assert(v != NULL && v->type == LEPT_NUMBER);
    return v->u.n;
}

char* lept_get_string(const lept_value* v){
    assert(v != NULL && v->type == LEPT_STRING);
    return v->u.str.s;
}
