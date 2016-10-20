/*
	Opens a shop window with the inventory specified below (w/SFX).

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
*/
// playSound "shopHI";

_nil = createDialog "DWR_ShopClass"; 
ctrlSetText [1000, format ["Funds:      $%1", player getVariable "DWR_PlayerCash"]]; 


_wpnAvail = [
	[300, "hgun_P07_F"], 
	[400, "hgun_ACPC2_F"], 
	[650,"arifle_Mk20C_F"], 
	[900,"srifle_EBR_F"]
];

_magAvail = [
	[20, "9Rnd_45ACP_Mag"], 
	[25, "16Rnd_9x21_Mag"], 
	[35, "30Rnd_556x45_Stanag"], 
	[45, "20Rnd_762x51_Mag"]
];

_wList = [];
for "_i" from 0 to (count _wpnAvail)-1 do {
	_u = _wpnAvail select _i;
	_wTitle = format["$%1 - %2", _u select 0, getText(configFile >>
							  "cfgWeapons" >>
							  (_u select 1) >>
							  "displayName")];
	_wPic = getText(configFile >> "cfgWeapons" >> (_u select 1) >>
			"picture");
	_wDesc = getText(configFile >> "cfgWeapons" >> (_u select 1) >>
			 "Library" >> "libTextDesc");

	_wlist = _wList + [[_u select 1, _wTitle, _wPic, _wDesc, "W",
			    _u select 0]];
};

_mList = [];

for "_i" from 0 to (count _magAvail)-1 do {
	_u = _magAvail select _i;
	_wTitle = format["   $%1 - %2", _u select 0, getText(configFile >>
							     "CfgMagazines" >>
							     (_u select 1) >>
							     "displayName")];
	_wPic = getText(configFile >> "CfgMagazines" >> (_u select 1) >>
			"picture");
	_wDesc = format ["\n\n%1", getText(configFile >> "CfgMagazines" >>
					   (_u select 1) >> "displayName")];

	_wlist = _wList + [[_u select 1, _wTitle, _wPic, _wDesc, "M",
			    _u select 0]];
};

for "_i" from 0 to (count _wList)-1 do {
	_weap = _wList select _i;
	lbAdd [1500, _weap select 1];
	lbSetPicture [1500, _i, _weap select 2];
	lbSetValue [1500, _i, _i];
};


disableSerialization;

_ctrlPic = finddisplay 60684 displayCtrl 1200;
_ctrlCost = findDisplay 60684 displayCtrl 1002;
_ctrlDesc = findDisplay 60684 displayCtrl 1001;


lbSetCurSel [1500, 0];

while {ctrlVisible 1500} do {
	_index = lbCurSel 1500;
	_purchase = false;
	_w = _wList select _index;
	_prc = _w select 5;
	if (player getVariable "DWR_BoughtItem") then {
	   player setVariable ["DWR_BoughtItem", false];
	   if ((_w select 4) == "W") then {
		   _purchase = [_prc, _w] call DWR_fnc_BuyWeapon;}
	   else {
		if ((_w select 4) == "M") then {
			_purchase = [_prc, _w] call DWR_fnc_BuyMagazine;};
		};
	   if (_purchase) then {
	        // ... it worked.
	   }
	   else {
	   	_ctrlCost ctrlSetText format ["!!!  $%1", _prc];
		};
	   ctrlSetText [1000, format ["Funds:      $%1",
				      player getVariable "DWR_PlayerCash"]]; 

	   }
	else {	 
	     _ctrlCost ctrlSetText format ["$%1", _prc];
	     _ctrlPic ctrlSetText (_w select 2);
	     _ctrlDesc ctrlSetText (_w select 3);
	     };
sleep 0.01;	  
};

// playSound "shopBYE";
