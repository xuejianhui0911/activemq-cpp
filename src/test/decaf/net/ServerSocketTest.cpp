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

#include "ServerSocketTest.h"

#include <decaf/net/Socket.h>
#include <decaf/net/ServerSocket.h>
#include <decaf/lang/Thread.h>

using namespace decaf;
using namespace decaf::net;
using namespace decaf::io;
using namespace decaf::lang;
using namespace decaf::lang::exceptions;

////////////////////////////////////////////////////////////////////////////////
namespace {

    class SocketClient : public Runnable {
    public:

        Socket* clientS;
        int port;

        SocketClient( int port ) : Runnable(), clientS( NULL ), port( port ) {

        }

        virtual void run() {

            try{
                Thread::sleep( 1000 );
                this->clientS = new Socket( "127.0.0.1", port );
                Thread::sleep( 1000 );
            } catch( InterruptedException& ex ) {
            } catch( Exception& ex ) {
                ex.printStackTrace();
                if( clientS != NULL ) {
                    delete clientS;
                }
            }
        }

    };

    SocketClient* client = NULL;
}

////////////////////////////////////////////////////////////////////////////////
ServerSocketTest::ServerSocketTest() {
}

////////////////////////////////////////////////////////////////////////////////
ServerSocketTest::~ServerSocketTest() {
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::setUp() {

    this->ssconn = NULL;
    this->theThread = NULL;

    // Clear global client value
    client = NULL;
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::tearDown() {

    if( this->theThread != NULL ) {
        this->theThread->join( 3000 );
    }

    delete this->theThread;

    if( this->ssconn != NULL ) {
        ssconn->close();
        delete ssconn;
    }

    // Delete the global client if it exists.
    delete client;
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::testConstructor() {

    try {

        ServerSocket s( 0, 10 );
        //s.setSoTimeout( 20000 );
        startClient( s.getLocalPort() );
        this->ssconn = s.accept();

        // DEBUG
        Thread::sleep( 1000 );

    } catch( InterruptedException& ex ) {
    } catch( Exception& ex ) {
        ex.printStackTrace();
        throw ex;
    }

    try{
        ServerSocket s1(0);

        CPPUNIT_ASSERT_THROW_MESSAGE(
            "Should throw an IOException",
            ServerSocket s2( s1.getLocalPort() ),
            IOException );

    } catch( Exception& ex ) {
        ex.printStackTrace();
        throw ex;
    }

    ServerSocket s2(0);
    int port = s2.getLocalPort();
    s2.close();
    ServerSocket s3( port );
    s3.close();
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::testClose() {

    ServerSocket s(0);
    s.close();

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should throw an IOException",
        s.accept(),
        IOException );
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::testGetLocalPort() {

    int port = 23232;
    int actual = 0;

    // Try the selected port, if it doesn't work don't complain just give up.
    try{

        ServerSocket s( port );
        actual = s.getLocalPort();

    } catch( IOException& ex ) {
        return;
    }

    CPPUNIT_ASSERT_EQUAL( port, actual );
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::testGetSoTimeout() {

    ServerSocket s(0);
    s.setSoTimeout( 100 );

    CPPUNIT_ASSERT_EQUAL_MESSAGE( "SO_TIMEOUT doesnt match what was set.", 100, s.getSoTimeout() );
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::testGetReuseAddress() {

    try{
        ServerSocket s;
        s.setReuseAddress( true );
        CPPUNIT_ASSERT_EQUAL_MESSAGE( "Reuse Address doesnt match what was set.", true, s.getReuseAddress() );
        s.setReuseAddress( false );
        CPPUNIT_ASSERT_EQUAL_MESSAGE( "Reuse Address doesnt match what was set.", false, s.getReuseAddress() );
    } catch( Exception& ex ) {
        ex.printStackTrace();
        throw ex;
    }
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::testGetReceiveBufferSize() {

    try{
        ServerSocket s;
        //CPPUNIT_ASSERT_MESSAGE( "Receive Buffer should never be zero.", 0 != s.getReceiveBufferSize() );
        //CPPUNIT_ASSERT_MESSAGE( "Receive Buffer should never be negative.", 0 < s.getReceiveBufferSize() );
    } catch( Exception& ex ) {
        ex.printStackTrace();
        throw ex;
    }
}

////////////////////////////////////////////////////////////////////////////////
void ServerSocketTest::startClient( int port ) {

    client = new SocketClient( port );

    theThread = new Thread( client );
    theThread->start();

    try {
        Thread::sleep( 1000 );
    } catch( InterruptedException& e ) {
        CPPUNIT_FAIL( std::string( "Exception during startClinet()" ) + e.getMessage() );
    }
}
