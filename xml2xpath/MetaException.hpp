//
//  MetaException.hpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 26/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#ifndef MetaException_hpp
#define MetaException_hpp

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class MetaException
{
private:
    uint32_t nExID;
    string   strExText;
    
public:
    MetaException(const uint32_t nExID,  const string&) _NOEXCEPT;
    MetaException(const uint32_t nExID,  const char*) _NOEXCEPT;
    
    MetaException(const MetaException&) _NOEXCEPT;
    MetaException& operator=(const MetaException&) _NOEXCEPT;
    
    ~MetaException() _NOEXCEPT;
    
    virtual const char* what() const _NOEXCEPT;
    
    static void verify(bool nCriteria, const u_int32_t nExID, const char* pszStringValue);
    
    const uint32_t getExceptionID ();
    const char* getExMessage ();
};

#endif /* MetaException_hpp */
