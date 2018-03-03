//
//  Util.cpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 26/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "Util.hpp"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>


bool isBetween (char chChar, const char* pszCharList, int32_t nMaxCharList=0)
{
    nMaxCharList--;

    while ((--nMaxCharList) >= 0 && pszCharList [nMaxCharList] != chChar) { /*std::cout << "comparing: " << pszCharList [nMaxCharList+1] << " : " << chChar  << std::endl; */ };
    
    return nMaxCharList < 0 ? false : true;
}

