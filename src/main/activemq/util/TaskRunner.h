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

#ifndef _ACTIVEMQ_UTIL_TASKRUNNER_H_
#define _ACTIVEMQ_UTIL_TASKRUNNER_H_

#include <activemq/util/Task.h>

#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/Mutex.h>
#include <decaf/lang/Pointer.h>

namespace activemq {
namespace util {

    using decaf::lang::Pointer;

    class TaskRunner : public decaf::lang::Runnable {
    private:

        decaf::util::concurrent::Mutex mutex;

        Pointer<decaf::lang::Thread> thread;

        bool threadTerminated;
        bool pending;
        bool shutDown;

        Task* task;

    public:

        TaskRunner( Task* task );
        virtual ~TaskRunner();

        /**
         * Shutdown after a timeout, does not guarantee that the task's iterate
         * method has completed and the thread halted.
         *
         * @param timeout - Time in Milliseconds to wait for the task to stop.
         */
        void shutdown( unsigned int timeout );

        /**
         * Shutdown once the task has finished and the TaskRunner's thread has exited.
         */
        void shutdown();

        /**
         * Signal the TaskRunner to wakeup and execute another iteration cycle on
         * the task, the Task instance will be run until its iterate method has
         * returned false indicating it is done.
         */
        void wakeup();

    protected:

        virtual void run();

    };

}}

#endif /*_ACTIVEMQ_UTIL_TASKRUNNER_H_*/
