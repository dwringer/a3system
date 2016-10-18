/* Arma 3 Civilian Rebellion Script
	Turns civilian group led by unit into
	 highly skilled OPFOR.
	Units  move to a defined cache,
	 become armed, and then go into a 
	 combat state.
	Not tested for MP.

  Updated: 24 March 2013

  Author: dwringer

  Arguments: [leader,
	      cache]
*/
#include <include\props.hpp>

private ["_grpLdr", "_wpnCache", "_grpThis", 
	 "_mgznMen", "_wpnMen", "_mgznLdr", "_wpnLdr",
	 "_grpNew", "_grpOPFOR", "_wptRegroup", "_wptArm",
	 "_wptDummy"];

_grpLdr = _this select 0;
_wpnCache = _this select 1;
_grpThis = group _grpLdr;

///////////
// WEAPONS:
_wpnLdr = WEAPON_A;
_wpnMen = WEAPON_B;
//////////

///////
//AMMO:
_mgznLdr = AMMO_A;
_mgznMen = AMMO_B;
///////

{_x allowFleeing 0;} forEach units _grpThis;
{_x setVariable ["hasRebelled", true];} forEach units _grpThis;

/////////
// TIMER:
//sleep (5 + (random 10));
/////////

_grpNew = createGroup (side _grpLdr);
_wptRegroup = _grpNew addWaypoint [position _grpLdr, 0];
_wptArm = _grpNew addWaypoint [position _wpnCache, 0];
_wptDummy = _grpNew addWaypoint [position _wpnCache, 0];
_wptRegroup setWaypointType "MOVE";
_wptRegroup setWaypointBehaviour "AWARE";
_wptArm setWaypointCompletionRadius 2.5;
_wptArm setWaypointType "MOVE";
_wptArm setWaypointBehaviour (["STEALTH", "AWARE"] select 1);
_wptArm setWaypointStatements ["true", format [

   "private [""_grp"", ""_grpOPFOR"", ""_wptCycle"", ""_wptSecure"", ""_dude""];

    _grpOPFOR = createGroup east; 
    if (isNull _grpOPFOR) then {
	createCenter east;
	_grpOPFOR = createGroup east;};

    _grp = group this;
    _wptSecure = _grpOPFOR addWaypoint [position this, 0];
    _wptSecure setWaypointCombatMode ""RED"";
    _wptSecure setWaypointBehaviour ([""COMBAT"", ""AWARE""] select 1);
    _wptSecure setWaypointType ""SAD"";
    _wptCycle = _grpOPFOR addWaypoint [position this, 0];
    _wptCycle setWaypointType ""CYCLE"";

    _grpOPFOR setCurrentWaypoint _wptSecure;
    
    (units _grp) joinSilent _grpOPFOR;
    deleteGroup _grp;

    {_dude = _x; {_dude addMagazine %1;} forEach [1,2,3,4];
    _x addWeapon %2;} forEach ((units _grpOPFOR) - [leader _grpOPFOR]);
    {(leader _grpOPFOR) addMagazine %3;} forEach [1,2,3,4];
    (leader _grpOPFOR) addWeapon %4; 

    {(leader _grpOPFOR) setSkill [_x select 0, _x select 1];}
    forEach [[""general"",    .8],
	     [""commanding"", .8],
	     [""courage"", .8],
	     [""endurance"", 1.0],
	     [""spotTime"", 1.0],
	     [""aimingSpeed"", 1.0],
	     [""aimingAccuracy"", 1.0],
             [""spotDistance"", 0.3],
             [""aimingShake"", 1.0],
             [""reloadSpeed"", 1.0]];
		    
    {private ""_y"";
     _y = _x;
     {_y setSkill [_x select 0, _x select 1];}
     forEach [[""general"", .5 + random .5],
 	      [""commanding"", .35],
	      [""courage"", .3 + random .4],
	      [""endurance"", .8],
	      [""spotTime"", 1.0],
	      [""aimingSpeed"", 1.0],
	      [""aimingAccuracy"", .5 + random .3],
              [""spotDistance"", 1.0],
              [""aimingShake"", .5 + random .3],
              [""reloadSpeed"", 1.0]];}
    	forEach ((units _grpOPFOR) - [leader _grpOPFOR]);",

   _mgznMen, _wpnMen, _mgznLdr, _wpnLdr
]];

_wptDummy setWaypointType "SAD";
_wptDummy setWaypointCombatMode "RED";

_grpNew setCurrentWaypoint _wptRegroup;  
{[_x] join _grpNew} forEach units (group _grpLdr);

deleteGroup _grpThis;

