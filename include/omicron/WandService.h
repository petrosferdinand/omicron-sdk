/**************************************************************************************************
 * THE OMEGA LIB PROJECT
 *-------------------------------------------------------------------------------------------------
 * Copyright 2010-2011		Electronic Visualization Laboratory, University of Illinois at Chicago
 * Authors:										
 *  Alessandro Febretti		febret@gmail.com
 *-------------------------------------------------------------------------------------------------
 * Copyright (c) 2010-2011, Electronic Visualization Laboratory, University of Illinois at Chicago
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of conditions 
 * and the following disclaimer. Redistributions in binary form must reproduce the above copyright 
 * notice, this list of conditions and the following disclaimer in the documentation and/or other 
 * materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF 
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************************************/
#ifndef __WAND_SERVICE_H__
#define __WAND_SERVICE_H__

#include "osystem.h"
#include "Service.h"

namespace omicron
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//! Merges events from a motion capture service and a controller / mouse to create a wand
	//! Input device. WandService emits pointer-type events, and is compatible with all services
	//! and applications consuming pointer events.
	class WandService: public Service
	{
	public:
		// Allocator function
		static WandService* New() { return new WandService(); }

		//! Enumerates the types of controllers that can be used as the wand input device.
		enum InputType { Wiimote, Mouse };

	public:
		WandService();

		virtual void setup(Setting& settings);
		virtual void initialize();
		virtual void poll();
		virtual void dispose();

	private:
		float myUpdateInterval;
		Stopwatch myUpdateTimer;

		int myRaySourceId;
		int myInputSourceId;
		int myOutputSourceId;
		Service* myInputService;
		InputType myInputType;

		Ray myRay;

		// Store fields for input data from controller service.
		bool myButton1State;
		bool myButton2State;
		bool myButtonStateChanged;
		int mySliderState;
		bool myDebug;
	};

}; // namespace omega

#endif