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

#ifndef ACTIVEMQ_TRANSPORT_COMMANDREADER_H_
#define ACTIVEMQ_TRANSPORT_COMMANDREADER_H_

#include <activemq/io/Reader.h>
#include <activemq/transport/CommandIOException.h>
#include <activemq/transport/Command.h>

namespace activemq{
namespace transport{

    /**
     * Interface for an object responsible for reading a command
     * from an input stream.
     */
    class CommandReader : public io::Reader
    {
    public:

        virtual ~CommandReader(){}

        /**
         * Reads a command from the given input stream.
         * @return The next command available on the stream.
         * @throws CommandIOException if a problem occurs during the read.
         */
        virtual Command* readCommand()
            throw ( CommandIOException ) = 0;

    };

}}

#endif /*ACTIVEMQ_COMMANDS_COMMANDREADER_H_*/
