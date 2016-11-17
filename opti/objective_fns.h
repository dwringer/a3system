component_fnc_units_nearby = [["_x", "_units", "_dist", "_min", "_max"], {
	/* Parametric cost for not having a certain number of units nearby */
	private ["_count"];
	_count = count ([_x, _units, _dist] call fnc_neighbors);
	(1 min (0 max ((_count - _min) / (_max - _min))))
}] call fnc_lambda;


component_fnc_partial_LOS_to_array_members = [["_p",
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
		_v = (1 - ([vehicle _p, "VIEW", vehicle _x] checkVisibility
		            [[(getPosASL _p) select 0, 
                              (getPosASL _p) select 1, 
		              ((getPosASL _p) select 2) + _eye_height], 
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


component_fnc_distance_from_position = [["_x", "_pos", "_min", "_max"], {
	/* Parametric cost for being close to a position */
	(1 min
	 (0 max
	  (([_pos, _x] call fnc_euclidean_distance) - _min) /
	  (_max - _min)))
}] call fnc_lambda;


fnc_find_intersections = [["_x", "_dist"], {
	/* Find all intersections within a certain radius of an entity */
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
	/* Given a start & some road segments, trace a singly connected path */
	private ["_trace", "_next", "_connected", "_found", "_newConnections"];
	_trace = [];
	_next = _start;
	_connected = roadsConnectedTo _start;
	while {True} do {
		scopeName "TracingPath";
		_found = false;
		for "_i" from 0 to ((count _connected) - 1) do {
			scopeName "CheckingUniqueness";
			_next = _connected select _i;
			_newConnections = roadsConnectedTo _next;
			if ((not (_next in _trace)) and
                            (not (count (_newConnections) > 2)) and
			    (_next in _candidates)) then {
				_trace = _trace + [_next];
   			        _connected = _newConnections;
				_found = true;
				breakOut "CheckingUniqueness";
			};
		};
		if (not _found) then {
			breakOut "TracingPath";
		};
	};
	_trace
}] call fnc_lambda;


fnc_find_roads = [["_p", "_dist"], {
	/* Attempt to find all distinct road paths within a certain radius */
	private ["_stems", "_roads", "_segments", "_road", "_connections",
	         "_last", "_next", "_edge", "_c"];
	_stems = [];
	_roads = [];

	// Collect stems from intersections
	{
		_stems = _stems + (roadsConnectedTo _x);
	} forEach ([_p, _dist] call fnc_find_intersections);

	// Prepare list of available segments
	_segments = _p nearRoads _dist;

	// Collect roads begun from stems and make segments unavailable:
	{
		_road = [_x, _segments] call fnc_trace_road;
		if ((count _road) > 0) then {
			_roads = _roads + [_road];
			_segments = _segments - _road;
		} else {
			_segments = _segments - [_x];
		};
	} forEach _stems;

	// While unassigned segments remain:
        while {(count _segments) > 0} do {
	        // Set first segment as edge
	        _edge = _segments select 0;
	        _next = _edge;
                while {_next in _segments} do {
                        scopeName "JumpToEdge";
                        // Remember last loc to check progress
                 	_last = _edge;  
	                // Advance edge position toward boundary
                        _edge = _next;
                   	// Get next round of possible advancements
	                _connections = roadsConnectedTo _edge;
                        if ((count _connections) > 0) then {
		                // Find next connected pos
				for "_i" from 0 to
					      ((count _connections) - 1) do {
					scopeName "MoveAlong";
					_c = _connections select _i;
					if (_c != _last) then {
						// If progress, proceed.
						_next = _c;
						breakOut "MoveAlong";
				        };
				};
				if (_next == (_segments select 0)) then {
					// We have looped, so we are done.
					breakOut "JumpToEdge";
				};
		        } else {
				// Nowhere to go; we are done.
				breakOut "JumpToEdge";
			};
                };
		
		// Trace road from edge segment, add it, and remove segments
		_road = [_edge, _segments] call fnc_trace_road;
		if ((count _road) > 0) then {
			_roads = _roads + [_road];
			_segments = _segments - _road;
		} else {
			_segments = _segments - [_edge];
		};
	};

	// Return resultant list of roads
	_roads
}] call fnc_lambda;


component_fnc_roads_nearby = [["_x", "_dist", "_min", "_max"], {
	/* Parametric cost for not having a certain number of units nearby */
	private ["_count"];
	_count = count ([_x, _dist] call fnc_find_roads);
	(1 min (0 max ((_count - _min) / (_max - _min))))
}] call fnc_lambda;


OPT_fnc_roads_nearby = [["_x"], {
	/* Cost function for having roads nearby */
	[_x, 10, 0, 10] call component_fnc_roads_nearby
}] call fnc_lambda;


OPT_fnc_building_positions_nearby = [["_x"], {
	/* Cost function for not having building positions nearby */
	(1 - ([_x, 35, 0, 10] call component_fnc_building_positions_nearby));
}] call fnc_lambda;


OPT_fnc_civilians_nearby = [["_x"], {
	/* Cost function for not being near civs in civArray */
	(1 - ([_x, civArray, 100, 0, 5] call component_fnc_units_nearby));
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


OPT_fnc_distance_from_targets = [["_x"], {
	/* Cost function for being close to designated targets */
	private ["_targets", "_positions", "_position", "_alen", "_component"];
	_targets = _x getVariable ["targets", []];
	_positions = [[["_t"], {position _t}] call fnc_lambda,
		      _targets] call fnc_map;
	_position = [];
	_alen = count _targets;
	for "_i" from 0 to 2 do {
		_component = 0;
		for "_j" from 0 to (_alen - 1) do {
			_component = _component +
			        (((_positions select _j) select _i) / _alen);
		};
		_position = _position + [_component];
	};
	1 - ([position _x, _position, 50, 300]
	     call component_fnc_distance_from_position);
}] call fnc_lambda;


fnc_intersection_ambush = [["_killzone_logic", "_radius"], {
    private ["_opti", "_targets"];
    _opti = ["Optimizer", 15, "Particle"] call fnc_new;  
    [_opti, "conform_units",
     [_killzone_logic, _radius] call fnc_find_intersections]
     call fnc_tell;   
    [_opti, "radial_scatter_2d", 50, 80] call fnc_tell;
    _targets = [killzone, 60] call fnc_find_intersections;
    {
        [_x, "_setf", "targets", _targets] call fnc_tell
    } forEach (_opti getVariable "population");  
    [_opti, "add_objective",
     OPT_fnc_roads_nearby] call fnc_tell;
    [_opti, "add_objective", 
     OPT_fnc_distance_from_targets] call fnc_tell; 
    [_opti, "add_objective",  
     OPT_fnc_partial_LOS_to_player_group] call fnc_tell;  
    [_opti, "add_objective", 
     OPT_fnc_civilians_nearby] call fnc_tell; 
    _opti spawn {
        private ["_optimizer", "_handle", "_bins"]; 
	_optimizer = _this;
	for "_i" from 0 to 5 do {  
	      _handle = [_optimizer, "MODE_step"] call fnc_tells;  
	      waitUntil {scriptDone _handle};  
	};  

	_bins = [_optimizer, "non_dominated_sort"] call fnc_tell; 

	{[[["_y"],  
	    {[_y, "hide"] call fnc_tell}] call fnc_lambda, 
	    _x] call fnc_map 
	} forEach ([_bins, 1, 0] call fnc_subseq); 
	hint str _bins;
	if ((count _bins) > 1) then { 
		     [100, _bins select 0] execVM "mkcivs\layAmbush.sqf"; 
  	} else {
	   {[_x, "hide"] call fnc_tell;
	    deleteVehicle _x} forEach (_bins select 0);
        }; 
    };  
}] call fnc_lambda;
