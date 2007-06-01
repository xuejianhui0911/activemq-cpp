/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _DECAF_UTIL_GUID_H_
#define _DECAF_UTIL_GUID_H_

#include <decaf/lang/exceptions/RuntimeException.h>
#include <decaf/lang/exceptions/IllegalArgumentException.h>
#include <decaf/util/Config.h>

// #if defined(HAVE_OBJBASE_H) && defined(HAVE_RPCDCE_H)
#if defined(HAVE_OBJBASE_H)
    #include <objbase.h>
    #include <rpcdce.h>
#elif defined(HAVE_UUID_UUID_H)
    #include <uuid/uuid.h>
#elif defined(HAVE_UUID_H)
    #include <uuid.h>
#endif

#include <string>

namespace decaf{
namespace util{

    class DECAF_API Guid
    {
    public:

        Guid();
        Guid(const Guid& source);
        Guid(const std::string& source)
            throw ( lang::exceptions::IllegalArgumentException );
        virtual ~Guid();

        /**
         * Determines if this GUID is null, if so it can be initialized with a
         * call to <code>createGUID</code>.
         * @return true for Null GUID, false otherwise.
         */
        bool isNull() const;

        /**
         * Clears the GUID's current value and sets it to a NULL GUID value
         * will now pass <code>isNull</code>.
         */
        void setNull();

        /**
         * Generate a new GUID which will overwrite any current GUID value
         * @return Reference to this object that now has a new GUID
         */
        Guid& createGUID() throw( lang::exceptions::RuntimeException );

        /**
         * Converts the GUID to a string and returns that string
         * @return a string with this GUID's stringified value
         */
        std::string toString() const throw( lang::exceptions::RuntimeException );

        /**
         * Converts the GUID to a byte array and return a pointer to the
         * new array, called takes ownership and must delete this array
         * when done.
         * @return a byte array with the GUID byte value, size = 16
         */
        const unsigned char* toBytes() const;

        /**
         * Initializes this GUID with the GUID specified in the bytes parameter
         * @return reference to this object.
         */
        Guid& fromBytes( const unsigned char* bytes )
            throw ( lang::exceptions::IllegalArgumentException );

        /**
         * Returns the Size in Bytes of the Raw bytes representation of the
         * GUID.
         * @return size of the Raw bytes representation
         */
        int getRawBytesSize() const;

        /**
         * string type cast operator
         * @returns string representation of this GUID
         */
        operator std::string() const;

        /**
         * byte array cast operator, caller does not own this memeory
         * @returns byte array with the GUID byte value representation
         */
        operator const unsigned char*() const;

        /**
         * Assignment operators
         * @return Reference to this GUID object
         */
        Guid& operator=( const Guid& source )
           throw ( lang::exceptions::IllegalArgumentException );
        Guid& operator=( const std::string& source )
           throw ( lang::exceptions::IllegalArgumentException );

        /**
         * Equality Comparison Operators
         * @return true for equal. false otherwise
         */
        bool operator==( const Guid& source ) const;
        bool operator==( const std::string& source ) const;

        /**
         * Inequality Comparison Operators
         * @return true for equal. false otherwise
         */
        bool operator!=( const Guid& source ) const;
        bool operator!=( const std::string& source ) const;

        /**
         * Less than operators
         * @return true for equal. false otherwise
         */
        bool operator<(const Guid& source) const;
        bool operator<(const std::string& source) const;

        /**
         * Less than or equal to operators
         * @return true for equal. false otherwise
         */
        bool operator<=( const Guid& source ) const;
        bool operator<=( const std::string& source ) const;

        /**
         * Greater than operators
         * @return true for equal. false otherwise
         */
        bool operator>( const Guid& source ) const;
        bool operator>( const std::string& source ) const;

        /**
         * Greater than or equal to operators
         * @return true for equal. false otherwise
         */
        bool operator>=( const Guid& source ) const;
        bool operator>=( const std::string& source ) const;

    public:

        /**
         * Static Guid Creation Method, creates a GUID and returns it as a string
         * @return Guid string.
         */
        static std::string createGUIDString();

        /**
         * Static Guid Create Method, create a GUID and returns the byte representation
         * of the new GUID.
         * @return Guid bytes array, size is 16
         */
        static const unsigned char* createGUIDBytes();

    private:

        // the uuid that this object represents.
        #ifdef HAVE_OBJBASE_H
            ::GUID uuid;
        #elif defined(HAVE_UUID_T)
            uuid_t uuid;
        #else
            #error Platform does not support any of the standard UUID types
        #endif

   };

}}

#endif /*_DECAF_UTIL_GUID_H_*/
