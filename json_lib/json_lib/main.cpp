#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "leptjson.h"

using std::cout;
using std::endl;

void test_access_literal(const char* json, const char* truth, lept_type type, const char* delimeter){
    lept_value v;
    lept_context c;
    c.json = json;
    size_t ret = lept_parse_literal(&c, &v, type, truth, delimeter);
    cout << ret <<  "\t" << v.type <<endl;
    
    char* s = (char*)malloc(1);
    s[0]='\0';
    size_t len = 0;
    s = lept_stringify_literal(&v, s, len, "\0");
    cout << s << "\t" << len << endl;
    free(s);
    lept_free(&v);
}

void test_access_number(const char* json, const char* delimeter){
    lept_value v;
    lept_context c;
    c.json = json;
    size_t ret = lept_parse_number(&c, &v);
    if (ret == LEPT_PARSE_OK)
        cout << ret << "\t" << v.u.n << endl;
    else
        cout << ret << "\t";
    
    char* s = (char*)malloc(1);
    s[0]='\0';
    size_t len = 0;
    s = lept_stringify_number(&v, s, len, "\0");
    cout << s << "\t" << len << endl;
    free(s);
    lept_free(&v);
}

void test_access_string(const char* json, const char* delimeter){
    lept_value v;
    lept_context c;
    c.json = json;
    int ret = lept_parse_string(&c, &v, delimeter);
    if (ret == LEPT_PARSE_OK)
        cout << ret << "\t" << v.u.str.s << "\t" << c.str << endl;
    else
        cout << ret << "\t" << c.str << endl;
    
    char* s = (char*)malloc(1);
    s[0]='\0';
    size_t len = 0;
    s = lept_stringify_string(&v, s, len, "\0");
    cout << s << "\t" << len << endl;
    free(s);
    lept_free(&v);
}

void print_object(lept_value* v);
void print_array(lept_value* v){
    lept_value temp;
    for (size_t i=0; i<v->u.array.len; i++){
        temp = v->u.array.e[i];
        if (temp.type == LEPT_NULL){
            cout << "null" << ", ";
        }else if (temp.type == LEPT_TRUE){
            cout << "true" << ", ";
        }else if (temp.type == LEPT_FALSE){
            cout << "false" << ", ";
        }else if (temp.type == LEPT_NUMBER){
            cout << temp.u.n << ", ";
        }else if (temp.type == LEPT_STRING){
            cout << temp.u.str.s << ", ";
        }else if (temp.type == LEPT_ARRAY){
            print_array(&temp);
        }else if (temp.type == LEPT_OBJECT){
            print_object(&temp);
        }
    }
}
void test_access_array(const char* json, const char* delimeter){
    lept_value v;
    lept_context c;
    c.json = json;
    size_t ret = lept_parse_array(&c, &v, delimeter);
    cout << ret << "\t";
    print_array(&v);
    cout << endl;

    char* s = (char*)malloc(1);
    s[0]='\0';
    size_t len = 0;
    s = lept_stringify_array(&v, s, len, "\0");
    cout << s << "\t" << len << endl;
    lept_free(&v);
}

void print_object(lept_value* v){
    lept_member temp;
    for (size_t i=0; i<v->u.object.len; i++){
        temp = v->u.object.m[i];
        cout << temp.k << ":";
        if (temp.v.type == LEPT_NULL){
            cout << "null" << ", ";
        }else if (temp.v.type == LEPT_TRUE){
            cout << "true" << ", ";
        }else if (temp.v.type == LEPT_FALSE){
            cout << "false" << ", ";
        }else if (temp.v.type == LEPT_NUMBER){
            cout << temp.v.u.n << ", ";
        }else if (temp.v.type == LEPT_STRING){
            cout << temp.v.u.str.s << ", ";
        }else if (temp.v.type == LEPT_ARRAY){
            print_array(&temp.v);
        }else if (temp.v.type == LEPT_OBJECT){
            print_object(&temp.v);
        }
    }
}

void test_access_object(const char* json, const char* delimeter){
    lept_value v;
    lept_context c;
    c.json = json;
    size_t ret = lept_parse_object(&c, &v, delimeter);
    cout << ret << "\t";
    print_object(&v);
    cout << endl;
    
    char* s = (char*)malloc(1);
    s[0]='\0';
    size_t len = 0;
    s = lept_stringify_object(&v, s, len, "\0");
    cout << s << "\t" << len << endl;
    lept_free(&v);
}


int main() {
    test_access_literal("true ", "true", LEPT_TRUE, "\0");
    test_access_literal("true ,", "true", LEPT_TRUE, ",");
    test_access_literal("tru", "true", LEPT_TRUE, "\0");
    test_access_literal("truee", "true", LEPT_TRUE, "\0");
    test_access_literal("false", "false", LEPT_FALSE, "\0");
    test_access_literal("null ", "null", LEPT_NULL, "\0");

    test_access_number("2324", "\0");
    test_access_number("0.2324", "\0");
    test_access_number("0.456 ", "\0");
    test_access_number("0x2324 ", "\0");

    test_access_string("\"\\u52B2h\\tworld\"\0", "\0");
    test_access_string("\"world\"", "\0");
    test_access_string("\"\\u4fa0h\\tworld\"  ,", ",");

    test_access_array("[2,3]", "\0");
    test_access_array("[[],[3,4]]", "\0");
    test_access_array("[\"abc\", \"cc\", \"sd\", 2.24242]", "\0");
    test_access_array("[\"abc\", \"cc\", \"sd\"]", "\0");
    test_access_array("[\"abc\", \"cc\", [\"d\", 3, 5], true, false,  null, [3, 4,5], true, \"sd\"]", "\0");
    test_access_array("[\"zhang san\", {\"info\": [\"zhang san\", 23, true]}]" , "\0");
    test_access_array("[\"zhang san\", {\"info\": [true]}]" , "\0");

    test_access_object("{\"name\": \"zhang san\"}", "\0");
    test_access_object("{\"name\": \"zhang san\", \"man\":true}", "\0");
    test_access_object("{\"name\": \"zhang san\", \"man\":true, \"age\":  23}", "\0");
    test_access_object("{\"name\": \"zhang san\", \"man\":true, \"age\":  23, \"birth\": [5, 10]}", "\0");
    test_access_object("{\"name\": \"zhang san\", \"man\":true, \"age\":  23, \"birth\": [5, 10], \"friend\":{\"name\": \"li si\"}}", "\0");
    test_access_object("{\"friend\": {\"name\": \"li si\"}}", "\0");
    test_access_object("{\"info\": [\"zhang san\", 23, true]}", "\0");
    return 0;
}
