DEFCLASS("LocationFinder") ["_self", "_pop_size", "_shape_fn"] DO {
	SUPER("ObjectRoot", _self);
	if (isNil "_pop_size") then {_pop_size = 5};
        if (isNil "_shape_fn") then {_shape_fn = fnc_make_ring };
	{_self setVariable [_x select 0, _x select 1];} forEach
	[["populationSize", _pop_size],
 	 ["shape",          [_pop_size] call _shape_fn],
	 ["radius",         105],
	 ["objectives",     [[false, 0.35, 1.5, '[_x, 3, 2]',
			     fnc_check_level]
			    call fnc_to_cost_function]],
	 ["assignments",    [["targets", []]]],
	 ["center",         [position player]],
	 ["color",          "ColorOrange"],
	 ["positionLog",    []]];
	_self
} ENDCLASSV;

DEFMETHOD("LocationFinder", "configure") ["_self", "_config_alist"] DO {
	{_self setVariable [_x select 0, _x select 1];} forEach _config_alist;
} ENDMETHOD;

DEFMETHOD("LocationFinder", "set_location") ["_self", "_location"] DO {
	_self setVariable ["center", _location];
} ENDMETHOD;

DEFMETHOD("LocationFinder", "obj_level_terrain") ["_self"] DO {
	_self setVariable ["objectives", [[false, 0.35, 1.5, '[_x, 3, 2]',
					   fnc_check_level]
					  call fnc_to_cost_function]];;
} ENDMETHOD;

DEFMETHOD("LocationFinder", "obj_landing_zones") ["_self", "_avoid"] DO {
	private ["_objectives", "_assignments"];
	_assignments = _self getVariable "assignments";
	_objectives = [[false, 0.35, 1.5, '[_x, 3, 2]',
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
	if (not (isNil "_avoid")) then {
		if (0 < (count _enemies)) then {
			_assignments = [["_avoid", _avoid]];
			_objectives = _objectives +
				[[false, 0, 1,
				  '[_x, _x getVariable "_avoid", 1.6, true]',
				  fnc_LOS_to_array] call fnc_to_cost_function,
				 [true, 25, 50,
				  '[position _x,
				    ([[["_y"], {position _y}] call fnc_lambda,
				      _x getVariable "_avoid"] call fnc_map)
				    call fnc_vector_mean]',
				  fnc_euclidean_distance]
				 call fnc_to_cost_function];
		};
	};
	_self setVariable [ "assignments", _assignments ];
	_self setVariable [ "objectives",  _objectives  ];
} ENDMETHOD;

DEFMETHOD("LocationFinder", "obj_tactical_approach") ["_self", "_targets"] DO {
	_self setVariable ["assignments", [["targets", _targets]]];
	_self setVariable ["center", [[["_x"], {position _x}] call fnc_lambda,
				      _targets] call fnc_map];
	_self setVariable ["objectives",
			   [OPT_fnc_no_LOS_to_targets,
			    OPT_fnc_extreme_distance_from_targets,
			    OPT_fnc_extreme_distance_to_targets,
			    OPT_fnc_cover_available,
			    OPT_fnc_vegetation_dense,
			    OPT_fnc_distance_to_roads,
			    OPT_fnc_surface_is_not_water]];
} ENDMETHOD;

DEFMETHOD("LocationFinder", "obj_tactical_advantage") ["_self", "_targets", "_avoid_water"] DO {
	private ["_appendix"];
	if (not (isNil "_avoid_water")) then {
		_appendix = [OPT_fnc_surface_is_not_water];
	} else {
		_appendix = [];
	};
	_self setVariable ["assignments", [["targets", _targets]]];
	_self setVariable ["center", [[["_x"], {position _x}] call fnc_lambda,
				      _targets] call fnc_map];
	_self setVariable ["objectives",
	                   [OPT_fnc_building_positions_nearby,
	                    OPT_fnc_cover_available,
	                    OPT_fnc_vegetation_dense,
                            OPT_fnc_distance_from_targets,
			    OPT_fnc_distance_to_targets,
			    OPT_fnc_LOS_to_targets,
	                    OPT_fnc_partial_LOS_to_targets] +
	                   _appendix];
} ENDMETHOD;

DEFMETHOD("LocationFinder", "obj_sniper_nests") ["_self", "_targets", "_avoid_water"] DO {
	private ["_appendix"];
	if (not (isNil "_avoid_water")) then {
		_appendix = [OPT_fnc_surface_is_not_water];
	} else {
		_appendix = [];
	};
	_self setVariable ["assignments", [["targets", _targets]]];
	_self setVariable ["center", [[["_x"], {position _x}] call fnc_lambda,
				      _targets] call fnc_map];
	_self setVariable ["objectives",
	                   [OPT_fnc_cover_available,
	                    OPT_fnc_vegetation_dense,
                            OPT_fnc_long_distance_from_targets,
			    OPT_fnc_LOS_to_targets,
                            OPT_fnc_partial_LOS_to_targets] +
	                   _appendix];
} ENDMETHOD;

DEFMETHOD("LocationFinder", "run") ["_self", "_max_required", "_step_count_target"] DO {
	private ["_result", "_acc"];
	if ( isNil "_max_required" ) then {
		_max_required = _self getVariable "populationSize";
	};
	if ( isNil "_step_count_target" ) then { _step_count_target = 4; };
	_result = [_self getVariable "radius",
		   _self getVariable "center",
		   _self getVariable "assignments",
		   _self getVariable "objectives",
		   _self getVariable "populationSize",
                   _step_count_target,
		   _max_required,
		   [[.35, .8], [.8, .35]], // [[weight-prior, mutation-freq]_0, "_f]
		   _self getVariable "shape",
		   _step_count_target,
		   _self getVariable "color"]
	call fnc_find_positions;
	[_self, "_push_attr", "positionLog", _result] call fnc_tell;
	_acc = [];
	[[["_elt"], {
		if (({
			([position _x,
			  position _elt] call fnc_euclidean_distance) < 1
		    } count _result) < 2) then {
			_acc append [_elt];
		} else {
			[_elt, "hide"] call fnc_tell;
			deleteVehicle _elt;
		};
	}] call fnc_lambda,
	_result] call fnc_mapnil;
	_acc
} ENDMETHODV;

// DEFMETHOD("LocationFinder", "") ["_self"] DO {
// 	private [];
	
// } ENDMETHOD;

// DEFMETHOD("LocationFinder", "") ["_self"] DO {
// 	private [];
	
// } ENDMETHOD;

// DEFMETHOD("LocationFinder", "") ["_self"] DO {
// 	private [];
	
// } ENDMETHOD;
