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
	/* Trace a singly connected path given a start [& opt road segments] */
	private ["_trace", "_next", "_connected", "_found", "_newConnections",
		 "_continue"];
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
                            (not (count (_newConnections) > 2))) then {
				_continue = true;
				if (not isNil "_candidates") then {
					if (not (_next in _candidates)) then {
						_continue = false;
					};
				};
				if (_continue) then {
					_trace = _trace + [_next];
					_connected = _newConnections;
					_found = true;
					breakOut "CheckingUniqueness";
				};
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
	// Collect stems from intersections:
	{
		_stems = _stems + (roadsConnectedTo _x);
	} forEach ([_p, _dist] call fnc_find_intersections);
	// Prepare list of available segments:
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
	        // Set first segment as edge:
	        _edge = _segments select 0;
	        _next = _edge;
                while {_next in _segments} do {
                        scopeName "JumpToEdge";
                        // Remember last loc to check progress:
                 	_last = _edge;  
	                // Advance edge position toward boundary:
                        _edge = _next;
                   	// Get next round of possible advancements:
	                _connections = roadsConnectedTo _edge;
                        if ((count _connections) > 0) then {
		                // Find next connected position:
				for "_i" from 0 to
					      ((count _connections) - 1) do {
					scopeName "MoveAlong";
					_c = _connections select _i;
					if (_c != _last) then {
						// If progress, proceed:
						_next = _c;
						breakOut "MoveAlong";
				        };
				};
				if (_next == (_segments select 0)) then {
					// We have looped, so we are done:
					breakOut "JumpToEdge";
				};
		        } else {
				// Nowhere to go; we are done:
				breakOut "JumpToEdge";
			};
                };
		// Trace road from edge segment, add it, and remove segments:
		_road = [_edge, _segments] call fnc_trace_road;
		if ((count _road) > 0) then {
			_roads = _roads + [_road];
			_segments = _segments - _road;
		} else {
			_segments = _segments - [_edge];
		};
	};
	// Return resultant list of roads:
	_roads
}] call fnc_lambda;
