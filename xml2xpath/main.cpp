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
#include <string.h>

#include "XmlParser.hpp"

using namespace std;




int main(int argc, const char * argv[]) {
    
    
    nice (19);
    
    char chCinbuffer [64 * 1024]; // 64k buffer;
    
    /*
     try
     {
     cout << "init text verify " << endl;
     
     jsonParserEx::verify(false, 10, "TESTE ");
     
     }
     catch (MetaException* ex)
     {
     cout << "Exception type (" << ex->what() << ") : " << ex->getExMessage() << endl;
     }
     */
    
    istream* isInput;
    
    ifstream* ifsFile;
    
    if (isatty (fileno(stdin)))
    {
        cout << "This applicacion works with pipe only." << endl;
        
        string strDataBuffer = "";
        
        if (argc != 2)
        {
            cout << "xml to Text - " << to_string(argc) << endl;
            cout << "By Gustavo Campos (2018)" << endl << endl;
            cout << "Use by piping data or ./xml2txt <file>" << endl << endl;
            
            exit (0);
        }
        
        ifsFile = new ifstream (argv[1]);
        //int errn = errno;
        
        if ((ifsFile->rdstate() & std::ifstream::failbit) != 0)
        {
            cerr << "Error: " << strerror(errno);
        }
        
        isInput = ifsFile;
        
    }
    else
    {
        cin.rdbuf()->pubsetbuf(chCinbuffer, sizeof (chCinbuffer));
        
        isInput = &cin;
    }
    
    

    try
    {
        XmlParser lexParser (*isInput);
        
        lexParser.ProcessAndPrintOut ();

    } catch (exception ex)
    {
        cerr << "ERROR:" << ex.what() << endl;
    }
    
    
    cout << "Final processing" << endl;
    
    
    return 0;
}
