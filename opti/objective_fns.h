////////////////////////////// OBJECTIVE_FNS.H ////////////////////////////////
//  A set of cost/objective functions and utilities for creating new ones    //
///////////////////////////////////////////////////////////////////////////////

////////////////////////
// UTILITY FUNCTIONS: //  For creating arbitrary normalized cost functions
///////////////////////////////////////////////////////////////////////////////

fnc_normalizer = [["_particle_function", "_min", "_max"], {
	/* Create a normalized version of the given function of one Particle */
	[["_p"], format ['private ["_min", "_max"];
                          _min = %2;
                          _max = %3;
                          (1 min (0 max 
                           (((_max min (_min max ([_p] call %1))) - _min) / 
                            (_max - _min))))',
                         _particle_function, _min, _max]] call fnc_lambdastr
}] call fnc_lambda;


fnc_to_cost_function = [["_maximize",
			 "_min",
			 "_max",
			 "_x_parameter_string",
			 "_function"], {
	/* Turn f("[_x_parameter_string]") to [min|max]imization f(_x) */
	private ["_pf", "_cf", "_prefix"];
	_pf = [["_x"],
	               format ["%1 call %2", _x_parameter_string, _function]]
 	       call fnc_lambdastr;
	if (_maximize) then {_prefix = "1 - "} else {_prefix = ""};
	_cf = [["_x"],
	       format ["%1([_x] call %2)",
		       _prefix,
		       [_pf, _min, _max] call fnc_normalizer]]
	       call fnc_lambdastr;
	_cf
}] call fnc_lambda;

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// OBJECTIVE DATA FUNCTIONS: //  Parameterized functions for objective data
///////////////////////////////////////////////////////////////////////////////

fnc_units_nearby = [["_x", "_units", "_dist"], {
	/* Count members of _units within _dist of _x */
	count ([_x, _units, _dist] call fnc_neighbors)
}] call fnc_lambda;


fnc_partial_LOS_to_array = [["_p",
			     "_array",
			     "_eye_height",
			     "_full_LOS_bias",
			     "_no_LOS_weight",
			     "_is_unit_array"], {
	/* Ratio of occluded LOS to array of positions */
	private ["_sum", "_visibilityParams", "_v", "_target"];
	_sum = 0;
	{
		_visibilityParams = [vehicle _p, "VIEW"];
		if (_is_unit_array) then {
			_visibilityParams = _visibilityParams + [vehicle _x];
			_target = eyePos _x;
		} else {
			_target = _x;
		};			
		_v = (1 - (_visibilityParams checkVisibility
		            [[(getPosASL _p) select 0, 
                              (getPosASL _p) select 1, 
		              ((getPosASL _p) select 2) + _eye_height], 
		             _target])); 
		if (_v < 0.025) then {
			_sum = _sum + _full_LOS_bias + _no_LOS_weight;
		} else {
			if (_v >= 1) then {
				_sum = _sum + (1 - _full_LOS_bias);
			};
		};
	} forEach _array;
	(_sum / (count _array))
}] call fnc_lambda;


fnc_building_positions_nearby = [["_x", "_dist"], {
	/* Parametric cost for not having building positions nearby */
	private ["_houses", "_positions"];
	_houses = _x nearObjects ["house", _dist];
	_positions = [];
	for "_i" from 0 to ((count _houses) - 1) do {
		_positions = _positions + ((_houses select _i) buildingPos -1);
	};
	count _positions
}] call fnc_lambda;


fnc_roads_nearby = [["_x", "_dist"], {
	/* Count roads near _x within _dist */
	count ([_x, _dist] call fnc_find_roads)
}] call fnc_lambda;

///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// NORMALIZED OBJECTIVE FUNCTIONS OF A SINGLE PARTICLE: //
///////////////////////////////////////////////////////////////////////////////

// Cost for having [2..6] roads within 7.5m:
OPT_fnc_distance_from_roads = [false, 2, 6,
			       '[_x, 7.5]',
			       fnc_roads_nearby]
	                       call fnc_to_cost_function;


// Cost for having [0..10] building positions within 35m:
OPT_fnc_building_positions_nearby = [true, 0, 10,
				     '[_x, 35]',
				     fnc_building_positions_nearby]
	                             call fnc_to_cost_function;


// Cost function for not being near [3..8] civs in civArray within 100m:
OPT_fnc_civilians_nearby = [true, 3, 8,
			    '[_x, civArray, 100]',
			    fnc_units_nearby]
	                    call fnc_to_cost_function;


// Cost function for not having occluded LOS to player group:
OPT_fnc_partial_LOS_to_player_group = [false, 0, 1,
				       '[_x, units group player, 
                                         1.6, 0, 0.5, true]',
				       fnc_partial_LOS_to_array]
                                       call fnc_to_cost_function;


// Cost function for not having occluded LOS to designated targets:
OPT_fnc_partial_LOS_to_targets = [false, 0, 1,
				  '[_x,
				    [[["_t"], {
                                             [(position _t) select 0,
                                              (position _t) select 1,
                                              1.5 + ((position _t) select 2)]
                                     }] call fnc_lambda,
				     _x getVariable "targets"]
				     call fnc_map,
                                    1.6, 0, 0.5, false]',
				  fnc_partial_LOS_to_array]
                                  call fnc_to_cost_function;


// Cost function for being close (w/in 50-300m) to player position:
OPT_fnc_distance_from_player = [true, 50, 300,
				'[position _x, position player]',
				fnc_euclidean_distance]
                                call fnc_to_cost_function;


// Cost function for being close to designated targets:
OPT_fnc_distance_from_targets = [true, 35, 200,
				 '[position _x,
                                   ([[["_t"], {position _t}] call fnc_lambda,
                                     _x getVariable "targets"] 
                                     call fnc_map) call fnc_vector_mean]',
				 fnc_euclidean_distance]
                                 call fnc_to_cost_function;

///////////////////////////////////////////////////////////////////////////////
