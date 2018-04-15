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
            
            if (strData.length()>0) return xmlLExRet.assign (string_qute_tag, strData);
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
        else if (nType == none_tag && !isBetween (chChar, LX_DIVISION) )
        {
            //cout << "setting simple string...." << endl;
            
            isIn.putback(chChar);
            
            nType = string_tag;
        }
        else if (nType == string_tag && isBetween(chChar, "<>=\" "))
        {
            if (isBetween(chChar, "<>=\""))
            {
                isIn.putback(chChar);
            }
            
            //cout << "Return simple srtring " << endl;
            
            nType = none_tag;
            return xmlLExRet.assign(string_tag, strData);
        }
        else if (nType == string_qute_tag || nType == string_tag || nType == value_tag)
        {
            if (! (strData.length() == 0 && chChar <= ' '))
            {
                if (bAddNext == true) bAddNext = false;
                
                //cout << "adding [" << chChar << "] - type: " << nType << endl;
                
                if (chChar == '\n')
                    strData += "\\n";
                else if (chChar == '\r')
                    strData += "\\r";
                else
                    strData += chChar;
            }
        }
    }
    
    return NULL;
}


void XmlParser::ProcessAndPrintOut()
{
    ProcessAndPrintOut("", none_tag);
}


void XmlParser::ProcessAndPrintOut(string strPath, xmlElements_t nType)
{
    if (strPath.length() > 0)
    {
        TRACE << endl << "ENTERING NEW LEVEL: " << strPath << endl;
        string strBasename = "";
        size_t nLen;
        
        if ((nLen = strPath.find("![")) != string::npos)
        {
            strBasename = strPath.substr(nLen);
            strPath = strPath.substr(0, nLen-1);
            
            
            cout << strPath << "=" << strBasename << endl;
            
            return;
        }
    }
    
    
    
    try
    {
        //XmlLexicalParser lexParser (cin);
        xmlLexicalITemRet xmlLexRet;
        
        string strAttributeName = "";
        
        bool boolHasData = false;
        
        while (getNextLexicalItem(xmlLexRet) != NULL)
        {
            TRACE << "Type: " << xmlLexRet.xmleType << " Value: " << xmlLexRet.strValue << endl;
            
            if (nType == none_tag)
            {
                if (xmlLexRet.xmleType == open_tag)
                {
                    nType = open_tag;
                    boolHasData = false;
                }
            }
            else if (nType == tag_tag)
            {
                if (xmlLexRet.xmleType == string_tag)
                {
                    if (strAttributeName.length() == 0)
                    {
                        strAttributeName = xmlLexRet.strValue;
                    }
                    else
                    {
                        cout << strPath << "@" << strAttributeName << "=" << endl;
                        strAttributeName = "";
                        nType  = tag_tag;
                    }
                }
                else if (xmlLexRet.xmleType == equal_tag)
                {
                    nType = equal_tag;
                }
                else if (xmlLexRet.xmleType == close_tag)
                {
                    string strBasename = "";
                    
                    if (getPathBasename(strPath, strBasename).find_last_of("?[") !=  string::npos || strAttributeName.find_last_of("?/") != string::npos)
                    {
                        return;
                    }
                    
                    nType = close_tag;
                }
            }
            else if (nType == close_tag)
            {
                if (xmlLexRet.xmleType == string_qute_tag)
                {
                    cout << strPath << "=" << xmlLexRet.strValue << endl;
                    
                    strAttributeName="";
                    
                    nType = none_tag;
                }
                else if (xmlLexRet.xmleType == open_tag)
                {
                    cout << "OPEN " << strPath << endl;
                    nType = end_tag;
                }
            }
            else if (nType == equal_tag && xmlLexRet.xmleType == string_tag)
            {
                if (strAttributeName.length() == 0)
                {
                    ASSERT_TEXT (strAttributeName.length() == 0, VERIFY_XMLPARSER_ATTR_NOT_COMPLIANCE, "Error, Attribute not compliance.");
                    
                    continue;
                }
                
                cout << strPath << "@" << strAttributeName << "=" << xmlLexRet.strValue << endl;
                
                strAttributeName="";
                
                nType = tag_tag;
            }
            else if ((nType == open_tag || nType == end_tag) && xmlLexRet.xmleType == string_tag)
            {
                if (xmlLexRet.strValue[0] == '/')
                {
                    string strBasename = "";
                    
                    do getPathBasename(strPath, strBasename); while (strBasename.find_last_of("!?") != string::npos);
                    
                    
                    TRACE << "PATH: [" << strPath <<"] Basename: [" << strBasename << "]" << endl;
                    
                    
                    ASSERT_TEXT(xmlLexRet.strValue.substr(1).compare (strBasename) == 0, VERIFY_XMLPARSER_CLOSE_TAG_NOT_THE_SAME, (_str + "Close TAG: " + xmlLexRet.strValue + " is not the same as the start (" + strBasename + ")").c_str());
                    
                    
                    return;
                }
                else if (isBetween(xmlLexRet.strValue[0], "@#$%^&*()-_+={}[]|/><.,'") == false)
                {
                    nType = tag_tag;

                    
                    if (strPath.find_last_of("?!") !=  string::npos)
                    {
                        TRACE << "Before Pop: " << strPath << endl;
                        popPath(strPath);
                        TRACE << "After  Pop: " << strPath << endl;
                    }
                     
                    
                    ProcessAndPrintOut(strPath + "/" + xmlLexRet.strValue, nType);
                    
                    TRACE << "Returning path: " << strPath << endl;
                    
                    nType = none_tag;
                }
                else
                {
                    nType = tag_tag;
                }
            }
        };
        
    } catch (std::bad_alloc& ex)
    {
        TRACE << __PRETTY_FUNCTION__ << " exception: " << ex.what();
        
        throw ex;
    }

    
    return;
}

//0103182186491
