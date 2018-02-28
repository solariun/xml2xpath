//
//  XmlLexicalParser.cpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 14/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "XmlLexicalParser.hpp"

#include "Util.hpp"


#include <new>;


#define LX_OTIONS "!-/=!"
/*
   Exception Handler
*/


XmlLexicalParserEx::XmlLexicalParserEx () : MetaException(0, "")
{}

XmlLexicalParserEx::XmlLexicalParserEx (uint32_t n32Code, string strMessage) : MetaException(n32Code, strMessage)
{}


/*
    Lexical Parser Functions
 */

XmlLexicalParser::XmlLexicalParser ()
{}

XmlLexicalParser::XmlLexicalParser (istream& isIn) : isIn (isIn)
{}

xmlLexicalITemRet* XmlLexicalParser::getNextLexicalItem (xmlLexicalITemRet& xmlLExRet)
{
    xmlElements_t nType = none_tag;
    string  strData = "";
    
    char    chChar = '\0';
    bool    bAddNext = false;
    
    if (isIn.eof()) return NULL;
    
    while (!isIn.eof())
    {
        chChar = isIn.get();
        
        cout << chChar << " tp: " << nType << " : String: [" << strData << "]" << endl;
        
        
        if (nType == none_tag && chChar == '<')
        {
            cout << "Return <" << endl;
            
            strData.assign("<");
            
            return xmlLExRet.assign (open_tag, strData);
        }
        else if (nType == none_tag && chChar == '>')
        {
            cout << "Return >" << endl;
            
            strData.assign(">");
            
            return xmlLExRet.assign (close_tag, strData);
        }
        else if (nType == none_tag && chChar == '=')
        {
            cout << "Return =" << endl;
            
            strData.assign("-");
            
            return xmlLExRet.assign (equal_tag, strData);
        }
        else if (nType == none_tag && chChar == '"')
        {
            nType = string_qute_tag;
        }
        else if (nType == string_qute_tag && chChar == '"' && bAddNext == false)
        {
            cout << "Return \"\" string" << endl;
            
            return xmlLExRet.assign(string_tag, strData);
        }
        else if (nType == string_qute_tag && chChar == '\\' && bAddNext == false)
        {
            bAddNext = true;
        }
        else if (nType == none_tag && chChar != ' ')
        {
            cout << "setting simple string...." << endl;
            
            isIn.putback(chChar);
            
            nType = string_tag;
        }
        else if (nType == string_tag && isBetween(chChar, "<>=\" ", 5))
        {
            if (isBetween(chChar, "<>=\"", 4))
            {
                isIn.putback(chChar);
            }
            
            cout << "Return simple srtring " << endl;
            
            return xmlLExRet.assign(string_tag, strData);
        }
        else if (nType == string_qute_tag || nType == string_tag)
        {
            if (bAddNext == true) bAddNext = false;
            
            cout << "adding [" << chChar << "]" << endl;
            
            strData += chChar;
        }
    }
    
    return NULL;
}

xmlLexicalITemRet* XmlLexicalParser::getNewxmlLexicalITemRet(xmlElements_t  xmleType, string strValue)
{
    try
    {
        return new xmlLexicalITemRet (xmleType, strValue);
        
    } catch (std::bad_alloc& ex)
    {
        cerr << __PRETTY_FUNCTION__ << " exception: " << ex.what();
        
        throw ex;
    }
    
    return NULL;
}


