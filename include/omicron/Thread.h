/******************************************************************************
* THE OMICRON SDK
*-----------------------------------------------------------------------------
* Copyright 2010-2015		Electronic Visualization Laboratory,
*							University of Illinois at Chicago
* Authors:
*  Alessandro Febretti		febret@gmail.com
*-----------------------------------------------------------------------------
* Copyright (c) 2010-2015, Electronic Visualization Laboratory,
* University of Illinois at Chicago
* All rights reserved.
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer. Redistributions in binary
* form must reproduce the above copyright notice, this list of conditions and
* the following disclaimer in the documentation and/or other materials provided
* with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*-----------------------------------------------------------------------------
* What's in this file:
* Exposes a few small wrapper classes around tinythreads, that implement basic 
* multithreading support.
******************************************************************************/
#ifndef __THREAD_H__
#define __THREAD_H__

#include "osystem.h"

// Used for lock.
namespace tthread { class mutex; class thread; class condition_variable; };

namespace omicron
{
    ////////////////////////////////////////////////////////////////////////////
    // Lock wrapper class
    class OMICRON_API Lock
    {
    public:
        Lock();
        ~Lock();
        void lock();
        void unlock();

        tthread::mutex* impl() { return myLockImpl; }
    private:
        tthread::mutex* myLockImpl;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Lock wrapper class
    class OMICRON_API Thread
    {
    public:
        Thread();
        ~Thread();
        void start();
        void stop();
        virtual void threadProc() {}

    private:
        tthread::thread* myThreadImpl;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    class AutoLock
    {
    public:
        Lock& l;
        AutoLock(Lock& lock): l(lock) { l.lock(); }
        ~AutoLock() { l.unlock(); }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    class OMICRON_API ThreadEvent
    {
    public:
        ThreadEvent();
        ~ThreadEvent();
        void signal();
        void signalOne();
        void wait();
    private:
        tthread::condition_variable* myCVImpl;
        Lock myLock;
    };
}; // namespace omicron

#endif