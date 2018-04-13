//
//  Util.cpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 26/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//
/*
 MIT License
 
 Copyright (c) [year] [fullname]
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */


#include "Util.hpp"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <string.h>


bool isBetween (char chChar, const char* pszCharList)
{
    if (pszCharList == nullptr) return false;
    
    int32_t nMaxCharList=(int32_t) strlen(pszCharList);
    
    while (nMaxCharList >= 0 && pszCharList [nMaxCharList] != chChar)
    {
        //std::cout << "comparing: (" << nMaxCharList<< ") [" << (int) pszCharList [nMaxCharList+1] << "] [" << (int) chChar  <<  "]" << std::endl;
        nMaxCharList--;
    };
    
    //std::cout << "Returning at: " << nMaxCharList << std::endl;
    
    return nMaxCharList < 0 ? false : true;
}


std::string& getPathBasename (std::string strPath, std::string& strReturn)
{
    //std::cerr << __FUNCTION__ << ":" << __LINE__ << ":" << strPath << std::endl;
    
    std::size_t found = strPath.find_last_of("/\\");
    
    if (found == std::string::npos)
    {
        strReturn = "";
    }
    else
    {
        strReturn = strPath.substr(found+1);
    }
    
    return strReturn;
}

std::string& popPath  (std::string& strPath)
{
    size_t nLastSlash = strPath.find_last_of("/");
    
    if (nLastSlash == std::string::npos)
        return strPath;
    
    //cerr << endl;
    //cerr << "Actual Path: [" << strPath << "(" << strPath.size() << ", " << nLastSlash << "," << strPath [nLastSlash] << ")" << endl;
    
    strPath.resize(nLastSlash);
    
    //cerr << "Previous accessed: [" << strPath << "]" << endl << endl;
    
    return strPath;
}
