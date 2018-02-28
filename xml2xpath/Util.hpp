//
//  Util.hpp
//  xml2xpath
//
//  Created by GUSTAVO CAMPOS on 26/02/18.
//  Copyright © 2018 GUSTAVO CAMPOS. All rights reserved.
//

#ifndef Util_hpp
#define Util_hpp

#include <stdio.h>

#define VERIFY(x,y, z...) if (!(x)) { ExceptionHandle (__FILE__, __PRETTY_FUNCTION__, __LINE__, #x, y [0] == '\0' ? strerror (errno) : y, ##z); IfException (); throw this;  } else { errno = 0; }



#endif /* Util_hpp */
