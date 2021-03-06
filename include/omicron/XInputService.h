/********************************************************************************************************************** 
 * THE OMICRON PROJECT
 *---------------------------------------------------------------------------------------------------------------------
 * Copyright 2010-2013							Electronic Visualization Laboratory, University of Illinois at Chicago
 * Authors:										
 *  Arthur Nishimoto							anishimoto42@gmail.com
 *---------------------------------------------------------------------------------------------------------------------
 * [LICENSE NOTE]
 *---------------------------------------------------------------------------------------------------------------------
 * Uses the Microsoft XInput API to access game controllers.
 *---------------------------------------------------------------------------------------------------------------------
 * Copyright (c) 2010-2013, Electronic Visualization Laboratory, University of Illinois at Chicago
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
 * following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer. Redistributions in binary form must reproduce the above copyright notice, this list of conditions 
 * and the following disclaimer in the documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************************************************************/
#ifndef __XINPUT__SERVICE_H__
#define __XINPUT__SERVICE_H__

#include "omicron/osystem.h"
#include "omicron/ServiceManager.h"
#include <set>
#include <Windows.h>
#include <XInput.h>

namespace omicron
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class OMICRON_API XInputService: public Service
{
public:
	// Allocator function
	static XInputService* New() { return new XInputService(); }

	enum ControllerType { Invalid, Xbox360, PS3 };
public:
	void setup(Setting& settings);
	virtual void initialize();
	virtual void poll();
	virtual void dispose();
	void checkForNewControllers();

	//! Sets the data update interval, in seconds. This is the interval at which this service will generate events
	//! If set to zero, the service will generate events as fast as possible.
	void setUpdateInterval(float value);
	//! @see setUpdateInterval
	float getUpdateInterval();

private:
	static XInputService* mysInstance;
	float myUpdateInterval;
	float myCheckControllerInterval;

	static int maxControllers;
};

}; // namespace omicron

#endif