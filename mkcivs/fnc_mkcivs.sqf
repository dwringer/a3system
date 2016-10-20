/*
	Dynamically spawn civilians in an area.

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
		low :: lower bound of civ group id range
		high :: upper bound of civ group id range
		size :: maximum size of civ groups
		position :: center of spawn area
		radius :: max distance to spawn civilians

	Return:
		true
*/
#include <include\props.hpp>

private ["_lo", "_hi", "_sz", "_p", "_r",
	 "_civs", "_tst", "_center", "_acc",
	 "_ck", "_g", "_r", "_wptDismiss",
	 "_ldr", "_hdg", "_civ", "_i", "_j"];

waitUntil {not Sentinel_mkCivs};
Sentinel_mkCivs = true;

// Initialize
_lo = _this select 0;
_hi = _this select 1;
_sz = _this select 2;
_p  = position (_this select 3);
_r  = _this select 4;

// Available civs:
_civs = CIVILIANS;

// Assert side exists, get sideLogic grp handle
_tst = createGroup civilian;
if (isNull _tst) then {
  _center = createCenter civilian;
  _tst = createGroup _center;};
deleteGroup _tst;
_tst = createGroup sideLogic;

// Make the civs:
_acc = [];
for "_i" from _lo to _hi do {

    // Get non-water position
    _ck = _tst createUnit ["LOGIC", _p, [], _r, "NONE"];
    while {(surfaceIsWater (position _ck))
       || (((getPosATL _ck) select 2) > 1)
       || ((count (nearestObjects [_ck, ["house"], 2])) > 0)} do {
	deleteVehicle _ck;
	_ck = _tst createUnit ["LOGIC", _p, [], _r, "NONE"];};

    // Set up group dismiss waypoint
    _g = createGroup civilian;
    _wptDismiss = _g addWaypoint [(position _ck), 0];
    _wptDismiss setWaypointType "DISMISS";
    _wptDismiss setWaypointSpeed "LIMITED";
    _wptDismiss setWaypointCompletionRadius (2 * _r);
    _g setCurrentWaypoint _wptDismiss;

    // Create group leader
    _ldr = _g createUnit [_civs select (floor random count _civs),
			  (position _ck),
			  [],
			  _r,
			  "NONE"];
    deleteVehicle _ck; // done with check logic
    _ldr setVariable ["civName", format ["civ_%1_1", _i]];
    _acc = _acc + [_ldr];

    // Create group members
    for "_j" from 2 to (random (_sz+1)) do {
	_civ = _g createUnit [_civs select (floor random count _civs), 
			      (position _ldr), 
			      [], 
			      4.2, 
			      "NONE"];
	_civ setVariable ["civName", format ["civ_%1_%2", _i, _j]];
	_hdg = _civ getRelDir (position (_acc select floor random count _acc));
	_civ setDir _hdg;
	_acc = _acc + [_civ];
    };
    
    // Initialize the group
    [_ldr, _r / 2] execVM "mkcivs\wrangle.sqf";};

// Finalize creation
deleteGroup _tst; // done with logic group
{
	_x addEventHandler ["killed", {
		civArray = civArray - [_this select 0];
		civKilled = civKilled + 1;
		hint format ["Civilian casualties: %1", civKilled];
        }];
} forEach _acc;
civArray = civArray + _acc;
Sentinel_mkCivs = false;
true; // RETURN
