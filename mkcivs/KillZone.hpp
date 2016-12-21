DEFCLASS("KillZone") ["_self", "_type", "_radius"] DO {
	switch (_type) do {
		case "intersections": {
			_self setVariable ["targets",
					   [_self, _radius]
					    call fnc_find_intersections];
		};
	};
	_self setVariable ["radius", _radius];
	_self
} ENDCLASS;


DEFMETHOD("KillZone", "arm") ["_self", "_population_size", "_generations"] DO {
	private ["_targets"];
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
			    [_population_size] call fnc_make_concentric_rings
			    ] call fnc_find_positions];
} ENDMETHOD;


DEFMETHOD("KillZone", "engage") ["_self", "_pull_radius"] DO {
	[_pull_radius, _self getVariable "positions"]
	 execVM "mkcivs\layAmbush.sqf";
} ENDMETHOD;
