////////////////////////////// OBJECTIVE_FNS.H ////////////////////////////////
//  A set of cost/objective functions and utilities for creating new ones    //
///////////////////////////////////////////////////////////////////////////////
//  Utilities:                                                               //
//    fnc_normalizer                                                         //
//        particle_function                                                  //
//        min                                                                //
//        max                                                                //
//    fnc_to_cost_function                                                   //
//        maximize?                                                          //
//        min                                                                //
//        max                                                                //
//        param_arr_str                                                      //
//        function                                                           //
//  Available parameterized particle functions:                              //
//    fnc_average_distance_to_nearest_terrain_objects                        //
//    fnc_average_distance_to_nearest_array_members                          //
//    fnc_building_positions_nearby                                          //
//    fnc_check_level                                                        //
//    fnc_get_elevation                                                      //
//    fnc_intersections_nearby                                               //
//    fnc_LOS_to_array                                                       //
//    fnc_partial_LOS_to_array                                               //
//    fnc_roads_nearby                                                       //
//    fnc_surface_is_water                                                   //
//    fnc_units_nearby                                                       //
//    fnc_vegetation_nearby                                                  //
//  Normalized functions of a single particle:                               //
//    OPT_fnc_above_elevation_target                                         //
//    OPT_fnc_below_elevation_target                                         //
//    OPT_fnc_building_positions_nearby                                      //
//    OPT_fnc_civilians_nearby                                               //
//    OPT_fnc_distance_from_player                                           //
//    OPT_fnc_distance_from_roads                                            //
//    OPT_fnc_distance_from_targets                                          //
//    OPT_fnc_fuel_station_nearby                                            //
//    OPT_fnc_level_surface                                                  //
//    OPT_fnc_partial_LOS_to_player_group                                    //
//    OPT_fnc_partial_LOS_to_targets                                         //
//    OPT_fnc_surface_is_water                                               //
//    OPT_fnc_surface_is_not_water                                           //
//    OPT_fnc_targets_nearby                                                 //
//    OPT_fnc_vegetation_clear                                               //
//    OPT_fnc_vegetation_dense                                               //
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
	/* Turn f(<"[_x_parameter_string]">) to [min|max]imization f([_x]) */
	private ["_pf", "_cf", "_prefix"];
	_pf = [["_x"], format ["%1 call %2", _x_parameter_string, _function]]
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

fnc_average_distance_to_nearest_terrain_objects = [["_x",
 						    "_n",
 						    "_types",
 						    "_search_step"], {
 	/* Return the avg dist to nearest _n terrainObjects matching _types */
 	private ["_r", "_found", "_nearest"];
 	_r = _search_step;
 	_found = [];
 	while {(count _found) < _n} do {
 		_nearest = nearestTerrainObjects [_x, _types, _r, true];
 		_found = _found + ([_nearest, 0,
 				    (count _nearest) min
 				    (_n - (count _found))] call fnc_subseq);
 		_r = _r + _search_step;
	};
 	[[["_a", "_b"], {_a + _b}] call fnc_lambda,
 	 [[["_terrainObject", "_p", "_length"], {
 			(_p distance _terrainObject) / _length
 	  }] call fnc_lambda,
 	 _found,
 	 [_x, _n]] call fnc_mapwith] call fnc_reduce
}] call fnc_lambda;


/////////////////////////////////// UNTESTED //////////////////////////////////
fnc_average_distance_to_nearest_array_members = [["_x", "_n", "_array"], {
 	/* Return the avg dist to nearest _n members of _array */
 	_distances = [[] call fnc_lambda,
 		      _array,
 		      [_x]] call fnc_mapwith;
 	_sorted = [_distances,
 		   [] call fnc_lambda] call fnc_sorted;
 	[[["_a", "_b"], {_a + _b}] call fnc_lambda,
 	 [[["_distance", "_length"], {
 		 _distance / _length
 	  }] call fnc_lambda,
 	  [_sorted, 0, _n] call fnc_subseq,
 	  [_n]] call fnc_mapwith] call fnc_reduce
}] call fnc_lambda;
/////////////////////////////////// UNTESTED //////////////////////////////////


fnc_building_positions_nearby = [["_x", "_dist"], {
	/* Return the number of building positions nearby */
	private ["_houses", "_positions"];
	_houses = _x nearObjects ["house", _dist];
	_positions = [];
	for "_i" from 0 to ((count _houses) - 1) do {
		_positions = _positions + ((_houses select _i) buildingPos -1);
	};
	count _positions
}] call fnc_lambda;


fnc_buildings_nearby = [["_x", "_radius"], {
	/* Return the number of buildings nearby */
	count ((position _x) nearObjects ["House", _radius])
}] call fnc_lambda;


fnc_check_level = [["_p", "_step", "_steps"], {
	/* Check a grid over position of _x and return the average delta-z */
	private ["_group", "_centerPosition", "_offset", "_cornerX",
		 "_cornerY", "_grid", "_logic", "_sum"];
	_group = createGroup sideLogic;
	_centerPosition = getPosATL _p;
	_offset = _steps * _step;
	_cornerX = (_centerPosition select 0) - _offset;
	_cornerY = (_centerPosition select 1) - _offset;
	_grid = [];
	for "_i" from 0 to (_steps * 2) do {
		for "_j" from 0 to (_steps * 2) do {
			_logic = _group createUnit
				["LOGIC",
				 [_cornerX + (_step * _i),
				  _cornerY + (_step * _j),
				  _centerPosition select 2],
				 [], 0, ""];
			_grid = _grid + [_logic];
		};
	};
	_sum = [[["_a", "_b"], {_a + _b}] call fnc_lambda,
		[[["_x", "_baseline"], {
			private ["_diff"];
			_diff = abs (((getPosASL _x) select 2) - _baseline);
			deleteVehicle _x;
			(_diff * _diff)
		 }] call fnc_lambda,
		_grid,
		[(getPosASL _p) select 2]]
		call fnc_mapwith] call fnc_reduce;
	deleteGroup _group;
	sqrt (_sum / (_steps * _steps))
}] call fnc_lambda;


fnc_closest_building = [["_x"], {
	/* Get distance to the nearest building */
	private ["_building"];
	_building = nearestBuilding _x;
	_x distance _building
}] call fnc_lambda;


fnc_forests_nearby = [["_x", "_radius"], {
	/* Return count of nearby forest objects within radius */
	count (nearestTerrainObjects [_x,
				      ["Forest Border",
				       "Forest Triangle",
				       "Forest Square",
				       "Forest"],
				      _radius,
				      false])
}] call fnc_lambda;


fnc_get_elevation = [["_x"], {
	/* Get elevation (m) of _x */
	(getPosASL _x) select 2
}] call fnc_lambda;


fnc_get_elevation_target_height = [["_x"], {
	/* Return height of elevation_target relative to _x */
	([_x getVariable "elevation_target"] call fnc_get_elevation) -
	([_x] call fnc_get_elevation)
}] call fnc_lambda;


fnc_intersections_nearby = [["_x", "_dist"], {
	/* Count intersections near _x within _dist */
	count ([_x, _dist] call fnc_find_intersections)
}] call fnc_lambda;


fnc_LOS_to_array = [["_p",
		     "_array",
		     "_eye_height",
		     "_is_unit_array"], {
	/* Sum of 0..1 visibility scores for each array member */
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
		_v = _visibilityParams checkVisibility
			[[(getPosASL _p) select 0,
			  (getPosASL _p) select 1,
			  ((getPosASL _p) select 2) + _eye_height],
			 _target];
		_sum = _sum + _v;
	} forEach _array;
	_sum
}] call fnc_lambda;


fnc_partial_LOS_to_array = [["_p",
			     "_array",
			     "_eye_height",
			     "_full_LOS_bias",
			     "_no_LOS_weight",
			     "_is_unit_array"], {
	/* Ratio of occluded LOS to array of logics or units */
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


fnc_roads_nearby = [["_x", "_dist"], {
	/* Count roads near _x within _dist */
	count ([_x, _dist] call fnc_find_roads)
}] call fnc_lambda;


/////////////////////////////////// UNTESTED //////////////////////////////////
fnc_surface_is_water = [["_x"], {
	/* If surface is water, returns 1, otherwise 0 */
	if (surfaceIsWater (position _x)) then {1} else {0}
}] call fnc_lambda;
/////////////////////////////////// UNTESTED //////////////////////////////////


fnc_units_nearby = [["_x", "_units", "_dist"], {
	/* Count members of _units within _dist of _x */
	count ([_x, _units, _dist] call fnc_neighbors)
}] call fnc_lambda;


fnc_vegetation_nearby = [["_x", "_radius"], {
	/* Count nearby trees and bushes within radius */
	count (nearestTerrainObjects [_x,
				      ["Tree",
				       "Small Tree",
				       "Bush"],
				      _radius,
				      false])
}] call fnc_lambda;

///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// NORMALIZED OBJECTIVE FUNCTIONS OF A SINGLE PARTICLE: //  Starter/Examples
///////////////////////////////////////////////////////////////////////////////

// Cost function for not being above elevation target:
OPT_fnc_above_elevation_target = [true, -5000, 5000,
				  '[_x]',
				  fnc_get_elevation_target_height]
                                  call fnc_to_cost_function;


// Cost function for not being below elevation target:
OPT_fnc_below_elevation_target = [false, -5000, 5000,
				  '[_x]',
				  fnc_get_elevation_target_height]
                                  call fnc_to_cost_function;


// Cost for not having [0..5] building positions within 15m:
OPT_fnc_building_positions_nearby = [true, 0, 5,
				     '[_x, 15]',
				     fnc_building_positions_nearby]
	                             call fnc_to_cost_function;


// Cost function for not being near [3..8] civs in civArray within 100m:
OPT_fnc_civilians_nearby = [true, 3, 8,
			    '[_x, civArray, 100]',
			    fnc_units_nearby]
	                    call fnc_to_cost_function;


// Cost function for being close (w/in 50-300m) to player position:
OPT_fnc_distance_from_player = [true, 50, 300,
				'[position _x, position player]',
				fnc_euclidean_distance]
                                call fnc_to_cost_function;


// Cost for having [0..6] roads within 7.5m:
OPT_fnc_distance_from_roads = [false, 0, 6,
			       '[_x, 7.5]',
			       fnc_roads_nearby]
	                       call fnc_to_cost_function;


// Cost function for being close to designated targets:
OPT_fnc_distance_from_targets = [true, 35, 200,
				 '[position _x,
                                   ([[["_t"], {position _t}] call fnc_lambda,
                                     _x getVariable "targets"] 
                                     call fnc_map) call fnc_vector_mean]',
				 fnc_euclidean_distance]
                                 call fnc_to_cost_function;


// Cost function for not being near a fuel station:
OPT_fnc_fuel_station_nearby = [false, 0, 2500,
 			       '[_x, 1, ["FUELSTATION"], 300]',
 			       fnc_average_distance_to_nearest_terrain_objects]
 	                       call fnc_to_cost_function;


// Cost function for not being fairly level at a 10m radius:
OPT_fnc_level_surface = [false, 0.35, 1.5,
			 '[_x, 5, 2]',
			 fnc_check_level]
                         call fnc_to_cost_function;


/////////////////////////////////// UNTESTED //////////////////////////////////
// Cost function for not having LOS to player group:
OPT_fnc_LOS_to_player_group = [false, 0, 1,
			       '[_x, units group player, 1.6, true]',
			       fnc_LOS_to_array]
	                       call fnc_to_cost_function;
/////////////////////////////////// UNTESTED //////////////////////////////////


/////////////////////////////////// UNTESTED //////////////////////////////////
// Cost function for not having LOS to targets:
OPT_fnc_LOS_to_targets = [false, 0, 1,
			  '[_x, _x getVariable "targets", 1.6, false]',
			  fnc_LOS_to_array]
                          call fnc_to_cost_function;
/////////////////////////////////// UNTESTED //////////////////////////////////


/////////////////////////////////// UNTESTED //////////////////////////////////
// Cost function for having LOS to player group:
OPT_fnc_no_LOS_to_player_group = [true, 0, 1,
				  '[_x, units group player, 1.6, true]',
				  fnc_LOS_to_array]
                                  call fnc_to_cost_function;
/////////////////////////////////// UNTESTED //////////////////////////////////


/////////////////////////////////// UNTESTED //////////////////////////////////
// Cost function for having LOS to targets:
OPT_fnc_no_LOS_to_targets = [true, 0, 1,
			     '[_x, _x getVariable "targets", 1.6, false]',
			     fnc_LOS_to_array]
                             call fnc_to_cost_function;
/////////////////////////////////// UNTESTED //////////////////////////////////


// Cost function for not having occluded LOS to player group:
OPT_fnc_partial_LOS_to_player_group = [false, 0, 1,
				       '[_x, units group player, 
                                         1.6, 0, 0.5, true]',
				       fnc_partial_LOS_to_array]
                                       call fnc_to_cost_function;


// Cost function for not having occluded LOS to designated targets:
OPT_fnc_partial_LOS_to_targets = [false, 0, 1,
				  '[_x,
				    _x getVariable "targets",
                                    1.6, 0, 0.5, false]',
				  fnc_partial_LOS_to_array]
                                  call fnc_to_cost_function;


/////////////////////////////////// UNTESTED //////////////////////////////////
// Cost function for being on water [binary]:
OPT_fnc_surface_is_water = [false, 0, 1, '[_x]',
			    fnc_surface_is_water]
                            call fnc_to_cost_function;
/////////////////////////////////// UNTESTED //////////////////////////////////


/////////////////////////////////// UNTESTED //////////////////////////////////
// Cost function for not being on water [binary]:
OPT_fnc_surface_is_not_water = [true, 0, 1, '[_x]',
				fnc_surface_is_water]
                                call fnc_to_cost_function;
/////////////////////////////////// UNTESTED //////////////////////////////////


// Cost function for not being near [3..8] targets within 100m:
OPT_fnc_targets_nearby = [true, 3, 8,
                          '[_x, _x getVariable "targets", 100]',
			  fnc_units_nearby]
	                  call fnc_to_cost_function;


// Cost function for not being clear of vegetation at a 15m radius:
OPT_fnc_vegetation_clear = [false, 0, 5,
			    '[_x, 15]',
			    fnc_vegetation_nearby]
	                    call fnc_to_cost_function;


// Cost function for not having vegetation within 10m:
OPT_fnc_vegetation_dense = [true, 2, 10,
			    '[_x, 10]',
			    fnc_vegetation_nearby]
	                    call fnc_to_cost_function;

///////////////////////////////////////////////////////////////////////////////
