/*
 *	Copyright (C) 2011 by Pandora Robotics Team, Aristotle Univeristy of Thessaloniki, Greece
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in
 *	all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *	THE SOFTWARE.
 */
#include "interface_testing/InterfaceTester.h"
#include "diagnostic_updater/diagnostic_updater.h"

class GenericDiagnostic {
	ros::NodeHandle nh;
	diagnostic_updater::Updater _updater;
	ros::Timer _timer;
	
	public:
	
	GenericDiagnostic(std::string diagnosticName):nh() {
		_updater.add(diagnosticName,this, &GenericDiagnostic::nodeDiagnostics);
		_timer = nh.createTimer(ros::Duration(4),&GenericDiagnostic::diagnosticTimerCallback,this);
		_updater.setHardwareID("none");
		
		
	};

	virtual void nodeDiagnostics(diagnostic_updater::DiagnosticStatusWrapper &stat)=0;

	void diagnosticTimerCallback(const ros::TimerEvent&) {
		
		_updater.update();
	};
};


