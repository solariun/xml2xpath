//
//  XmlLexicalParser.cpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 14/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "XmlLexicalParser.hpp"



XmlLexicalParser::XmlLexicalParser ()
{
    return;
}

XmlLexicalParser::XmlLexicalParser (istream isIn)
{
    return;
}


XmlLexicalParser::XmlLexicalParserEx::XmlLexicalParserEx () : runtime_error("")
{
}

XmlLexicalParser::XmlLexicalParserEx::XmlLexicalParserEx (uint32_t n32Code, string strMessage) : n32Code(n32Code), strMessage(strMessage), runtime_error(strMessage)
{
}

