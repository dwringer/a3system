
#define GUI_GRID_X 0
#define GUI_GRID_Y 0
#define GUI_GRID_W 0.025
#define GUI_GRID_H 0.04

class RscTitles {	

class Default 
	{
		idd = -1;
		fadein = 0;
		fadeout = 0;
		duration = 0;
	};

class TalkDisplay {
  idd = 1988;
  onLoad = "uiNamespace setVariable ['TalkDisplay', _this select 0]";
  fadein = 0;
  fadeout = 0;
  duration = 10e10;
  controlsBackground[] = {};
  objects[] = {};
  controls[] = { RscPicture_1200,
		 RscFrame_1800,
		 RscText_1000,
		 RscFrame_1801,
		 RscText_1001 };	
	////////////////////////////////////////////////////////
	// GUI EDITOR OUTPUT START (by dwringer, v1.063, #Zonyjo)
	////////////////////////////////////////////////////////

	class RscPicture_1200: RscPicture
	{
		idc = 1200;
		text = "#(argb,256,256,1)r2t(camrender0,1.0)";
		x = 0.005;
		y = 0.745;
		w = 0.25;
		h = 0.25;
	};
	class RscFrame_1800: RscFrame
	{
		idc = 1800;
		x = 0;
		y = 0.74;
		w = 0.2625;
		h = 0.26;
	};
	class RscText_1000: RscText
	{
		idc = 1000;
		text = ""; //--- ToDo: Localize;
		x = 0.2625;
		y = 0.74;
		w = 0.7375;
		h = 0.04;
		colorBackground[] = { 0.1, 0.1, 0.1, 0.8 }; 
	        colorText[] = { 1, 1, 1, 1 }; 
	};
	class RscFrame_1801: RscFrame
	{
		idc = 1801;
		x = 0.2625;
		y = 0.78;
		w = 0.7375;
		h = 0.22;
	};
	class RscText_1001: RscText
	{
		idc = 1001;
		text = ""; //--- ToDo: Localize;
		x = 0.2625;
		y = 0.78;
		w = 0.7375;
		h = 0.22;
		colorBackground[] = { 0.1, 0.1, 0.1, 0.6 }; 
	        colorText[] = { 1, 1, 1, 1 }; 
		style = ST_MULTI;
		lineSpacing = 1;

	};
	////////////////////////////////////////////////////////
	// GUI EDITOR OUTPUT END
	////////////////////////////////////////////////////////

};
};

class TalkDialog { 
  idd = 1987; 
  movingEnable = false;  // the dialog can be moved with the mouse (see "moving" below) 
  //enableSimulation = false;  // freeze the game 
  controlsBackground[] = { };  // no background controls needed 
  objects[] = { };  // no objects needed 
  controls[] = { RscPicture_1200, 
		 RscText_1000,
		 RscText_1001,
		 RscFrame_1800, 
		 RscFrame_1801,
		 RscButton_1600,
		 RscButton_1601,
		 RscButton_1602,
		 RscButton_1603 }; 


	////////////////////////////////////////////////////////
	// GUI EDITOR OUTPUT START (by dwringer, v1.063, #Rygyke)
	////////////////////////////////////////////////////////

	class RscFrame_1800: RscFrame
	{
		idc = 1800;
		x = 0;
		y = 0;
		w = 0.25;
		h = 0.25;
	};
	class RscPicture_1200: RscPicture
	{
		idc = 1200;
		text = "#(argb,256,256,1)r2t(camrender0,1.0)";
		x = 0.005;
		y = 0.005;
		w = 0.24;
		h = 0.24;
	};
	class RscText_1000: RscText
	{
		idc = 1000;
		text = ""; //--- ToDo: Localize;
		x = 0.25;
		y = 0;
		w = 0.75;
		h = 0.04;
		colorBackground[] = { 0.1, 0.1, 0.1, 0.8 }; 
	        colorText[] = { 1, 1, 1, 1 }; 
	};
	class RscFrame_1801: RscFrame
	{
		idc = 1801;
		x = 0.25;
		y = 0.04;
		w = 0.75;
		h = 0.26;
	};
	class RscText_1001: RscText
	{
		idc = 1001;
		text = ""; //--- ToDo: Localize;
		x = 0.25;
		y = 0.04;
		w = 0.75;
		h = 0.26;
		colorBackground[] = { 0.1, 0.1, 0.1, 0.6 }; 
	        colorText[] = { 1, 1, 1, 1 }; 
		style = ST_MULTI;
		lineSpacing = 1;

	};
	class RscButton_1600: RscButton
	{
		idc = 1600;
		text = "1"; //--- ToDo: Localize;
		x = 0.0125;
		y = 0.26;
		w = 0.05;
		h = 0.04;
		action = "[DialogTarget, 1] call fnc_diagAct";
	};
	class RscButton_1601: RscButton
	{
		idc = 1601;
		text = "2"; //--- ToDo: Localize;
		x = 0.075;
		y = 0.26;
		w = 0.05;
		h = 0.04;
		action = "[DialogTarget, 2] call fnc_diagAct";
	};
	class RscButton_1602: RscButton
	{
		idc = 1602;
		text = "3"; //--- ToDo: Localize;
		x = 0.1375;
		y = 0.26;
		w = 0.05;
		h = 0.04;
		action = "[DialogTarget, 3] call fnc_diagAct";
	};
	class RscButton_1603: RscButton
	{
		idc = 1603;
		text = "X"; //--- ToDo: Localize;
		x = 0.2125;
		y = 0.26;
		w = 0.025;
		h = 0.04;
		action = closeDialog 0;
	};
	////////////////////////////////////////////////////////
	// GUI EDITOR OUTPUT END
	////////////////////////////////////////////////////////


};


