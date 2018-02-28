//
//  XmlLexicalParser.cpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 14/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "XmlLexicalParser.hpp"



XmlLexicalParser::XmlLexicalParser ()
{}

XmlLexicalParser::XmlLexicalParser (istream isIn)
{}


XmlLexicalParserEx::XmlLexicalParserEx () : MetaException(0, "")
{}

XmlLexicalParserEx::XmlLexicalParserEx (uint32_t n32Code, string strMessage) : MetaException(n32Code, strMessage)
{}

