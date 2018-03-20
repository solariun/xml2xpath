//
//  XmlLexicalParser.cpp
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


#include "XmlParser.hpp"

#include "Util.hpp"

#include <iostream>
#include <new>


#define LX_OTIONS "!-/=!"
#define LX_DIVISION " \r\n\t"
/*
   Exception Handler
*/


/*
    Lexical Parser Functions
 */

XmlParser::XmlParser ()
{}

XmlParser::XmlParser (istream& isIn) : isIn (isIn)
{}

xmlLexicalITemRet* XmlParser::getNextLexicalItem (xmlLexicalITemRet& xmlLExRet)
{
    string  strData = "";
    
    char    chChar = '\0';
    bool    bAddNext = false;
    
    if (isIn.eof()) return NULL;
    
    while (isIn.good())
    {
        chChar = isIn.get();
        
        //cout << chChar << " tp: " << nType << " : String: [" << strData << "]" <<  " EOF: " << isIn.eof () << endl;
        
        
        if (nType == none_tag && chChar == '<')
        {
            //cout << "Return <" << endl;
            
            strData = chChar;
            
            nType = none_tag;
            return xmlLExRet.assign (open_tag, strData);
        }
        else if (nType == none_tag && chChar == '>')
        {
            //cout << "Return >" << endl;
            
            strData = chChar;
            
            nType = value_tag;
            return xmlLExRet.assign (close_tag, strData);
        }
        else if (nType == value_tag && chChar == '<')
        {
            //cout << "Return >" << endl;
            
            nType = none_tag;
            
            isIn.putback(chChar);
            
            return xmlLExRet.assign (close_tag, strData);
        }
        else if (nType == none_tag && chChar == '=')
        {
            //cout << "Return =" << endl;
            
            strData = chChar;
            
            nType = none_tag;
            return xmlLExRet.assign (equal_tag, strData);
        }
        else if (nType == none_tag && chChar == '"')
        {
            nType = string_qute_tag;
        }
        else if (nType == string_qute_tag && chChar == '"' && bAddNext == false)
        {
            //cout << "Return \"\" string" << endl;
            
            nType = none_tag;
            return xmlLExRet.assign(string_tag, strData);
        }
        else if (nType == string_qute_tag && chChar == '\\' && bAddNext == false)
        {
            bAddNext = true;
        }
        else if (nType == none_tag && !isBetween (chChar, LX_DIVISION, sizeof (LX_DIVISION)-1) )
        {
            //cout << "setting simple string...." << endl;
            
            isIn.putback(chChar);
            
            nType = string_tag;
        }
        else if (nType == string_tag && isBetween(chChar, "<>=\" ", 5))
        {
            if (isBetween(chChar, "<>=\"", 4))
            {
                isIn.putback(chChar);
            }
            
            //cout << "Return simple srtring " << endl;
            
            nType = none_tag;
            return xmlLExRet.assign(string_tag, strData);
        }
        else if (nType == string_qute_tag || nType == string_tag || nType == value_tag)
        {
            if (bAddNext == true) bAddNext = false;
            
            //cout << "adding [" << chChar << "] - type: " << nType << endl;
            
            if (chChar == '\n')
                strData += "\n";
            else if (chChar == '\r')
                strData += "\r";
            else
                strData += chChar;
            
        }
    }
    
    return NULL;
}

xmlLexicalITemRet* XmlParser::getNewxmlLexicalITemRet(xmlElements_t  xmleType, string strValue)
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

//0103182186491
