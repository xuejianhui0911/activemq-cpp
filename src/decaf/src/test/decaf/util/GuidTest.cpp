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

#include "GuidTest.h"

#include <decaf/util/Guid.h>

CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::GuidTest );

using namespace std;
using namespace decaf;
using namespace decaf::util;
using namespace decaf::lang;

void GuidTest::test() {

    util::Guid guid;

    guid.createGUID();

    CPPUNIT_ASSERT( guid.toString() == (std::string)guid );

    Guid copy = guid;

    CPPUNIT_ASSERT( guid == copy );
    CPPUNIT_ASSERT( !(guid < copy) );
    CPPUNIT_ASSERT( guid <= copy );
    CPPUNIT_ASSERT( !(guid > copy) );
    CPPUNIT_ASSERT( guid >= copy );

    std::string less = "0f2bd21c-9fee-4067-d739-c4d84a5d7f62";
    std::string more = "1f2bd21c-9fee-4067-d739-c4d84a5d7f62";

    CPPUNIT_ASSERT( less < more );
    CPPUNIT_ASSERT( less <= more );
    CPPUNIT_ASSERT( !(less > more) );
    CPPUNIT_ASSERT( !(less >= more) );

    less = more;

    CPPUNIT_ASSERT( less == more );

    const unsigned char* bytes = guid.toBytes();

    Guid bytesGUID;
    bytesGUID.fromBytes(bytes);

    CPPUNIT_ASSERT( guid == bytesGUID );

    delete [] bytes;

    Guid bytesGUID2;
    bytesGUID2.fromBytes((const unsigned char*)guid);

    CPPUNIT_ASSERT( guid == bytesGUID2 );

    Guid stringGUID(guid.toString());

    CPPUNIT_ASSERT( stringGUID == guid );

    Guid stringGUID2(guid.toString().c_str());

    CPPUNIT_ASSERT( stringGUID2 == guid );
    CPPUNIT_ASSERT( !(stringGUID2 != guid) );
}
