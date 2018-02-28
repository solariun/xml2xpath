//
//  main.cpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 09/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

#include "XmlLexicalParser.hpp"

using namespace std;



string* getStdinLine (string& strData)
{
    char chData;
    
    strData.clear();
    
    if (cin.eof())
        return NULL;
    
    while (!cin.eof() && (chData = cin.get()) && chData != '\n')
    {
        if (chData == '\t' || chData >= ' ')
        {
            strData.append (sizeof (char), chData);
        }
    }
    
    //cerr << "Reado so far: " << strData.length() << endl;
    
    return &strData;
}


int main(int argc, const char * argv[]) {
    
    nice (19);
    
    char chCinbuffer [64 * 1024]; // 64k buffer;

    /*
    try
    {
        cout << "init text verify " << endl;
        
        XmlLexicalParserEx::verify(false, 10, "TESTE ");
        
    }
    catch (MetaException* ex)
    {
        cout << "Exception type (" << ex->what() << ") : " << ex->getExMessage() << endl;
    }
    */
    
    if (isatty (fileno(stdin)))
    {
        cout << "This applicacion works with pipe only." << endl;
    }
    
    cin.rdbuf()->pubsetbuf(chCinbuffer, sizeof (chCinbuffer));
    
    string strDataBuffer = "";
    
    
    cout << "Final processing" << endl;
    
    
    return 0;
}
