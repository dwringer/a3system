#define GUI_GRID_X	(0)
#define GUI_GRID_Y	(0)
#define GUI_GRID_W	(0.025)
#define GUI_GRID_H	(0.04)
#define GUI_GRID_WAbs	(1)
#define GUI_GRID_HAbs	(1)

class DWR_ContractClass
{
	idd = 70684;
	movingenable = true;
	class Controls
	{


	////////////////////////////////////////////////////////
	// GUI EDITOR OUTPUT START (by dwringer, v1.062, #Tumify)
	////////////////////////////////////////////////////////
	class DWR_BOX2: Box
	{
		idc = -1;
		text = ""; //--- ToDo: Localize;
		x = 11 * GUI_GRID_W + GUI_GRID_X - 0.016;
		y = 6 * GUI_GRID_H + GUI_GRID_Y - 0.016;
		w = 18 * GUI_GRID_W + 0.032;
		h = 18 * GUI_GRID_H + 0.032;
	};


	class DWR_ContractFrame: RscFrame
	{
		idc = 2800;
		text = "Contract Management:"; //--- ToDo: Localize;
		x = 11 * GUI_GRID_W + GUI_GRID_X;
		y = 6 * GUI_GRID_H + GUI_GRID_Y;
		w = 18 * GUI_GRID_W;
		h = 18 * GUI_GRID_H;
	};
	class DWR_ContractTitle: RscText
	{
		idc = 2000;
		text = "CONTRACT:"; //--- ToDo: Localize;
		colorText[] = {1,1,1,0.9};
		colorBackground[] = {0,0,0,0};
		x = 12 * GUI_GRID_W + GUI_GRID_X;
		y = 7 * GUI_GRID_H + GUI_GRID_Y;
		w = 5.5 * GUI_GRID_W;
		h = 2 * GUI_GRID_H;
	};
	class DWR_ContractPaymentTitle: RscText
	{
		idc = 2001;
		text = "PAYMENT:"; //--- ToDo: Localize;
		colorText[] = {1,1,1,0.9};
		colorBackground[] = {0,0,0,0};
		x = 12 * GUI_GRID_W + GUI_GRID_X;
		y = 11 * GUI_GRID_H + GUI_GRID_Y;
		w = 8 * GUI_GRID_W;
		h = 2.5 * GUI_GRID_H;
	};
	class DWR_ContractRiskTitle: RscText
	{
		idc = 2002;
		text = "RISK ASSESSMENT:"; //--- ToDo: Localize;
		colorText[] = {1,1,1,0.9};
		colorBackground[] = {0,0,0,0};
		x = 12 * GUI_GRID_W + GUI_GRID_X;
		y = 14 * GUI_GRID_H + GUI_GRID_Y;
		w = 8.5 * GUI_GRID_W;
		h = 2 * GUI_GRID_H;
	};
	class DWR_ContractTimeTitle: RscText
	{
		idc = 2003;
		text = "COMPLETE BY:"; //--- ToDo: Localize;
		colorText[] = {1,1,1,0.9};
		colorBackground[] = {0,0,0,0};
		x = 12 * GUI_GRID_W + GUI_GRID_X;
		y = 17 * GUI_GRID_H + GUI_GRID_Y;
		w = 6.5 * GUI_GRID_W;
		h = 1.5 * GUI_GRID_H;
	};
	class DWR_ContractExit: RscButton
	{
		idc = 2600;
		text = "X"; //--- ToDo: Localize;
		x = 24.5 * GUI_GRID_W + GUI_GRID_X;
		y = 21 * GUI_GRID_H + GUI_GRID_Y;
		w = 4 * GUI_GRID_W;
		h = 2.5 * GUI_GRID_H;
	};
	class DWR_ContractAccept: RscButton
	{
		idc = 2601;
		text = "ACCEPT"; //--- ToDo: Localize;
		x = 20 * GUI_GRID_W + GUI_GRID_X;
		y = 21 * GUI_GRID_H + GUI_GRID_Y;
		w = 4 * GUI_GRID_W;
		h = 2.5 * GUI_GRID_H;
	};
	class DWR_ContractDesc: RscText
	{
		idc = 2004;
		text = "This will be the description"; //--- ToDo: Localize;
		colorBackground[] = {0,0,0,0};
		x = 12.5 * GUI_GRID_W + GUI_GRID_X;
		y = 8.5 * GUI_GRID_H + GUI_GRID_Y;
		w = 14.5 * GUI_GRID_W;
		h = 3.5 * GUI_GRID_H;
		style = 0x10;
	};
	class DWR_ContractPay: RscText
	{
		idc = 2005;
		text = "DOLLADOLLA"; //--- ToDo: Localize;
		colorBackground[] = {0,0,0,0};
		colorText[] = {0.8,0.23,0.3,0.84};
		x = 13 * GUI_GRID_W + GUI_GRID_X;
		y = 12.5 * GUI_GRID_H + GUI_GRID_Y;
		w = 11.5 * GUI_GRID_W;
		h = 1.5 * GUI_GRID_H;
	};
	class DWR_ContractRA: RscText
	{
		idc = 2006;
		text = "Low/Med/High/ETC"; //--- ToDo: Localize;
		colorBackground[] = {0,0,0,0};
		x = 13 * GUI_GRID_W + GUI_GRID_X;
		y = 15.5 * GUI_GRID_H + GUI_GRID_Y;
		w = 13 * GUI_GRID_W;
		h = 1 * GUI_GRID_H;
	};
	class RscText_1007: RscText
	{
		idc = 2007;
		text = "Low/Med/High/ETC"; //--- ToDo: Localize;
		colorBackground[] = {0,0,0,0};
		x = 13 * GUI_GRID_W + GUI_GRID_X;
		y = 18 * GUI_GRID_H + GUI_GRID_Y;
		w = 13 * GUI_GRID_W;
		h = 1.5 * GUI_GRID_H;
	};
	////////////////////////////////////////////////////////
	// GUI EDITOR OUTPUT END
	////////////////////////////////////////////////////////
	};
};

class DWR_ShopClass
{
	idd = 60684;
	movingenable = true;
	class Controls
	{

////////////////////////////////////////////////////////
// GUI EDITOR OUTPUT START (by dwringer, v1.062, #Tidomo)
////////////////////////////////////////////////////////

class DWR_BOX: BOX
{
	idc = -1;
	text = ""; //--- ToDo: Localize;
	x = 7 * GUI_GRID_W + GUI_GRID_X  - 0.016;
	y = 9.5 * GUI_GRID_H + GUI_GRID_Y - 0.016;
	w = 26 * GUI_GRID_W + 0.032;
	h = 14 * GUI_GRID_H + 0.032;
};

class DWR_ShopDialog: RscFrame
{
	idc = 1800;
	text = "Purchase Equipment:"; //--- ToDo: Localize;
	x = 7 * GUI_GRID_W + GUI_GRID_X;
	y = 9.5 * GUI_GRID_H + GUI_GRID_Y;
	w = 26 * GUI_GRID_W;
	h = 14 * GUI_GRID_H;
};
class DWR_ShopCancel: RscButton
{
	idc = 1600;
	text = "X"; //--- ToDo: Localize;
	x = 28.5 * GUI_GRID_W + GUI_GRID_X;
	y = 20.5 * GUI_GRID_H + GUI_GRID_Y;
	w = 4 * GUI_GRID_W;
	h = 2.5 * GUI_GRID_H;
	action = "closeDialog 0;";
};
class DWR_ShopBuy: RscButton
{
	idc = 1601;
	text = "BUY"; //--- ToDo: Localize;
	x = 24 * GUI_GRID_W + GUI_GRID_X;
	y = 20.5 * GUI_GRID_H + GUI_GRID_Y;
	w = 4 * GUI_GRID_W;
	h = 2.5 * GUI_GRID_H;
	action = "player setVariable [""DWR_BoughtItem"", true];";
};
class DWR_ShopList: RscListbox
{
	idc = 1500;
	x = 7.5 * GUI_GRID_W + GUI_GRID_X;
	y = 10.5 * GUI_GRID_H + GUI_GRID_Y;
	w = 16 * GUI_GRID_W;
	h = 12.5 * GUI_GRID_H;
};
class DWR_ShopCash: RscText
{
	idc = 1000;
	text = "Funds:";
	x = 24 * GUI_GRID_W + GUI_GRID_X;
	y = 10.5 * GUI_GRID_H + GUI_GRID_Y;
	w = 8 * GUI_GRID_W;
	h = 1 * GUI_GRID_H;
	sizeEx = .8 * GUI_GRID_H;
};
class DWR_ShopPhoto: RscPicture
{
	idc = 1200;
	text = "#(argb,8,8,3)color(0,0,0,1)";
	x = 24.5 * GUI_GRID_W + GUI_GRID_X - 0.042;
	y = 13 * GUI_GRID_H + GUI_GRID_Y - 0.05;
	w = 7 * GUI_GRID_W + 0.06;
	h = 4 * GUI_GRID_H;
};
class DWR_ShopText: RscText
{
	idc = 1001;
	text = "Desc: "; //--- ToDo: Localize;
	colorText[] = {1,1,1,0.9};
	colorBackground[] = {0,0,0,0};
	x = 24 * GUI_GRID_W + GUI_GRID_X - 0.007;
	y = 17.5 * GUI_GRID_H + GUI_GRID_Y - 0.09;
	w = 8.5 * GUI_GRID_W;
	h = 5 * GUI_GRID_H;
	sizeEx = .42 * GUI_GRID_H;
	style = 0x10;

};
class DWR_ShopCost: RscText
{
	idc = 1002;
	text = "COST"; //--- ToDo: Localize;
	colorText[] = {0.8,0.23,0.3,0.84};
	colorBackground[] = {0,0,0,0};
	x = 24.5 * GUI_GRID_W + GUI_GRID_X;
	y = 12 * GUI_GRID_H + GUI_GRID_Y - 0.01;
	w = 7 * GUI_GRID_W;
	h = 1 * GUI_GRID_H;
	style = 0x01;
};
////////////////////////////////////////////////////////
// GUI EDITOR OUTPUT END
////////////////////////////////////////////////////////

	};
};
