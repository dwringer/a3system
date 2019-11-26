fnc_calculate_DE_parameters = [["_range_matrix",
                                "_current_index",
                                "_total_steps"], {
	/* Linear adjustment of DE parameters over time */
	private ["_weight", "_freq"];
	_weight = ((_range_matrix select 0) select 0) +
	          (_current_index *
		   ((((_range_matrix select 0) select 1) -
		     ((_range_matrix select 0) select 0)) /
		    (_total_steps - 1)));
	_freq = ((_range_matrix select 1) select 0) +
	        (_current_index *
		  ((((_range_matrix select 1) select 1) -
		    ((_range_matrix select 1) select 0)) /
		   (_total_steps - 1)));
	[_weight, _freq]
}] call fnc_lambda;


fnc_find_positions = [["_radius",           /* Initial search radius */
                       "_init_array",       /* Initial position set */
                       "_assignments",      /* Local bindings for particles */
                       "_objectives",       /* Objective [cost] functions */
                       "_pop_size",         /* Particle count */
                       "_generations",      /* Number of GA steps */
                       "_number_expected",  /* Done if this many within gens */
                       "_DE_parameters",    /* DE parameter[ range]s */
		       "_seed_form"], {     /* Initialize with shape */
	/* Evolve positions from initial array */
	private ["_optimizer", "_result", "_assignment", "_assignments",
	         "_key", "_value", "_bins", "_retries"];

        // Prepare the optimizer:       
        _optimizer = ["Optimizer", _pop_size, "Particle"] call fnc_new;
        [_optimizer, "conform_positions", _init_array] call fnc_tell;
	{
		[_optimizer, "add_objective", _x] call fnc_tell;
	} forEach _objectives;

	// Handle default/optional arguments:
	if (isNil "_seed_form") then {
		_seed_form = [_pop_size] call fnc_make_ring;
	};
	[_optimizer, "displace_shape", _seed_form, random 360, _radius]
	 call fnc_tell;
        if (isNil "_number_expected") then {
		_number_expected = floor (_pop_size / 5);
	};
	if (isNil "_DE_parameters") then {
		_DE_parameters = [[0.35, 0.35], [0.8, 0.8]];
	} else {
		if (typeName (_DE_parameters select 0) != "ARRAY") then {
			_DE_parameters = [[_DE_parameters select 0,
			                   _DE_parameters select 0],
			                  _DE_parameters select 1];
		};
		if (typeName (_DE_parameters select 1) != "ARRAY") then {
		        _DE_parameters = [_DE_parameters select 0,
                                         [_DE_parameters select 1,
                                          _DE_parameters select 1]];
		};
	};

	// Prepare local particle assignments:
        {
		for "_i" from 0 to ((count _assignments) - 1) do {
			_assignment = _assignments select _i;
         		_key = _assignment select 0;
			_value = _assignment select 1;
			[_x, "_setf", _key, _value] call fnc_tell;
		};
        } forEach (_optimizer getVariable "population");
	
	// Run evolution process:
	for "_i" from 0 to (_generations - 1) do {
		([_optimizer, "MODE_step"] +
		([_DE_parameters, _i, _generations]
		  call fnc_calculate_DE_parameters))
		 call fnc_tell;
	};
	_bins = [_optimizer, "non_dominated_sort"] call fnc_tell;
	
	// Keep going if only one bin or not enough dominant solutions found:
	_retries = 0;
	while {(((count _bins) <= 1) or
		((count (_bins select 0)) < _number_expected)) and
	       (_retries < _generations)} do {
	        ([_optimizer, "MODE_step"] +
		([_DE_parameters, _retries, _generations]
		  call fnc_calculate_DE_parameters))
		 call fnc_tell;
		_bins = [_optimizer, "non_dominated_sort"] call fnc_tell;
		_retries = _retries + 1;
	};
	
	// Save the dominant bin, clean up, and return:
	[_optimizer, "_setf", "result", _bins select 0] call fnc_tell;
	{
		[[["_y"], {
			[_y, "hide"] call fnc_tell;
			deleteVehicle _y;
		 }] call fnc_lambda,
		 _x] call fnc_map;
	} forEach ([_bins, 1, 0] call fnc_subseq);
	_result = _optimizer getVariable "result";
	deleteVehicle _optimizer;
	_result
}] call fnc_vlambda;
