//
//  MetaException.cpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 26/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#include "MetaException.hpp"
#include <sstream>


MetaException::MetaException(const uint32_t nExID,  const string& strValue) _NOEXCEPT: strExText(strValue), nExID(nExID)
{
    return;
}

MetaException::MetaException(const uint32_t nExID,  const char* pszValue)  _NOEXCEPT: strExText(pszValue), nExID(nExID)
{
    return;
}


MetaException::MetaException(const MetaException& exMetaException) _NOEXCEPT
{
    (*this) =exMetaException;
    return;
}

MetaException& MetaException::operator=(const MetaException& exMetaException) _NOEXCEPT
{
    this->nExID = exMetaException.nExID;
    this->strExText.assign(exMetaException.strExText);
    
    return (*this);
}


MetaException::~MetaException() _NOEXCEPT
{
    return;
}

const char* MetaException::what() const _NOEXCEPT
{
    return "Default Exception mode.";
}


void MetaException::verify(bool bCriteria, const u_int32_t nExID, const char* pszStringValue)
{
    if (!bCriteria)
    {
        std::stringstream strValue;
        
        strValue << "Exception at " <<  __FILE__ << "(" << __LINE__ << "):" << __PRETTY_FUNCTION__ << ":" << nExID << ":" << pszStringValue;
        
        throw new MetaException (nExID, strValue.str());
    }
}


const uint32_t MetaException::getExceptionID ()
{
    return (const uint32_t) nExID;
}

const char* MetaException::getExMessage ()
{
    return strExText.c_str();
}
