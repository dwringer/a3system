fnc_unload_helicopters = [["_position",           /* Start search here */
			   "_helicopters",        /* Vehicles to be landed */
			   "_enemies",            /* Array to avoid */
			   "_search_radius",      /* Size of search area */
			   "_search_steps",       /* Number of evolutions */
			   "_search_population",  /* Size of population */
			   "_search_shape"], {    /* Unit shape positions */ 
	private ["_pad", "_solutions", "_group", "_solutionIndex", "_wp",
		 "_pads", "_confirmed", "_assignments", "_optimizations",
		 "_fn_distanceSort"];
	_assignments = [];
	_optimizations = [[false, 0.35, 1.5, '[_x, 3, 2]',
			   fnc_check_level]
			   call fnc_to_cost_function,
			  [false, 0, 1, '[_x]',
			   fnc_surface_is_water]
			   call fnc_to_cost_function,
			  [true, 0, 40,
			   '[_x, 1, ["Building", "House", "Church", "Chapel",
				     "Rock", "Bunker", "Fortress", "Fountain",
				     "Lighthouse", "Fuelstation", "Hospital",
				     "Busstop", "Ruin", "Rocks",
                                     "Tree", "Small Tree",
                                     "Forest Border", "Forest Triangle", 
                                     "Forest Square", "Forest"],
                             20]',
			   fnc_average_distance_to_nearest_terrain_objects]
			   call fnc_to_cost_function,
			  [true, 0.15, .85, '[_x, 2, 2, .75]',
			   fnc_check_los_grid]
			   call fnc_to_cost_function];
	if (not (isNil "_enemies")) then {
		if ((count _enemies) > 0) then {
			_assignments = [["targets", _enemies]];
			_optimizations = _optimizations +
				[[false, 0, 1,
				  '[_x, _x getVariable "targets", 1.6, true]',
				   fnc_LOS_to_array]
				  call fnc_to_cost_function,
				 [true, 25, 50,
				  '[position _x,
                                     ([[["_t"], {position _t}] call fnc_lambda,
                                       _x getVariable "targets"] 
                                       call fnc_map) call fnc_vector_mean]',
				   fnc_euclidean_distance]
				  call fnc_to_cost_function];
		};
	};
	if (isNil "_search_radius") then {
		_search_radius = 75;
	};
	if (isNil "_search_steps") then {
		_search_steps = ceil sqrt (2 * count _helicopters);
	};
	if (isNil "_search_population") then {
		_search_population = floor (7 * (sqrt (count _helicopters)));
	};
	if (isNil "_search_shape") then {
		_search_shape = [_search_population] call fnc_make_ring;
	};
	_fn_distanceSort = [["_a", "_b"], {
				   ([_a, 1,
				     ["Building", "House", "Church", "Chapel",
				      "Rock", "Bunker", "Fortress", "Fountain",
				      "Lighthouse", "Fuelstation", "Hospital",
				      "Busstop", "Ruin", "Rocks",
				      "Tree", "Small Tree", "Forest Border",
				      "Forest Triangle", "Forest Square",
				      "Forest"],
				     40]
	       call fnc_average_distance_to_nearest_terrain_objects) >
				   ([_b, 1,
				     ["Building", "House", "Church", "Chapel",
				      "Rock", "Bunker", "Fortress", "Fountain",
				      "Lighthouse", "Fuelstation", "Hospital",
				      "Busstop", "Ruin", "Rocks",
				      "Tree", "Small Tree", "Forest Border",
				      "Forest Triangle", "Forest Square",
				      "Forest"],
				     40]
	       call fnc_average_distance_to_nearest_terrain_objects)
	}] call fnc_lambda;
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
				      ceil ((count _helicopters) / .618),
				      [[.35, .8], [.8, .35]],
				      _search_shape]
				      call fnc_find_positions;
			_solutions = [[["_s"], {
					([_s] call ([false, 0.35, 1.5,
						     '[_x, 3, 2]',
						     fnc_check_level]
						    call fnc_to_cost_function))
					< 0.1
				      }] call fnc_lambda,
				      _solutions] call fnc_filter;
			_solutions = [_solutions,
				      _fn_distanceSort] call fnc_sorted;
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
