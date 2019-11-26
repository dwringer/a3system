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
#include <include\props.h>

private ["_grpLdr", "_wpnCache", "_grpThis", "_side",
	 "_mgznMen", "_wpnMen", "_mgznLdr", "_wpnLdr",
	 "_grpNew", "_grpOPFOR", "_wptRegroup", "_wptArm",
	 "_wptDummy", "_arms"];

_grpLdr = _this select 0;
_wpnCache = _this select 1;
if (2 < (count _this)) then { _side = _this select 2; }
                       else { _side = OPFOR;          };
_grpThis = group _grpLdr;

_arms = SMALL_ARMS;
if (isClass (configFile >> "CfgPatches" >> "CUP_CAMisc")) then {
	_arms = CUP_SMALL_ARMS;
};

///////////
// WEAPONS:
_wpnLdr = _arms;
_wpnLdr = _wpnLdr select ([count _wpnLdr] call fnc_randint);
_wpnMen = _arms;
_wpnMen = _wpnMen select ([count _wpnMen] call fnc_randint);
//////////

///////
//AMMO:
_mgznLdr = getArray(configfile >> "cfgWeapons" >> _wpnLdr >> "magazines");
_mgznLdr = _mgznLdr select ([count _mgznLdr] call fnc_randint);
_mgznMen = getArray(configfile >> "cfgWeapons" >> _wpnMen >> "magazines");
_mgznMen = _mgznMen select ([count _mgznMen] call fnc_randint);
///////

_wpnLdr = """" + _wpnLdr + """";
_wpnMen = """" + _wpnMen + """";
_mgznLdr = """" + _mgznLdr + """";
_mgznMen = """" + _mgznMen + """";

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

    _grpOPFOR = createGroup %7; 
    if (isNull _grpOPFOR) then {
	createCenter %7;
	_grpOPFOR = createGroup %7;};

    _grp = group this;
    _wptSecure = _grpOPFOR addWaypoint [%1, 0];
    _wptSecure setWaypointCombatMode ""RED"";
    _wptSecure setWaypointBehaviour ([""COMBAT"", ""AWARE""] select 1);
    _wptSecure setWaypointType ""SAD"";
    _wptCycle = _grpOPFOR addWaypoint [%2, 0];
    _wptCycle setWaypointType ""CYCLE"";

    _grpOPFOR setCurrentWaypoint _wptSecure;
    
    (units _grp) joinSilent _grpOPFOR;
    deleteGroup _grp;

    {
        _dude = _x;
        if (%4 == ""CUP_launch_RPG18"") then {
            _dude addBackpack ""B_HuntingBackpack"";
        };
        {
            _dude addMagazine %3;
        } forEach [1,2,3,4];
        _x addWeapon %4;
    } forEach ((units _grpOPFOR) - [leader _grpOPFOR]);
    (leader _grpOPFOR) addBackpack ""B_HuntingBackpack"";
    {(leader _grpOPFOR) addMagazine %5;} forEach [1,2,3,4];
    (leader _grpOPFOR) addWeapon %6; 

    {(leader _grpOPFOR) setSkill [_x select 0, _x select 1];}
    forEach [[""general"",    .8],
	     [""commanding"", .9],
	     [""courage"", .8],
	     [""endurance"", 1.0],
	     [""spotTime"", 1.0],
	     [""aimingSpeed"", 1.0],
	     [""aimingAccuracy"", 1.0],
             [""spotDistance"", 0.7 + random .3],
             [""aimingShake"", 1.0],
             [""reloadSpeed"", 1.0]];
		    
    {private ""_y"";
     _y = _x;
     {_y setSkill [_x select 0, _x select 1];}
     forEach [[""general"", .5 + random .5],
 	      [""commanding"", .65 + random .35],
	      [""courage"", .6 + random .4],
	      [""endurance"", .8],
	      [""spotTime"", 1.0],
	      [""aimingSpeed"", 1.0],
	      [""aimingAccuracy"", .5 + random .3],
              [""spotDistance"", .7 + random .3],
              [""aimingShake"", .5 + random .5],
              [""reloadSpeed"", 1.0]];}
    	forEach ((units _grpOPFOR) - [leader _grpOPFOR]);",
   waypointPosition _wptArm, waypointPosition _wptArm,
   _mgznMen, _wpnMen, _mgznLdr, _wpnLdr, _side
]];

_wptDummy setWaypointType "SAD";
_wptDummy setWaypointCombatMode "RED";

_grpNew setCurrentWaypoint _wptRegroup;  
{[_x] join _grpNew} forEach units (group _grpLdr);

deleteGroup _grpThis;

