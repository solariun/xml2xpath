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
    start_tag,
    end_tag,
    value_tag,
    close_tag,
    Attr_tag,
    equal_tag,
    string_tag
};



/*
 * Type used for returning the Lexical ITem
 */

typedef struct
{
    xmlElements_t   xmleType;
    string          strValue;
} xmlLexicalITemRet;



/*
 * Implementation Prototypes
 */

class XmlLexicalParser
{
private:
    XmlLexicalParser ();

public:
    
    XmlLexicalParser (istream isIn);
    
    xmlLexicalITemRet getNextLexicalItem ();
};


#endif /* XmlLexicalParser_hpp */
