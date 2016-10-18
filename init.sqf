#include <desrc\ga.h>

if (!isServer) exitWith {};

civArray = [];
civKilled = 0;

fnc_civLeaders = compile preprocessfile "civLeaders.sqf";

fnc_logarithm = compile preprocessfile "logarithm.sqf";
fnc_bits2int = compile preprocessfile "bits2int.sqf";
fnc_randint = compile preprocessfile "randint.sqf";


fnc_mkcivs = compile preprocessfile "mkcivs.sqf";
fnc_rmcivs = compile preprocessfile "rmCivs.sqf";
Sentinel_mkCivs = false;
Bool_civSpawn_0_3 = false;
Bool_civSpawn_4_7 = false;
Bool_civSpawn_8_11 = false;
Bool_civSpawn_12_15 = false;

//fnc_rebel = compile preprocessfile "rebel.sqf";
//fnc_layAmbush = compile preprocessfile "layAmbush.sqf";

player setVariable ["DWR_PlayerCash", 1000];
player setVariable ["DWR_BoughtItem", false];
 
DWR_fnc_BuyWeapon = compile preprocessfile "DWR_fnc_BuyWeapon.sqf";
DWR_fnc_BuyMagazine = compile preprocessfile "DWR_fnc_BuyMagazine.sqf";

execVM "randomWeather.sqf";
([[["sunrise", "sunset"] select floor random 2], []]
 select floor random 2) execVM "randomTime.sqf";


/*
[] spawn {
	_grp = group campMan;
	while {({alive _x} count (units _grp)) > 0} do {
		sleep 4.20;};
	hint "MISSION SUCCESS\nFunds Deposited: $600";
	player setVariable ["DWR_PlayerCash",
			    600 + (player getVariable "DWR_PlayerCash")];
};
*/
