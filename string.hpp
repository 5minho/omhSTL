//
//  String.hpp
//  MSTL
//
//  Created by 오민호 on 2017. 3. 22..
//  Copyright © 2017년 오민호. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include <iostream>
#include <cstring>

using namespace std;

namespace omh {
    class String {
    private:
        char* str;
        size_t len;
    public:
        String();
        String(const char* str);
        String(const String& ref);
        String& operator=(const String& ref);
        String operator+(const String& s);
        String& operator+=(const String& s);
        bool operator==(const String& s);
        bool operator!=(const String& s);
        ~String();
        friend std::ostream& operator<<(std::ostream& os, const String& s);
        friend std::istream& operator>>(std::istream& is, String& s);
    };
    
    std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.str;
        return os;
    }
    
    std::istream& operator>>(std::istream& is, String& s) {
        char tmp[100];
        is >> tmp;
        s = String(tmp);
        return is;
    }
}


#endif /* String_hpp */
