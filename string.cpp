//
//  String.cpp
//  MSTL
//
//  Created by 오민호 on 2017. 3. 22..
//  Copyright © 2017년 오민호. All rights reserved.
//

#include "String.hpp"

using namespace omh;

String::String() {
    len = 0;
    str = NULL;
}

String::String(const char* str): len(strlen(str)) {
    this->str = new char[len + 1];
    strcpy(this->str, str);
}

String::String(const String& ref): len(ref.len) {
    this->str = new char[len + 1];
    strcpy(this->str, str);
}

String::~String() {
    delete[] str;
}

String& String::operator=(const String& ref) {
    if(str != NULL) delete [] str;
    len = strlen(str);
    this->str = new char[len + 1];
    strcpy(this->str, str);
    return *this;
}

String String::operator+(const String& s) {
    String nstr = this->str;
    nstr+=s;
    return nstr;
}

String& String::operator+=(const String& s) {
//    strncat(this->str, s.str, s.len);
//    this->len += s.len;
    len = len + s.len + 1;
    char* temp = new char[len];
    strcpy(temp, this->str);
    strcat(temp, s.str);
    if(str != NULL)
        delete[] str;
    str = temp;
    return *this;
}
bool String::operator==(const String& s) {
    return !strcmp(this->str, s.str);
}

bool String::operator!=(const String& s) {
    return strcmp(this->str, s.str);
}
