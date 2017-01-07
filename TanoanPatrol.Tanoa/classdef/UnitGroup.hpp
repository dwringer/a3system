/*
  UnitGroup class
    :: UnitGroup -> ObjectRoot

  Methods:
    center_pos    :: Get the mean position of all group units
    add unit      :: Add a unit to group
    remove unit   :: Remove a unit from group
    groups        :: Return list of in-game groups represented
    move          :: Move to a position while blocking [[use fnc_tells]]
    sequester     :: Record group structure and loadouts, then despawn units
    desequester   :: Respawn sequestered units into cloned groups w/o waypoints
    timed_patrol  :: Run BIS_fnc_taskPatrol for a set duration, then move back

      This is an abstraction to represent a group of units.  This is distinct
  from unit groups in the typical sense - these groups exist independently and
  are commanded separately through the class method interface. (TBD)

  Example:
    uGrp = ["UnitGroup"] call fnc_new;
    [uGrp, "add", player] call fnc_tell;
    [uGrp, "add", man_1] call fnc_tell;
    [uGrp, "add", man_2] call fnc_tell;

    hint str ([uGrp, "_getf", "units"] call fnc_tell)
    // ... outputs [<player name>, man_1, man_2]
  
    hint str ([uGrp, "center_pos"] call fnc_tell
    // ... outputs mean position vector from all units
*/

DEFCLASS("UnitGroup") ["_self"] DO {
	/* A group abstraction - distinct from Groups in the engine */
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "units", []] call fnc_tell;
	_self
} ENDCLASS;


DEFMETHOD("UnitGroup", "center_pos") ["_self"] DO {
	/* Get the mean position of all units in this UnitGroup */
	private ["_positions", "_center", "_alen", "_comp"];
	_positions = [[["_u"], {position _u}] call fnc_lambda,
		      [_self, "_getf", "units"] call fnc_tell] call fnc_map;
	_alen = count _positions;
	_center = [];
	for "_i" from 0 to 2 do {
		_comp = 0;
		for "_j" from 0 to (_alen - 1) do {
			_comp = _comp + ((_positions select _j) select _i);
		};
		_center = _center + [_comp / _alen];
	};
	_center
} ENDMETHOD;


DEFMETHOD("UnitGroup", "add") ["_self", "_unit"] DO {
	/* Add a unit to this UnitGroup */
	[_self, "_push_attr", "units", _unit] call fnc_tell;
	[_self, "_getf", "units"] call fnc_tell
} ENDMETHOD;


DEFMETHOD("UnitGroup", "remove") ["_self", "_unit"] DO {
	/* Remove a unit from this UnitGroup */
	private ["_units"];
	_units = [_self, "_getf", "units"] call fnc_tell;
	_units = _units - [_unit];
	[_self, "_setf", "units", _units] call fnc_tell;
	_units
} ENDMETHOD;


DEFMETHOD("UnitGroup", "groups") ["_self"] DO {
	/* Return all groups represented in this UnitGroup */
	private ["_groups", "_group"];
	_groups = [];
	{
		_group = group _x;
		if (not (_group in _groups)) then {
			_groups = _groups + [_group];
		};
	} foreach (_self getVariable "units");
	_groups
} ENDMETHOD;


DEFMETHOD("UnitGroup", "reinitialize_groups") ["_self", "_next_waypoint"] DO {
	private ["_group"];
	{
		_group = createGroup (side _x);
		_group copyWaypoints _x;
		if (not isNil "_next_waypoint") then {
			switch (_next_waypoint) do {
				case true: {
					_group setCurrentWaypoint
					       [_group,
						(currentWaypoint _x) + 1];
				};
				default {
					_group setCurrentWaypoint
					       [_group, _next_waypoint];
				};
			};
		} else {
			_group setCurrentwaypoint
			       [_group, (currentWaypoint _group)];
		};
		(units _x) joinSilent _group;
		deleteGroup _x;
	} forEach ([_self, "groups"] call fnc_tell);
} ENDMETHOD;


DEFMETHOD("UnitGroup", "move") ["_self", "_destination"] DO {
	/* Block until unit group has moved to the new position or stopped */
	private ["_pos", "_matches", "_newPos"];
	{
		_x move _destination;
	} forEach ([_self, "groups"] call fnc_tell);
	_pos = [_self, "center_pos"] call fnc_tell;
	_matches = 0;
	waitUntil {
		sleep 1;
		_newPos = [_self, "center_pos"] call fnc_tell;
		if (_pos isEqualTo _newPos) then {
			_matches = _matches + 1;
		} else {
			_matches = 0;
		};
		_pos = _newPos;
		(((_pos distance _destination) < 15) or
		 (_matches > 5))
	};
} ENDMETHOD;


DEFMETHOD("UnitGroup", "sequester") ["_self"] DO {
	/* Despawn units and record groups/loadouts */
	private ["_loadouts", "_classnames", "_positions", "_group", "_groups",
		 "_groupIndices", "_sides", "_i", "_units", "_vehicles",
		 "_monitor"];
	_loadouts = [];
	_classnames = [];
	_positions = [];
	_groups = [];
	_groupIndices = [];
	_sides = [];
	_units = _self getVariable "units";
	_vehicles = _self getVariable "vehicles";
	if (not isNil "_vehicles") then {
		_units = _units - _vehicles;
	} else {
		_vehicles = [];
	};
	{
		if (alive _x) then {
			_loadouts pushBack (getUnitLoadout _x);
			_classnames pushBack (typeOf _x);
			_positions pushBack (position _x);
			if (not ((group _x) in _groups)) then {
				_groupIndices pushBack (count _groups);
				_groups pushBack (group _x);
			} else {
				_i = 0;
				while {(_groups select _i) != (group _x)} do {
					_i = _i + 1;
				};
				_groupIndices pushBack _i;
			};
			_sides pushBack (side _x);
		};
		_monitor = _x getVariable "monitor";
		if (not isNil "_monitor") then {
			terminate _monitor;
		};
		unassignVehicle _x;
	} forEach _units;
	{deleteVehicle _x;} forEach _units;
	[_self, "_setf", "units", _vehicles] call fnc_tell;
	[_self, "_setf", "_loadouts", _loadouts] call fnc_tell;
	[_self, "_setf", "_classnames", _classnames] call fnc_tell;
	[_self, "_setf", "_positions", _positions] call fnc_tell;
	[_self, "_setf", "_groupIndices", _groupIndices] call fnc_tell;
	[_self, "_setf", "_sides", _sides] call fnc_tell;
	[_self, "_setf", "sequestered", true] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("UnitGroup", "desequester") ["_self"] DO {
	/* Respawn sequestered units into replica groups (w/o waypoints) */
	private ["_groups", "_sides", "_unit", "_vehicles"];
	_groups = [];
	_sides = _self getVariable "_sides";
	{
		_i = _x select 0;
		_gi = _x select 1;
		_side = _sides select _i;
		if (_gi >= (count _groups)) then {
			_groups pushBack (createGroup _side);
		};
	} forEach ((_self getVariable "_groupIndices") call fnc_enumerate);
	[[["_loadout", "_classname", "_position", "_group_index"], {
		_unit = (_groups select _group_index) createUnit [_classname,
								  _position,
								  [],
								  0,
								  "NONE"];
		_unit setUnitLoadout _loadout;
		[_self, "_push_attr", "units", _unit] call fnc_tell;
	 }] call fnc_lambda,
 	 _self getVariable "_loadouts",
	 _self getVariable "_classnames",
	 _self getVariable "_positions",
	 _self getVariable "_groupIndices"] call fnc_map;
	_vehicles = _self getVariable "vehicles";
	if (not isNil "_vehicles") then {
		_self setVariable ["vehicles", []];
		_self setVariable ["gunners", []];
		_self setVariable ["drivers", []];
		_self setVariable ["cargo", []];
		[_self, "auto_assign", _self getVariable "units"]
		 call fnc_tell;
	};
	[_self, "_setf", "sequestered", nil] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("UnitGroup", "timed_patrol") ["_self",
					"_location",
					"_radius",
					"_time",
					"_return_to"] DO {
	/* Run BIS_fnc_taskPatrol for a set duration then move back */
	private ["_groups", "_group", "_return_pos", "_wpt", "_waypoint",
		 "_wpType", "_vehicles"];
	_groups = [_self, "groups"] call fnc_tell;
	for "_i" from 0 to ((count _groups) - 1) do {
		if ((({alive _x} count (units (_groups select _i))) > 0) and
		    (not isNil "_location")) then {
			[_groups select _i, _location, _radius]
			 call BIS_fnc_taskPatrol;
		};
	};
	sleep _time;
	if (isNil "_return_to") then {
		_return_to = [_self, "center_pos"] call fnc_tell;
	};
	if ((typeName _return_to) == "ARRAY") then {
		_return_pos = _return_to;
	} else {
		_return_pos = position _return_to;
	};
	_vehicles = _self getVariable "vehicles";
	if (isNil "_vehicles") then {
		_wpType = "MOVE";
	} else {
		_wpType = "GETOUT";
	};
	{
		_group = createGroup (side _x);
		_wpt = _group addWaypoint [_return_pos,
					   currentWaypoint _group];
		if ((typeName _return_to) != "ARRAY") then {
			_wpt waypointAttachVehicle _return_to;
		};
		_wpt setWaypointType _wpType;
		_wpt setWaypointBehaviour "SAFE";
		_group setCurrentWaypoint _wpt;
		(units _x) joinSilent _group;
		deleteGroup _x;
	} forEach _groups;
} ENDMETHOD;


DEFMETHOD("UnitGroup", "add_waypoint") ["_self", "_waypoint", "_index"] DO {
	/* Add a waypoint instance to every group in the UnitGroup */
	if (isNil "_index") then {
		_index = -1;
	};
	[[["_grp", "_wpt", "_idx"], {
		[_wpt, "to_group", _grp, _idx] call fnc_tell;
	 }] call fnc_lambda,
	 [_self, "groups"] call fnc_tell,
	 [_waypoint, _index]] call fnc_mapwith
} ENDMETHOD;

