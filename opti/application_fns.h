fnc_find_positions = [["_radius",        /* Initial search radius */
                       "_init_array",    /* Initial position set */
		       "_assignments",   /* Local bindings for particles */
		       "_objectives",    /* Objective [cost] functions */
                       "_pop_size",      /* Particle count */
		       "_generations",   /* Number of GA steps */
		       "_fill_area"], {  /* Fill circle instead of ring */
	/* Evolve positions from initial array */
        private ["_optimizer", "_thread", "_result", "_assignment",
 	         "_assignments", "_key", "_value"];
        _optimizer = ["Optimizer", _pop_size, "Particle"] call fnc_new;
	[_optimizer, "conform_positions", _init_array] call fnc_tell;
	if (isNil "_fill_area") then {
		[_optimizer, "radial_scatter_2d",
		 _radius / 1.25, _radius * 1.25] call fnc_tell;
	} else {
		[_optimizer, "perturb", 2, _radius] call fnc_tell;		 
	};
	{
		for "_i" from 0 to ((count _assignments) - 1) do {
			_assignment = _assignments select _i;
			_key = _assignment select 0;
			_value = _assignment select 1;
			[_x, "_setf", _key, _value] call fnc_tell;
		};
        } forEach (_optimizer getVariable "population");
	{
		[_optimizer, "add_objective", _x] call fnc_tell;
	} forEach _objectives;
	_thread = [_optimizer, _generations, floor (_pop_size / 5)]
	           spawn ([["_opti", "_gens", "_sz"], {
		private ["_bins", "_handle", "_retries"];
		for "_i" from 0 to (_gens - 1) do {
			_handle = [_opti, "MODE_step"] call fnc_tells;
		        waitUntil {scriptDone _handle};
		};
		_bins = [[]];
		_retries = 0;
		while {(((count _bins) <= 1) or
			((count (_bins select 0)) < _sz)) and
	               (_retries < _gens)} do {
			_handle = [_opti, "MODE_step"] call fnc_tells;
		        waitUntil {scriptDone _handle};
		        _bins = [_opti,
              		         "non_dominated_sort"] call fnc_tell;
			_retries = _retries + 1;
		};
		[_opti, "_setf",
		 "result", _bins select 0] call fnc_tell;
		{
			[[["_y"], {
				[_y, "hide"] call fnc_tell;
				deleteVehicle _y;
			 }] call fnc_lambda,
			 _x] call fnc_map;
		} forEach ([_bins, 1, 0] call fnc_subseq);
	}] call fnc_lambda);
        waitUntil {scriptDone _thread};
	_result = _optimizer getVariable "result";
	deleteVehicle _optimizer;
	_result
}] call fnc_lambda;
