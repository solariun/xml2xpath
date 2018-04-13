//
//  XmlLexicalParser.hpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 14/02/18.
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


#ifndef XmlLexicalParser_hpp
#define XmlLexicalParser_hpp

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include "MetaException.hpp"

using namespace std;

/*
 Excpetion habler
 */
class XmlLexicalParserEx : public MetaException
{
private:
    uint32_t n32Code;
    string   strMessage;
    
    XmlLexicalParserEx();
    
public:
    
    XmlLexicalParserEx (uint32_t n32Code, string strMessage);
    
    virtual const char* what() const throw()
    {
        return "XmlLexicalParser::XmlLexicalParserEx";
    }
};


/*
 * ERROR CODES
 */

#define VERIFY_XMLPARSER_ATTR_NOT_COMPLIANCE        100
#define VERIFY_XMLPARSER_CLOSE_TAG_NOT_THE_SAME     101


/*
 * Enum used to typing the Lexical Itens.
 */

enum xmlElements_t
{
    none_tag,
    open_tag,
    end_tag,
    string_tag,
    string_qute_tag,
    close_tag,
    equal_tag,
    value_tag,
    tag_tag
};



/*
 * Type used for returning the Lexical ITem
 */

class xmlLexicalITemRet
{
public:
    xmlLexicalITemRet(xmlElements_t  xmleType, string& strValue) : xmleType(xmleType), strValue(strValue){};
    
    xmlLexicalITemRet(){};

    xmlLexicalITemRet* assign (xmlElements_t  xmleType, string& strValue)
    {
        this->xmleType = xmleType;
        this->strValue = strValue;
        
        return this;
    }
    
    xmlElements_t   xmleType = none_tag;
    string          strValue = "";
};



/*
 * Implementation Prototypes
 */

class XmlParser
{
protected:
    istream& isIn = cin;
    xmlElements_t nType = none_tag;
    
    
private:
    XmlParser ();

    xmlLexicalITemRet* getNextLexicalItem (xmlLexicalITemRet& strData);

    void ProcessAndPrintOut(string strCurTag,  xmlElements_t nType);

public:

    void ProcessAndPrintOut();

    XmlParser (istream& isIn);
    
    
    
};


#endif /* XmlLexicalParser_hpp */
