#define WAYPOINT_PARAMETERS ["_behavior",		\
			     "_combat_mode",		\
			     "_completion_radius",	\
			     "_description",		\
			     "_formation",		\
			     "_placement_radius",	\
			     "_position",		\
			     "_speed",			\
			     "_statements",		\
			     "_timeout",		\
			     "_type",			\
			     "_visible"]


#define WAYPOINT_FUNCTIONS [["_behavior", "setWaypointBehaviour"],  \
			    ["_combat_mode", "setWaypointCombatMode"],  \
			    ["_completion_radius",  \
			     "setWaypointCompletionRadius"],  \
			    ["_description", "setWaypointDescription"],  \
			    ["_formation", "setWaypointFormation"],  \
			    ["_position", "setWaypointPosition"],  \
			    ["_speed", "setWaypointSpeed"],  \
			    ["_statements", "setWaypointStatements"],  \
			    ["_timeout", "setWaypointTimeout"],  \
			    ["_type", "setWaypointType"],  \
			    ["_visible", "setWaypointVisible"]]


DEFCLASS("Waypoint") (["_self"] + WAYPOINT_PARAMETERS) DO {
	/* Create a waypoint with the appropriate parameters (or nil) */
	private ["_value"];
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "_parameters", _this] call fnc_tell;
	for "_i" from 1 to ((count _this) - 1) do {
		_value = _this select _i;
		if (not isNil "_value") then {
			[_self, "_setf", WAYPOINT_PARAMETERS select (_i - 1),
			 _value]
			 call fnc_tell;
		};
	};
	_self
} ENDCLASS;


DEFMETHOD("Waypoint", "to_group") ["_self", "_group", "_index"] DO {
	/* Render a group waypoint from instance then return it */
	private ["_waypoint", "_value", "_operation", "_parameters"];
	_parameters = [_self getVariable "_position",
		       _self getVariable "_placement_radius"];
	if (not isNil "_index") then {
		if (_index == 0) then {
			_parameters = _parameters + [currentWaypoint _group];
		} else {
			if (_index > 0) then {
				_parameters = _parameters + [_index];
			};
		};
	};
	_waypoint = _group addWaypoint _parameters;
	{
		_value = _self getVariable _x;
		_operation = [_x, WAYPOINT_FUNCTIONS] call fnc_alist_get;
		if ((not isNil "_value") and (not isNil "_function")) then {
			call compile format ["_waypoint %2 %1;",
					     _operation,
					     _value];
		};
	} forEach (WAYPOINT_PARAMETERS - ["_position", "_placement_radius"]);
	_waypoint
} ENDMETHOD;
