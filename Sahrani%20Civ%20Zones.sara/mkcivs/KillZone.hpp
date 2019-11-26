DEFCLASS("KillZone") ["_self", "_type", "_radius", "_probability", "_targets", "_side"] DO {
	if (isNil "_side") then { _side = OPFOR; };
	_self setVariable ["_side", _side];
	switch (_type) do {
		case "intersections": {
			_self setVariable ["targets",
					   [_self, _radius]
					    call fnc_find_intersections];
		};
		case "roads": {
			_self setVariable ["targets",
					   (position _self) nearRoads _radius];
		};
		case "units": {
			_self setVariable ["targets", _targets];
		};
		case "group": {
			_self setVariable ["targets", units group _targets];
		};
	};
	_self setVariable ["radius", _radius];
	if (not isNil "_probability") then {
		_self setVariable ["probability", _probability];
	} else {
		_self setVariable ["probability", 1.0];
	};
	_self
} ENDCLASSV;


DEFMETHOD("KillZone", "arm") ["_self", "_population_size", "_generations"] DO {
	private ["_targets"];
	if ((random 1) <= (_self getVariable "probability")) then {
		_targets = _self getVariable "targets";
		_self setVariable ["positions",
				   [_self getVariable "radius",
				    [[["_x"], {position _x}] call fnc_lambda,
				     _targets] call fnc_map,
				    [["targets", _targets]],
				    [OPT_fnc_distance_from_roads,
				     OPT_fnc_building_positions_nearby,
				     OPT_fnc_distance_from_targets,
				     OPT_fnc_partial_LOS_to_targets,
				     OPT_fnc_civilians_nearby],
				    _population_size,
				    _generations,
				    ceil (1.618 * (count _targets)),
				    [[.35, .8], [.8, .35]],
				    [_population_size]
				     call fnc_make_concentric_rings]
				    call fnc_find_positions];
	};
} ENDMETHOD;


DEFMETHOD("KillZone", "engage") ["_self", "_pull_radius", "_probability"] DO {
	private ["_positions"];
	_positions = _self getVariable "positions";
	if (isNil "_probability") then {
		_probability = 1.0;
	};
	if (not isNil "_positions") then {
		[_pull_radius, _self getVariable "positions",
		 _probability, _self getVariable "_side"]
		 execVM "mkcivs\layAmbush.sqf";
	};
} ENDMETHOD;
