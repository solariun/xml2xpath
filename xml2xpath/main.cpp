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

#include "XmlParser.hpp"

using namespace std;





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
    
    ifstream ifFileStream ("/Users/gustavocampos/Library/Developer/Xcode/DerivedData/xml2xpath-dgdhxtmfhjqugkemvbedmvgjcbwp/Build/Products/Debug/teste.xml");
    
    //XmlLexicalParser lexParser (cin);
    XmlParser lexParser (ifFileStream);

    
    xmlLexicalITemRet xmlLexRet;
    
    
    while (lexParser.getNextLexicalItem(xmlLexRet) != NULL){ cout << "Type: " << xmlLexRet.xmleType << " Value: " << xmlLexRet.strValue << endl; };
    
    cout << "Final processing" << endl;
    
    
    return 0;
}
