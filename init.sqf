#include <desrc\ga.h>  // Currently unused.
#include <include\directed_graph.hpp>
#include <include\randint.hpp>
#include <include\mkcivs.hpp>

if (!isServer) exitWith {};


/* Compile functions in order of call dependence: */
DWR_fnc_BuyWeapon = compile preprocessfile "fnc_BuyWeapon.sqf";
DWR_fnc_BuyMagazine = compile preprocessfile "fnc_BuyMagazine.sqf";

// fnc_rmcivs = compile preprocessfile "rmcivs.sqf";
// fnc_civtriggers = compile preprocessfile "civtriggers.sqf";
//fnc_rebel = compile preprocessfile "rebel.sqf";
//fnc_layAmbush = compile preprocessfile "layAmbush.sqf";



/* Prepare variables for shop usage: */
player setVariable ["DWR_PlayerCash", 1000];
player setVariable ["DWR_BoughtItem", false];
 

execVM "randomWeather.sqf";
([[["sunrise", "sunset"] select floor random 2], []]
 select floor random 2) execVM "randomTime.sqf";
