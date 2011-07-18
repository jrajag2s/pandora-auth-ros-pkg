/**
  * main function
  * Author: Dimitrios Vitsios
  * Date:  9 March 2011
  * Change History: - 
  */

#define QT_NO_KEYWORDS
/*#include "moveArmGui.h"
#include "signalslib.hpp"
#include <QApplication>
#include "masterGui.h"
#include "mainMotorStateGui.h"
#include "setVehicleSpeedGui.h"
#include "setVecSpeedThread.h"
#include "irGui.h"
#include "sonarGui.h"
#include "co2Gui.h"
#include "thermalGui.h"
#include "butterflyGui.h"
#include "debugText.h"
#include "stateManagerGui.h"
#include "victimsFound.h"
#include "mapThread.h"
#include "sensorsThread.h"
#include "videoStreamThread.h"
#include "displayVideo.h"
#include "mapStreamThread.h"
#include "displayMap.h"
#include "videoStreaming.h"*/
#include "setVecSpeedThread.h"
#include "sensorsThread.h"
#include "videoStreamThread.h"
#include "mapStreamThread.h"
#include "consoleManager.h"
#include "masterGui.h"
#include "geotiffCreator.h"
#include "math.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

QString homeFolderString;
QString curFolderString;

int main(int argc, char *argv[])
{
	//ros::init(argc,argv,"gui");
	
	QApplication app(argc, argv);
	
	
	//Can be used instead of shell export of variable ROS_MASTER_URI
	//setenv("ROS_MASTER_URI","http://localhost:11311",1);
	
	//Setting the ROS_IP variable will force ros master to use this ip instead of
	//trying to resolve the hostname
	//setenv("ROS_IP","192.168.1.6",1);

	ros::init(argc, argv, "gui");
	
	//get home directory name
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	std::string homeFolderStr(homedir);
	homeFolderString = homeFolderStr.c_str();
	
	
	
	//create masterGui Object
	masterGui masterG;		

	curFolderString = app.applicationDirPath();
	curFolderString.remove("/bin");
	
	//display pandora logo
	QImage logo;
	QString logoPath = curFolderString;
	logoPath = logoPath.append("/src/masterGui/pandora_logo.jpg");
	logo.load(logoPath);
	gui->ui.pandoraLogoLabel->setPixmap(QPixmap().fromImage(logo));

	QSize pandoraGuiSize = gui->ui.tabWidget->size();


	//set tab1 background
	QImage backg1;
	QString tab1BackgPath = curFolderString;
	tab1BackgPath = tab1BackgPath.append("/src/masterGui/tab1Background.jpg");
	backg1.load(tab1BackgPath);  
	gui->ui.tab1BackLabel->setPixmap(QPixmap().fromImage(backg1).scaled(pandoraGuiSize.width(), pandoraGuiSize.height()));
	
	//set tab2 background
	QImage backg2;
	QString tab2BackgPath = curFolderString;
	tab2BackgPath = tab2BackgPath.append("/src/masterGui/tab2Background.jpg");
	backg2.load(tab2BackgPath);
	gui->ui.tab2BackLabel->setPixmap(QPixmap().fromImage(backg2).scaled(pandoraGuiSize.width(), pandoraGuiSize.height()));
	
	//set tab3 background
	QImage backg3;
	QString tab3BackgPath = curFolderString;
	tab3BackgPath = tab3BackgPath.append("/src/masterGui/tab3Background.jpg");
	backg3.load(tab3BackgPath);
	gui->ui.tab3BackLabel->setPixmap(QPixmap().fromImage(backg3).scaled(pandoraGuiSize.width(), pandoraGuiSize.height()));
	
	
	consoleManager consManag;
	
	//--- create gui elements ---
	
	stateManagerGui stmanGui;
	butterflyGui btfGui;
	thermalGui thermal;
	
	//optionally enable-disable display of rosout_agg messages in Debug tab
	//debugText dbText;
	
	//start sensors (for mainMotorState, IRs, Sonars, CO2) in a new thread
	sensorsThread sensTh;
	sensTh.moveToThread(&sensTh);
	sensTh.start();
	
	soundTest sndst;
	
	//start "setVehicleSpeedGui" in a new thread
	setVecSpeedThread svsTh;
	svsTh.moveToThread(&svsTh);
	svsTh.start();
	
	//start video streaming in a new thread
	videoStreamThread vidStrTh;
	vidStrTh.moveToThread(&vidStrTh);
	vidStrTh.start();
	displayVideo vidG;


	//draw map using "compressed image" streaming of ROS.
	mapStreaming mapStr;
	displayMap disMap;

	// -- draw map after calling the corresponding services (deprecated). --
	//start map in a new thread
	/*
	mapThread mapTh;
	mapTh.start();
	*/
	
	//arm manipulation
	moveArmGui maGui;

	victimsFound vf;
	semiAutonomousGui smaugui;
	semiAutoMsgPublisher samsgpub;
	
	
	//class for geotiff creation
	geotiffCreator geotCr;
	
	ros::AsyncSpinner spinner(2);
	spinner.start();
	app.exec();

	return 0;
}
