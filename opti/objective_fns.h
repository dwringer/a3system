component_fnc_units_nearby = [["_x", "_units", "_dist", "_min", "_max"], {
	/* Parametric cost for not having a certain number of units nearby */
	private ["_count"];
	_count = count ([_x, _units, _dist] call fnc_neighbors);
	(1 min (0 max ((_count - _min) / (_max - _min))))
}] call fnc_lambda;


component_fnc_partial_LOS_to_array_members = [["_y",
					       "_array",
					       "_eye_height",
					       "_full_LOS_bias",
					       "_no_LOS_weight",
					       "_min",
					       "_max"], {
	/* Parametric cost for not having occluded LOS to array members */
	private ["_sum", "_v"];
	_sum = 0;
	{
		_v = (1 - ([vehicle _y, "VIEW", vehicle _x] checkVisibility
		            [[(getPosASL _y) select 0, 
                              (getPosASL _y) select 1, 
		              ((getPosASL _y) select 2) + _eye_height], 
		             eyePos _x])); 
		if ((_v >= 0.025) && (_v < 1)) then {
			_sum = _sum + 0;
		} else {
			if (_v < 0.025) then {
				_sum = _sum + _full_LOS_bias + _no_LOS_weight;
			} else {
				_sum = _sum + (1 - _full_LOS_bias);
			};
		};
	} forEach _array;
	(((_sum / (count _array)) - _min) / (_max - _min))
}] call fnc_lambda;


component_fnc_building_positions_nearby = [["_x", "_dist", "_min", "_max"], {
	/* Parametric cost for not having building positions nearby */
	private ["_houses", "_positions"];
	_houses = _x nearObjects ["house", _dist];
	_positions = [];
	for "_i" from 0 to ((count _houses) - 1) do {
		_positions = _positions + ((_houses select _i) buildingPos -1);
	};
	(1 min (0 max (((count _positions) - _min)) / (_max - _min)))
}] call fnc_lambda;


fnc_find_intersections = [["_x", "_dist"], {
	private ["_segments", "_intersections", "_segment"];
	_segments = _x nearRoads _dist;
	_intersections = [];
	for "_i" from 0 to ((count _segments) - 1) do {
		_segment = _segments select _i;
		if ((count roadsConnectedTo _segment) > 2) then {
			_intersections = _intersections + [_segment];
		};
	};
	_intersections
}] call fnc_lambda;


fnc_trace_road = [["_start", "_candidates"], {
	private ["_trace", "_next", "_connected", "_foundOne", "_selection",
                 "_newConnections"];
	_trace = [];
	_next = _start;
	_connected = roadsConnectedTo _next;
	while {True} do {
		scopeName "TracingPath";
		_foundOne = false;
		for "_i" from 0 to ((count _connected) - 1) do {
			scopeName "CheckingUniqueness";
			_selection = _connected select _i;
			_newConnections = roadsConnectedTo _selection;
			if ((not (_selection in _trace)) and
                            (not (count (_newConnections) > 2)) and
			    (_selection in _candidates)) then {
				_trace = _trace + [_selection];
				_next = _selection;
   			        _connected = _newConnections;
				_foundOne = true;
				breakOut "CheckingUniqueness";
			};
		};
		if (not _foundOne) then {
			breakOut "TracingPath";
		};
	};
	_trace
}] call fnc_lambda;


component_fnc_distance_from_position = [["_x", "_pos", "_min", "_max"], {
	/* Parametric cost for being close to a position */
	(1 min
	 (0 max
	  (([_pos, _x] call fnc_euclidean_distance) - _min) /
	  (_max - _min)))
}] call fnc_lambda;


OPT_fnc_building_positions_nearby = [["_x"], {
	/* Cost function for not having building positions nearby */
	1 - ([_x, 35, 2, 10] call component_fnc_building_positions_nearby);
}] call fnc_lambda;


OPT_fnc_civilians_nearby = [["_x"], {
	/* Cost function for not being near civs in civArray */
	1 - ([_x, civArray, 100, 1, 5] call component_fnc_units_nearby);
}] call fnc_lambda;


OPT_fnc_partial_LOS_to_player_group = [["_x"], {
	/* Cost function for not having occluded LOS to player group */
	[_x, units group player,
	 1.6, 0, 0.5, 0, 1] call component_fnc_partial_LOS_to_array_members;
}] call fnc_lambda;


OPT_fnc_partial_LOS_to_targets = [["_x"], {
        /* Cost function for not having occluded LOS to designated targets */
	private ["_targets"];
	_targets = _x getVariable ["targets", []];
	[_x, _targets,
	 1.6, 0, 0.5, 0, 1] call component_fnc_partial_LOS_to_array_members;
}] call fnc_lambda;


OPT_fnc_distance_from_player = [["_x"], {
	/* Cost function for being close to a position */
	1 -
	([position _x, position player, 50, 300]
	  call component_fnc_distance_from_position);
}] call fnc_lambda;
