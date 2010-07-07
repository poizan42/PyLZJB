/**
$Id: wrapper.hpp 2981 2010-06-14 11:08:57Z Bear $

Copyright (c) 2010 Nuwa Information Co., Ltd, All Rights Reserved.

* CDDL HEADER START

The contents of this file are subject to the terms of the
Common Development and Distribution License, Version 1.0 only
(the "License").  You may not use this file except in compliance
with the License.

You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
or http://www.opensolaris.org/os/licensing.
See the License for the specific language governing permissions
and limitations under the License.

When distributing Covered Code, include this CDDL HEADER in each
file and include the License file at usr/src/OPENSOLARIS.LICENSE.
If applicable, add the following below this CDDL HEADER, with the
fields enclosed by brackets "[]" replaced with your own identifying
information: Portions Copyright [yyyy] [name of copyright owner]

* CDDL HEADER END

$Author: Bear $
$Date: 2010-06-14 19:08:57 +0800 (星期一, 14 六月 2010) $
$Revision: 2981 $ 
*/
#ifndef _PYLZJB_WRAPPER_
#define _PYLZJB_WRAPPER_

#include "compress.h"

#ifdef _DEBUG
#include <iostream>
#endif

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_array.hpp>

#include <boost/python.hpp>

#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

namespace bp = boost::python;

typedef boost::shared_ptr<std::string> StringPtr;

// boost::shared_ptr<std::string> -> PyString Converter.
struct StringPointerToPyString {
    static ::PyObject* convert( ::boost::shared_ptr<::std::string> const& p_str ){
        return ::PyString_FromStringAndSize( p_str->data(), p_str->size() );
    }
};


#define COMPRESS_RESERVED_TIMES    1

#define DECOMPRESS_RESERVED_TIMES  128

/**
@name Wrap global functions.
*/
//@{
StringPtr CompressWrap(::std::string const & str, unsigned int reserved = 0){

    StringPtr dstPtr(new std::string);

    Py_BEGIN_ALLOW_THREADS

    if(reserved == 0) {
        reserved = str.size() * COMPRESS_RESERVED_TIMES;
    }

    boost::scoped_array<uchar_t> dst(new uchar_t[reserved]);

    size_t l = compress((void *)str.data(), (void *)dst.get(), str.size());

    dstPtr->assign(
     reinterpret_cast<std::string::const_pointer>(dst.get()), l);

    Py_END_ALLOW_THREADS

    return dstPtr;
}

StringPtr DecompressWrap(::std::string const & str, unsigned int reserved = 0){

    StringPtr dstPtr(new std::string);

    Py_BEGIN_ALLOW_THREADS

    if(reserved == 0) {
        reserved = str.size() * DECOMPRESS_RESERVED_TIMES;    
    }

    boost::scoped_array<uchar_t> dst(new uchar_t[reserved]);

    size_t l = decompress((void *)str.data(), (void *)dst.get(), 
                          str.size(), reserved);

    dstPtr->assign(
     reinterpret_cast<std::string::const_pointer>(dst.get()), l);

    Py_END_ALLOW_THREADS

    return dstPtr;
}
//@}

BOOST_PYTHON_MODULE(PyLZJB){

    { //::compress
    
        typedef ::StringPtr ( *compress_function_type )( ::std::string const &, unsigned int);
        
        bp::def( 
            "compress"
            , compress_function_type( &CompressWrap )
            , ( bp::arg("str"), bp::arg("reserved")=0 ) );
    
    }

    { //::decompress
    
        typedef ::StringPtr ( *decompress_function_type )( ::std::string const &, unsigned int );
        
        bp::def( 
            "decompress"
            , decompress_function_type( &::DecompressWrap )
            , ( bp::arg("str"), bp::arg("reserved")=0 ) );
    
    }

    bp::to_python_converter<::StringPtr, ::StringPointerToPyString>();
}

#endif
