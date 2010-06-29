/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <activemq/wireformat/openwire/marshal/generated/ActiveMQBytesMessageMarshaller.h>

#include <activemq/commands/ActiveMQBytesMessage.h>
#include <activemq/exceptions/ActiveMQException.h>
#include <decaf/lang/Pointer.h>

//
//     NOTE!: This file is autogenerated - do not modify!
//            if you need to make a change, please see the Java Classes in the
//            activemq-core module
//

using namespace std;
using namespace activemq;
using namespace activemq::exceptions;
using namespace activemq::commands;
using namespace activemq::wireformat;
using namespace activemq::wireformat::openwire;
using namespace activemq::wireformat::openwire::marshal;
using namespace activemq::wireformat::openwire::utils;
using namespace activemq::wireformat::openwire::marshal::generated;
using namespace decaf;
using namespace decaf::io;
using namespace decaf::lang;

///////////////////////////////////////////////////////////////////////////////
DataStructure* ActiveMQBytesMessageMarshaller::createObject() const {
    return new ActiveMQBytesMessage();
}

///////////////////////////////////////////////////////////////////////////////
unsigned char ActiveMQBytesMessageMarshaller::getDataStructureType() const {
    return ActiveMQBytesMessage::ID_ACTIVEMQBYTESMESSAGE;
}

///////////////////////////////////////////////////////////////////////////////
void ActiveMQBytesMessageMarshaller::tightUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn, BooleanStream* bs ) {

    try {

        MessageMarshaller::tightUnmarshal( wireFormat, dataStructure, dataIn, bs );

        ActiveMQBytesMessage* info =
            dynamic_cast<ActiveMQBytesMessage*>( dataStructure );
        info->beforeUnmarshal( wireFormat );


        info->afterUnmarshal( wireFormat );
    }
    AMQ_CATCH_RETHROW( decaf::io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, decaf::io::IOException )
    AMQ_CATCHALL_THROW( decaf::io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
int ActiveMQBytesMessageMarshaller::tightMarshal1( OpenWireFormat* wireFormat, DataStructure* dataStructure, BooleanStream* bs ) {

    try {

        ActiveMQBytesMessage* info =
            dynamic_cast<ActiveMQBytesMessage*>( dataStructure );

        info->beforeMarshal( wireFormat );
        int rc = MessageMarshaller::tightMarshal1( wireFormat, dataStructure, bs );

        return rc + 0;
    }
    AMQ_CATCH_RETHROW( decaf::io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, decaf::io::IOException )
    AMQ_CATCHALL_THROW( decaf::io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ActiveMQBytesMessageMarshaller::tightMarshal2( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataOutputStream* dataOut, BooleanStream* bs ) {

    try {

        MessageMarshaller::tightMarshal2( wireFormat, dataStructure, dataOut, bs );

        ActiveMQBytesMessage* info =
            dynamic_cast<ActiveMQBytesMessage*>( dataStructure );
        info->afterMarshal( wireFormat );
    }
    AMQ_CATCH_RETHROW( decaf::io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, decaf::io::IOException )
    AMQ_CATCHALL_THROW( decaf::io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ActiveMQBytesMessageMarshaller::looseUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn ) {

    try {

        MessageMarshaller::looseUnmarshal( wireFormat, dataStructure, dataIn );
        ActiveMQBytesMessage* info =
            dynamic_cast<ActiveMQBytesMessage*>( dataStructure );
        info->beforeUnmarshal( wireFormat );
        info->afterUnmarshal( wireFormat );
    }
    AMQ_CATCH_RETHROW( decaf::io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, decaf::io::IOException )
    AMQ_CATCHALL_THROW( decaf::io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ActiveMQBytesMessageMarshaller::looseMarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataOutputStream* dataOut ) {

    try {

        ActiveMQBytesMessage* info =
            dynamic_cast<ActiveMQBytesMessage*>( dataStructure );
        info->beforeMarshal( wireFormat );
        MessageMarshaller::looseMarshal( wireFormat, dataStructure, dataOut );
        info->afterMarshal( wireFormat );
    }
    AMQ_CATCH_RETHROW( decaf::io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, decaf::io::IOException )
    AMQ_CATCHALL_THROW( decaf::io::IOException )
}

