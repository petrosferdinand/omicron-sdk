/**************************************************************************************************
* THE OMICRON PROJECT
 *-------------------------------------------------------------------------------------------------
 * Copyright 2010-2012		Electronic Visualization Laboratory, University of Illinois at Chicago
 * Authors:										
 *  Arthur Nishimoto		anishimoto42@gmail.com
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
#ifndef __MS_KINECT_SERVICE_H__
#define __MS_KINECT_SERVICE_H__

#include "omicron/osystem.h"
#include "omicron/ServiceManager.h"

#undef WIN32_LEAN_AND_MEAN // needed to fix syntax errors in NUI headers
#include "windows.h" // needs to be included before NuiApi.h
#include "NuiApi.h"
#include "mskinect/resource.h"

/*
typedef enum XnSkeletonJoint (XnTypes.h - OpenNI)
{
	XN_SKEL_HEAD			= 1,
	XN_SKEL_NECK			= 2,
	XN_SKEL_TORSO			= 3,
	XN_SKEL_WAIST			= 4,

	XN_SKEL_LEFT_COLLAR		= 5,
	XN_SKEL_LEFT_SHOULDER	= 6,
	XN_SKEL_LEFT_ELBOW		= 7,
	XN_SKEL_LEFT_WRIST		= 8,
	XN_SKEL_LEFT_HAND		= 9,
	XN_SKEL_LEFT_FINGERTIP	=10,

	XN_SKEL_RIGHT_COLLAR	=11,
	XN_SKEL_RIGHT_SHOULDER	=12,
	XN_SKEL_RIGHT_ELBOW		=13,
	XN_SKEL_RIGHT_WRIST		=14,
	XN_SKEL_RIGHT_HAND		=15,
	XN_SKEL_RIGHT_FINGERTIP	=16,

	XN_SKEL_LEFT_HIP		=17,
	XN_SKEL_LEFT_KNEE		=18,
	XN_SKEL_LEFT_ANKLE		=19,
	XN_SKEL_LEFT_FOOT		=20,

	XN_SKEL_RIGHT_HIP		=21,
	XN_SKEL_RIGHT_KNEE		=22,
	XN_SKEL_RIGHT_ANKLE		=23,
	XN_SKEL_RIGHT_FOOT		=24	
} XnSkeletonJoint;

enum _NUI_SKELETON_POSITION_INDEX (NuiSensor.h - Kinect for Windows)
    {	NUI_SKELETON_POSITION_HIP_CENTER	= 0,
	NUI_SKELETON_POSITION_SPINE	= 1 ,
	NUI_SKELETON_POSITION_SHOULDER_CENTER	= 2 ,
	NUI_SKELETON_POSITION_HEAD	= 3 ,
	NUI_SKELETON_POSITION_SHOULDER_LEFT	= 4 ,
	NUI_SKELETON_POSITION_ELBOW_LEFT	= 5 ,
	NUI_SKELETON_POSITION_WRIST_LEFT	= 6 ,
	NUI_SKELETON_POSITION_HAND_LEFT	= 7 ,
	NUI_SKELETON_POSITION_SHOULDER_RIGHT	= 8 ,
	NUI_SKELETON_POSITION_ELBOW_RIGHT	= 9 ,
	NUI_SKELETON_POSITION_WRIST_RIGHT	= 10
	NUI_SKELETON_POSITION_HIP_LEFT	= 11 ,
	NUI_SKELETON_POSITION_KNEE_LEFT	= 12 ,
	NUI_SKELETON_POSITION_ANKLE_LEFT	= 13 ,
	NUI_SKELETON_POSITION_FOOT_LEFT	= 14 ,
	NUI_SKELETON_POSITION_HIP_RIGHT	= 15 ,
	NUI_SKELETON_POSITION_KNEE_RIGHT	= 16 ,
	NUI_SKELETON_POSITION_ANKLE_RIGHT	= 17 ,
	NUI_SKELETON_POSITION_FOOT_RIGHT	= 18 ,
	NUI_SKELETON_POSITION_COUNT	= 19
    }

*/

namespace omicron
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MSKinectService: public Service
{
public:
	// Allocator function
	MSKinectService();
	static MSKinectService* New() { return new MSKinectService(); }

public:
	virtual void setup(Setting& settings);
	virtual void initialize();
	virtual void poll();
	virtual void dispose();

	
private:
	HANDLE m_pSkeletonStreamHandle;
    HANDLE m_hNextSkeletonEvent;
	HRESULT CreateFirstConnected();
	void ProcessSkeleton();
	void GenerateMocapEvent( const NUI_SKELETON_DATA&, INuiSensor* );
	void SkeletonPositionToEvent( const NUI_SKELETON_DATA&, Event*, _NUI_SKELETON_POSITION_INDEX );
private:
	MSKinectService* mysInstance;

	static const int        cScreenWidth  = 320;
    static const int        cScreenHeight = 240;

    static const int        cStatusMessageMaxLen = MAX_PATH*2;

	HWND                    m_hWnd;
    bool                    m_bSeatedMode;

	// Current Kinect
    INuiSensor*             m_pNuiSensor;
};

}; // namespace omicron

#endif