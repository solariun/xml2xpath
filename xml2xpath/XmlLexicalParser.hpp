//
//  XmlLexicalParser.hpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 14/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

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
    equal_tag
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

class XmlLexicalParser
{
protected:
    istream& isIn = cin;
    
private:
    XmlLexicalParser ();

    xmlLexicalITemRet* getNewxmlLexicalITemRet(xmlElements_t  xmleType, string strValue);
    
public:
    
    XmlLexicalParser (istream& isIn);
    
    xmlLexicalITemRet* getNextLexicalItem (xmlLexicalITemRet& strData);
    
};


#endif /* XmlLexicalParser_hpp */
