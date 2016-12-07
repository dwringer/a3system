#define COMPUTE_SOLUTIONS [_search_radius,  \
			   [_position],	\
			   [["targets", _enemies]],	\
			   [OPT_fnc_no_LOS_to_targets,  \
			    OPT_fnc_vegetation_clear,	\
			    OPT_fnc_forests_clear,	\
			    OPT_fnc_cover_unavailable,  \
			    OPT_fnc_level_surface,	\
			    OPT_fnc_surface_is_not_water,	\
			    OPT_fnc_area_LOS_clear,		\
			    OPT_fnc_distance_from_targets],	\
			   _search_population,			\
			   _search_steps,			\
			   true] call fnc_find_positions

fnc_unload_helicopters = [["_position", "_helicopters", "_enemies",
			   "_search_radius", "_search_steps",
			   "_search_population", "_include_center"], {
	private ["_pad", "_solutions", "_group", "_solutionIndex", "_wp",
		 "_pads", "_helicopterIndex", "_confirmed", "_assignments",
		 "_optimizations"];
	_assignments = [];
	_optimizations = [OPT_fnc_vegetation_clear,
			  OPT_fnc_forests_clear,
			  OPT_fnc_cover_unavailable,
			  OPT_fnc_level_surface,
			  OPT_fnc_surface_is_not_water,
			  OPT_fnc_area_LOS_clear];
	if (not isNil "_enemies") then {
		_assignments = [["targets", _enemies]];
		_optimizations = _optimizations +
			         [OPT_fnc_no_LOS_to_targets,
				  OPT_fnc_distance_from_targets];
	};
	if (isNil "_search_radius") then {
		_search_radius = 100;
	};
	if (isNil "_search_steps") then {
		_search_steps = 2;
	};
	if (isNil "_search_population") then {
		_search_population = 7;
	};
	if (isNil "_include_center") then {
		_include_center = true;
	};
	_solutions = [];
	_solutionIndex = 0;
	_helicopterIndex = 0;
	_pads = [];
	while {_helicopterIndex < (count _helicopters)} do {
		_confirmed = false;
		while {not _confirmed} do {
			_confirmed = true;
			for "_i" from 0 to ((count _pads) - 1) do {
				scopeName "skipClose";
				if (((_pads select _i) distance
				     (_solutions select _solutionIndex)) < 25)
				then {
					_solutionIndex = _solutionIndex + 1;
					_confirmed = false;
					breakOut "skipClose";
				};
			};
		};
		if (_solutionIndex >= (count _solutions)) then {
			_solutions = [_search_radius,
				      [_position],
				      _assignments,
				      _optimizations,
				      _search_population,
				      _search_steps,
				      _include_center] call fnc_find_positions;
			_solutions = [_solutions,
				      [["_a", "_b"], {
				          ((_a distance (nearestBuilding _a)) >
				           (_b distance (nearestBuilding _b)))
				      }] call fnc_lambda] call fnc_sorted;
			_solutionIndex = 0;
		} else {
			_pad = "Land_HelipadEmpty_F" createVehicle
			       (position (_solutions select _solutionIndex));
			_solutionIndex = _solutionIndex + 1;
			_helicopterIndex = _helicopterIndex + 1;
			_pads = _pads + [_pad];
		};
	};
	for "_i" from 0 to ((count _helicopters) - 1) do {
		_pad = _pads select _i;
		_group = group ((crew (_helicopters select _i)) select 0);
		_wp = _group addWaypoint [position _pad,
					  currentWaypoint _group];
		_wp waypointAttachVehicle _pad;
		_wp setWaypointType "TR UNLOAD";
		_wp setWaypointBehaviour "CARELESS";
		_group setCurrentWaypoint _wp;
	};
}] call fnc_vlambda;
