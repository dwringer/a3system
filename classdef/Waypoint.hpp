////////////////////////////////// UNTESTED ///////////////////////////////////
////////////////////////////////// UNTESTED ///////////////////////////////////
////////////////////////////////// UNTESTED ///////////////////////////////////
#define WAYPOINT_PARAMETERS ["_self",  \
			     "_behavior",		\
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
			    ["_speed", "setWaypointSpeed"],  \
			    ["_statements", "setWaypointStatements"],  \
			    ["_timeout", "setWaypointTimeout"],  \
			    ["_type", "setWaypointType"],  \
			    ["_visible", "setWaypointVisible"]]


DEFCLASS("Waypoint") WAYPOINT_PARAMETERS DO {
	/* Create a waypoint with the appropriate parameters (or nil) */
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "_parameters",
	 [WAYPOINT_PARAMETERS, 1, 0] call fnc_subseq] call fnc_tell;
	{
		call compile format ["
                        if (not isNil ""%1"") then {
                                [_self, ""_setf"", ""%1"", %1] call fnc_tell;
                        };
                ", _x]
	} forEach (_self getVariable "_parameters");
	_self
} ENDCLASS;


DEFMETHOD("Waypoint", "add_to_group") ["_self", "_group"] DO {
	/* Render a group waypoint from instance then return it */
	private ["_waypoint", "_value", "_operation"];
	_waypoint = _group addWaypoint [_self getVariable "_position",
					_self getVariable "_placement_radius"];
	{
		_value = _self getVariable _x;
		_operation = [_x, WAYPOINT_FUNCTIONS] call fnc_alist_get;
		if ((not isNil "_value") and (not isNil "_function")) then {
			call compile format ["_waypoint %2 %1;",
					     _operation,
					     _value];
		};
	} forEach ((_self getVariable "_parameters") -
		   ["_position", "_placement_radius"]);
	_waypoint
} ENDMETHOD;
////////////////////////////////// UNTESTED ///////////////////////////////////
////////////////////////////////// UNTESTED ///////////////////////////////////
////////////////////////////////// UNTESTED ///////////////////////////////////
