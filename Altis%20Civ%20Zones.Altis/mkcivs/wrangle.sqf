/* Arma 3 Dismissed Unit Bounding Script
	Stops "DISMISSED" units from moving
	 beyond a certain radius.
	Reinitializes the unit/group.
	Break by adding "hasRebelled" flag
	 to leader's namespace.
	Not tested for MP.

  Updated: 9 March 2013

  Author: dwringer

  Arguments: [leader,
	      radius]
*/

private ["_man", "_distMax", "_distRet",
	 "_posStart", "_tx", "_ty", "_td",
	 "_distCurr", "_grpOld", "_grpNew",
	 "_wptReturn", "_wptDismiss"];

_man = _this select 0;
_distMax = _this select 1;
_distRet = _distMax * 0.85;
_posStart = getPos _man;
_man setVariable ["hasRebelled", false];

sleep random 5;

while {!(_man getVariable "hasRebelled")} do {
	_grpOld = group _man;
	_distCurr = 0;
        {
		_tx = (position _x select 0) - (_posStart select 0);
		_ty = (position _x select 1) - (_posStart select 1);
		_td = sqrt ((_tx * _tx) + (_ty * _ty));
		_distCurr = _distCurr max _td;
	} forEach units _grpOld;
	if (_distCurr >= _distMax) then {
		_grpNew = createGroup (side _man);
		_wptReturn = _grpNew addWaypoint [_posStart, 0];
		_wptReturn setWaypointType "MOVE";
		_wptReturn setWaypointSpeed "LIMITED";
		_wptReturn setWaypointCompletionRadius _distRet;
		_wptDismiss = _grpNew addWaypoint [
		        waypointPosition _wptReturn, 0];
		_wptDismiss setWaypointType "DISMISS";
		_wptDismiss setWaypointSpeed "NORMAL";
		_wptDismiss setWaypointCompletionRadius _distRet;
		_grpNew setCurrentWaypoint _wptReturn;
		{[_x] join _grpNew} forEach units (group _man);
		deleteGroup _grpOld;
	};
	sleep 45;
};  
