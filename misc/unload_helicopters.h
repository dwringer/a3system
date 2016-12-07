fnc_unload_helicopters = [["_position",           /* Start search here */
			   "_helicopters",        /* Vehicles to be landed */
			   "_enemies",            /* Array to avoid */
			   "_search_radius",      /* Size of search area */
			   "_search_steps",       /* Number of evolutions */
			   "_search_population",  /* Size of population */
			   "_include_center"], {  /* Scatter over full area? */
	private ["_pad", "_solutions", "_group", "_solutionIndex", "_wp",
		 "_pads", "_confirmed", "_assignments", "_optimizations"];
	_assignments = [];
	_optimizations = [[false, 0, 5, '[_x, 15]', fnc_vegetation_nearby]
			   call fnc_to_cost_function,
			  [false, 0, 5, '[_x, 25]', fnc_forests_nearby]
			   call fnc_to_cost_function,
			  [false, 1, 10, '[_x, 25]', fnc_cover_nearby]
			   call fnc_to_cost_function,
			  [false, 0.35, 1.5, '[_x, 5, 2]', fnc_check_level]
			   call fnc_to_cost_function,
			  [false, 0, 1, '[_x]', fnc_surface_is_water]
			   call fnc_to_cost_function,
			  [true, 0.15, .85, '[_x, 1.5, 4, 0.75]',
			   fnc_check_los_grid] call fnc_to_cost_function];
	if (not isNil "_enemies") then {
		_assignments = [["targets", _enemies]];
		_optimizations = _optimizations +
			         [[false, 0, 1,
				   '[_x, _x getVariable "targets", 1.6, true]',
				   fnc_LOS_to_array] call fnc_to_cost_function,
				  [true, 25, 50,
				   '[position _x,
                                     ([[["_t"], {position _t}] call fnc_lambda,
                                       _x getVariable "targets"] 
                                       call fnc_map) call fnc_vector_mean]',
				   fnc_euclidean_distance]
				   call fnc_to_cost_function];
	};
	if (isNil "_search_radius") then {
		_search_radius = 100;
	};
	if (isNil "_search_steps") then {
		_search_steps = 2;
	};
	if (isNil "_search_population") then {
		_search_population = floor (7 * (sqrt (count _helicopters)));
	};
	if (isNil "_include_center") then {
		_include_center = true;
	};
	_solutions = [];
	_solutionIndex = 0;
	_pads = [];
	while {(count _pads) < (count _helicopters)} do {
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
				      _include_center,
				      ceil ((count _helicopters) / .618)]
				      call fnc_find_positions;
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
