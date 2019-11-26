/*
  Optimizer class
    :: Optimizer -> ObjectRoot

  Methods:
   __init__                      :: Initialize w/ population of n particles
       n                  
       particle_classname 
   get_position                  :: Determine mean position vector of population
   position_offsets              :: Get population position offsets from mean
   set_position                  :: Move population center and reposition all
       position
   uniform_position              :: Move all population to the same position
       position
   report_position               :: Report all population positions and mean
   conform_positions             :: Distribute population across positions
       positions
   conform_units                 :: Distribute population across unit positions
       units
   do_nothing                    :: Pass without modifications
   fit_terrain                   :: Adjust population to terrain elevation
   perturb                       :: Perturb population by n-dimensional radius
       n
       radius
   radial_scatter_2d             :: Scatter points between min/max radius in 2d
       min_radius
       max_radius
   add_objective                 :: Push objective function to each individual
       objective_fn
   evaluate_objectives           :: Matrix of all individuals' objective evals
   de_candidates                 :: Create second population via Diff. Evol.
       weight
       freqeuency
   non_dominated_sort            :: Bin pop. by NSGA-II domination ranks (asc.)
   sorted_average_distances_3d   :: Sort subpop by avg 3-d distance to others
       subpop
   sorted_average_distances      :: Sort subpop by avg N-d distance to others
       subpop
   moea_step                     :: Multi-objective evolutionary algorithm step
       candidate_generation_method
       candidate_generation_params
       preevaluation_method       
       preevaluation_params       
       bin_creation_method        
       bin_creation_params        
       bin_ordering_method        
       bin_ordering_params        
   MODE_step                     :: Multi-Objective Differential Evolution step

      This class represents a generic optimization algorithm implementation.  A
  population of individuals is kept over which various evolutionary algorithms
  can be applied.  Candidate solutions are kept as separate object instances,
  providing for full locality but severely limited performance on large 
  population sizes.

  Example:
      opti = ["Optimizer", 15, "Particle"] call fnc_new;  
      [opti, "conform_units", units group player] call fnc_tell;   
      [opti, "radial_scatter_2d", 100, 120] call fnc_tell;  
      [opti, "add_objective",  
       OPT_fnc_partial_LOS_to_player_group] call fnc_tell;  
      [opti, "add_objective", 
       OPT_fnc_distance_from_player] call fnc_tell; 
      [opti, "add_objective",
       OPT_fnc_roads_nearby] call fnc_tell;
      [opti, "add_objective", 
       OPT_fnc_civilians_nearby] call fnc_tell; 
      opti spawn {  
	  private ["_handle", "_bins"]; 

	  for "_i" from 0 to 5 do {  
	      _handle = [opti, "MODE_step"] call fnc_tells;  
	      waitUntil {scriptDone _handle};  
	  };  

	  _bins = [opti, "non_dominated_sort"] call fnc_tell; 

	  {[[["_y"],  
	    {[_y, "hide"] call fnc_tell}] call fnc_lambda, 
	    _x] call fnc_map 
	  } forEach ([_bins, 1, 0] call fnc_subseq); 
	  hint str _bins;
	  if ((count _bins) > 1) then { 
		     [100, _bins select 0] execVM "mkcivs\layAmbush.sqf"; 
          }; 
      };  

*/

DEFCLASS("Optimizer") ["_self", "_n", "_particle_classname", "_particle_color"] DO {
	/* Instantiate optimizer population with n particles */
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "population", []] call fnc_tell;
	private ["_p", "_position"];
	if (isNil "_particle_color") then {
		_particle_color = ["ColorBlack",
				   "ColorGrey",
				   "ColorRed",
				   "ColorBrown",
				   "ColorOrange",
				   "ColorYellow",
				   "ColorKhaki",
				   "ColorGreen",
				   "ColorBlue",
				   "ColorPink",
				   "ColorWhite"]
				   select ([11] call fnc_randint);
	};
	for "_i" from 1 to _n do {
	        _p = [_particle_classname, _particle_color] call fnc_new;
                if (isNil "_position") then {
			_position = [_p, "get_position"] call fnc_tell;
		};
		[_self, "_push_attr", "population", _p] call fnc_tell;
	};
	_self setPos ([_position, 0, 3] call fnc_subseq);
	_self
} ENDCLASS;


DEFMETHOD("Optimizer", "get_position") ["_self"] DO {
	/* Determine mean position of population and set to object */
	private ["_positions", "_alen", "_position", "_component"];
	_positions = [[["_x"], {position _x}] call fnc_lambda,
		      [_self, "_getf", "population"] call fnc_tell
		     ] call fnc_map;
	_alen = count _positions;
	_position = [];
	for "_i" from 0 to 2 do {
		_component = 0;
		for "_j" from 0 to (_alen - 1) do {
			_component = _component +
			        (((_positions select _j) select _i) / _alen);
		};
		_position pushBack _component;
	};
	_self setPos ([_position, 0, 3] call fnc_subseq);
	_position
} ENDMETHOD;


DEFMETHOD("Optimizer", "position_offsets") ["_self"] DO {
	/* Return each population member's distance from group center */
	private ["_position", "_population", "_offsets", "_fn_getOffset",
		 "_p", "_offset"];
	_position = [_self, "get_position"] call fnc_tell;
	_population = [_self, "_getf", "population"] call fnc_tell;
	_offsets = [];
	_fn_getOffset = [["_a", "_b"], {_a - _b}] call fnc_lambda;
	for "_i" from 0 to ((count _population) - 1) do {
		_p = _population select _i;
		_offset = [_fn_getOffset,
			   [_p, "get_position"] call fnc_tell,
			   _position] call fnc_map;
		_offsets pushBack _offset;
	};
	_offsets
} ENDMETHOD;


DEFMETHOD("Optimizer", "set_position") ["_self", "_position"] DO {
	/* Move population center to specified coordinates */
	private ["_population", "_offsets", "_pos"];
	_population = [_self, "_getf", "population"] call fnc_tell;
	_offsets = [_self, "position_offsets"] call fnc_tell;
	_self setPos ([_position, 0, 3] call fnc_subseq);
	for "_i" from 0 to ((count _population) - 1) do {
		_pos = [];
		for "_j" from 0 to ((count _position) - 1) do {
			_pos = _pos +
			[(_position select _j) +
			 ((_offsets select _i) select _j)];
		};
		[_population select _i, "set_position", _pos] call fnc_tell;
	};
} ENDMETHOD;


DEFMETHOD("Optimizer", "uniform_position") ["_self", "_position"] DO {
	/* Place every population individual at the same position */
	private ["_population"];
	[_self, "set_position", _position] call fnc_tell;
	_population = [_self, "_getf", "population"] call fnc_tell;
	for "_i" from 0 to ((count _population) - 1) do {
		[_population select _i, "set_position",
 		 _position] call fnc_tell;
	};
} ENDMETHOD;


DEFMETHOD("Optimizer", "report_position") ["_self"] DO {
	/* Provide a formatted string with position readouts */
	private ["_posString", "_population"];
	_posString = "";
	_population = [_self, "_getf", "population"] call fnc_tell;
	for "_i" from 0 to ((count _population) - 1) do {
		_posString = format ["%1%2\n", _posString,
                                     [_population select _i,
                                      "get_position"] call fnc_tell];
        };
	_posString = format ["%1-------------\n%2", _posString,
	                     [_self, "get_position"] call fnc_tell];
	_posString
} ENDMETHOD;


DEFMETHOD("Optimizer", "conform_positions") ["_self", "_positions"] DO {
	/* Distribute population across specified positions */
	private ["_population"];
	_positions = _positions call fnc_shuffle;
	_population = [_self, "_getf", "population"] call fnc_tell;
	for "_i" from 0 to ((count _population) - 1) do {
		[_population select _i, "set_position",
		 _positions select (_i mod count _positions)] call fnc_tell;
	};
} ENDMETHOD;


DEFMETHOD("Optimizer", "conform_units") ["_self", "_units"] DO {
	/* Distribute population across positions of specified units */
	[_self, "conform_positions",
         [[["_x"], {position _x}] call fnc_lambda, _units] call fnc_map
	] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Optimizer", "fit_terrain") ["_self"] DO {
	/* Adjust population to terrain elevation */
	private ["_pos"];
        {
		_pos = position _x;
		_pos set [2, (_pos select 2) -
		             ((getPosATL _x) select 2)];
		_x setPos _pos;
	} forEach ([_self, "_getf", "population"] call fnc_tell);
} ENDMETHOD;


DEFMETHOD("Optimizer", "do_nothing") ["_self"] DO {
	/* Do nothing - used for preprocessing */
} ENDMETHOD;


DEFMETHOD("Optimizer", "perturb") ["_self", "_n", "_radius"] DO {
	/* Randomly perturb each population member up to radius in n-dims */
	private ["_population", "_position", "_constants", "_newPos",
		 "_fn_subtract", "_fn_square", "_fn_add", "_posDelta"];
	_population = [_self, "_getf", "population"] call fnc_tell;
	_fn_subtract = [["_a", "_b"], {_a - _b}] call fnc_lambda;
	_fn_square = [["_x"], {_x * _x}] call fnc_lambda;
	_fn_add = [["_a", "_b"], {_a + _b}] call fnc_lambda;
	for "_i" from 0 to ((count _population) - 1) do {
		_position = [_population select _i,
		             "get_position"] call fnc_tell;
		_constants = [_position, _n, 0] call fnc_subseq;
		while {true} do {
			scopeName "randomPlacement";
			_newPos = [];
			for "_j" from 0 to (_n - 1) do {
				_newPos = _newPos +
                                          [(_position select _j) -
                    		           _radius +
                                           random (2 * _radius)];
       			};
			_posDelta = [_fn_subtract,
				     _newPos, _position] call fnc_map;
			if ((sqrt ([_fn_add,
                                    [_fn_square, _posDelta] call fnc_map
				   ] call fnc_reduce)) <=
			    _radius) then {
				breakOut "randomPlacement";
                        };
		};
		_newPos = _newPos + _constants;
		[_population select _i, "set_position", _newPos] call fnc_tell;
	};
} ENDMETHOD;


DEFMETHOD("Optimizer", "radial_scatter_2d") ["_self",
                                             "_min_radius",
                                             "_max_radius"] DO {
        private ["_p", "_theta", "_radius", "_dx", "_dy"];
        {
		_p = [_x, "get_position"] call fnc_tell;
		_theta = 360 * (random 1);
		_radius = _min_radius +
		          ((random 1) * (_max_radius - _min_radius));
		_dx = _radius * (cos _theta);
		_dy = _radius * (sin _theta);
		_p set [0, (_p select 0) + _dx];
		_p set [1, (_p select 1) + _dy];
		[_x, "set_position", _p] call fnc_tell;
        } forEach (_self getVariable "population");
} ENDMETHOD;


DEFMETHOD("Optimizer", "displace_shape") ["_self",
					  "_points",
					  "_heading",
					  "_scale"] DO {
	/* Displace population as into a given shape of points */
	private ["_angle"];
	_angle = 90 - _heading;
	_points = [_points, _scale, _angle] call fnc_scale_and_rotate;
	{
		_i = _x select 0;
		_p = _x select 1;
		[_p, "set_position",
		 [[["_a", "_b"], {_a + _b}] call fnc_lambda,
		  position _p,
		  _points select (_i mod (count _points))] call fnc_map]
		 call fnc_tell;
	} forEach ((_self getVariable "population") call fnc_enumerate);
} ENDMETHOD;


DEFMETHOD("Optimizer", "ring_out") ["_self", "_radius"] DO {
	/* Move population members as into a ring around current positions */
	private ["_population", "_ring"];
	_population = _self getVariable "population";
	_ring = [count _population] call fnc_make_ring;
	[_self, "displace_shape", _ring, random 360, _radius] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Optimizer", "rings_out") ["_self", "_radius", "_leaves"] DO {
	/* Move population members as into rings around current positions */
	private ["_population", "_rings"];
	_population = _self getVariable "population";
	_rings = [count _population, _leaves] call fnc_make_ring_cross;
	[_self, "displace_shape", _rings, random 360, _radius] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Optimizer", "add_objective") ["_self", "_objective_fn"] DO {
	/* Add objective function to each population member */
	{
		[_x, "add_objective", _objective_fn] call fnc_tell;
	} forEach ([_self, "_getf", "population"] call fnc_tell);
} ENDMETHOD;


DEFMETHOD("Optimizer", "evaluate_objectives") ["_self"] DO {
	/* Collect evaluations of each individual's objectives */
	private ["_acc"];
	_acc = [];
	{
		_acc pushBack ([_x, "evaluate_objectives"] call fnc_tell);
	} forEach ([_self, "_getf", "population"] call fnc_tell);
	_acc
} ENDMETHOD;


DEFMETHOD("Optimizer", "de_candidates") ["_self", "_weight", "_frequency"] DO {
	/* Create a second population by differential evolution */
	private ["_population", "_population2", "_others"];
	_population = [_self, "_getf", "population"] call fnc_tell;
	_population2 = [];
	{
		_others = [_population, 4] call fnc_choose;
		switch (_x) do {
			case (_others select 0): {
				_others set [0, _others select 3];
			};
			case (_others select 1): {
				_others set [1, _others select 3];
			};
			case (_others select 2): {
				_others set [2, _others select 3];
			};
		};
		_population2 = _population2 +
		               [[_x, "differential_evolve",
                                 _others select 0,
		                 _others select 1,
		                 _others select 2,
                                 _weight, _frequency] call fnc_tell];
	} forEach _population;
	_population2
} ENDMETHOD;


DEFMETHOD("Optimizer", "non_dominated_sort") ["_self"] DO {
	/* NSGA-II fast non-dominated sort algorithm */
	private ["_bins", "_population", "_domByN", "_y", "_dominated",
	         "_binIndex", "_nextBin", "_xScore", "_yScore",
		 "_fn_multiply", "_fn_1_if_lte_else_0"];
	_bins = [[]];
	_population = [_self, "_getf", "population"] call fnc_tell;
	_fn_multiply = [["_a", "_b"], {_a * _b}] call fnc_lambda;
	_fn_1_if_lte_else_0 = [["_a", "_b"],
			       {if (_a <= _b) then {1}
                                              else {0}}] call fnc_lambda;
	{
		_xScore = [_x, "evaluate_objectives"] call fnc_tell;
		_domByN = 0;
		_x setVariable ["_NSGA_dominates", []];
		for "_i" from 0 to ((count _population) - 1) do {
			_y = _population select _i;
			_yScore = [_y, "evaluate_objectives"] call fnc_tell;
			if (([_fn_multiply,
		              [_fn_1_if_lte_else_0,
                               _xScore, _yScore] call fnc_map
                             ] call fnc_reduce) == 1) then {
				[_x, "_push_attr", "_NSGA_dominates",
				 _y] call fnc_tell;
                        } else {
		                if (([_fn_multiply,
				      [_fn_1_if_lte_else_0,
				       _yScore, _xScore] call fnc_map
				     ] call fnc_reduce) == 1) then {
				_domByN = _domByN + 1;
                                };
                        };
		};
		_x setVariable ["_NSGA_domByN", _domByN];
		if (_domByN == 0) then {
			_bins set [0, (_bins select 0) + [_x]];
		};
	} forEach _population;
	{
		_x setVariable ["computedObjectives", nil];
	} forEach _population;
	_binIndex = 0;
        while {_binIndex < count _bins} do {
	        _nextBin = [];
                {
			_dominated = _x getVariable "_NSGA_dominates";
			for "_i" from 0 to ((count _dominated) - 1) do {
				_y = _dominated select _i;
				_domByN = (_y getVariable "_NSGA_domByN") - 1;
				_y setVariable ["_NSGA_domByN", _domByN];
				if (_domByN == 0) then {
					_nextBin pushBack _y;
				};
			};
		} forEach (_bins select _binIndex);
		_binIndex = _binIndex + 1;
		if ((count _nextBin) > 0) then {
			_bins pushBack _nextBin;
		};
	};
	_bins
} ENDMETHOD;


DEFMETHOD("Optimizer", "sorted_average_distances_3d") ["_self", "_subpop"] DO {
	/* For given subpop, assign to each the avg distance to others */
	private ["_fn_add", "_fn_dist_over_len", "_fn_distAvg_gt"];
	_fn_add = [["_a", "_b"], {_a + _b}] call fnc_lambda;
	_fn_dist_over_len = [["_a", "_b", "_len"],
			     {(_a distance _b) / _len}] call fnc_lambda;
	_fn_distAvg_gt = [["_a", "_b"], {
			      (_a getVariable "_distAvg") >
			      (_b getVariable "_distAvg")
	         	 }] call fnc_lambda;
	{_x setVariable ["_distAvg",
	  [_fn_add,
	   [_fn_dist_over_len,
	    _subpop, [_x, count _subpop]] call fnc_mapwith] call fnc_reduce];
	} forEach _subpop;
	_subpop = [_subpop, _fn_distAvg_gt] call fnc_sorted;
	_subpop	
} ENDMETHOD;


DEFMETHOD("Optimizer", "sorted_average_distances") ["_self", "_subpop"] DO {
	/* For given subpop, assign to each the avg distance to others */
	private ["_fn_add", "_fn_dist_over_len", "_fn_distAvg_gt"];
	_fn_add = [["_a", "_b"], {_a + _b}] call fnc_lambda;
	_fn_dist_over_len = [["_a", "_b", "_len"], {
			         ([[_a, "get_position"] call fnc_tell,
                                   [_b, "get_position"] call fnc_tell
          		          ] call fnc_euclidean_distance) / _len
		            }] call fnc_lambda;
	_fn_distAvg_gt = [["_a", "_b"], {
			      (_a getVariable "_distAvg") >
			      (_b getVariable "_distAvg")
	         	 }] call fnc_lambda;
	{_x setVariable ["_distAvg",
	  [_fn_add,
	   [_fn_dist_over_len,
 	    _subpop, [_x, count _subpop]] call fnc_mapwith] call fnc_reduce];
	} forEach _subpop;
	_subpop = [_subpop, _fn_distAvg_gt] call fnc_sorted;
	_subpop	
} ENDMETHOD;


DEFMETHOD("Optimizer", "moea_step") ["_self",
                                     "_candidate_generation_method",
				     "_candidate_generation_params",
                                     "_preevaluation_method",
				     "_preevaluation_params",
                                     "_bin_creation_method",
				     "_bin_creation_params",
                                     "_bin_ordering_method",
				     "_bin_ordering_params"] DO {
	/* Add candidate solutions, rank then cull to pop size */
	private ["_bins", "_population", "_newPop", "_tgtLength",
	         "_newLength", "_available"];
        _population = [_self, "_getf", "population"] call fnc_tell;
        _tgtLength = count _population;
	_population = _population +
		      (([_self, _candidate_generation_method] +
			_candidate_generation_params) call fnc_tell);
        [_self, "_setf", "population", _population] call fnc_tell;
        if (not isNil "_preevaluation_method") then {
		([_self, _preevaluation_method] +
		 _preevaluation_params) call fnc_tell;
  	};
	_bins = ([_self, _bin_creation_method] +
		 _bin_creation_params) call fnc_tell;
	_newPop = [];
        for "_i" from 0 to ((count _bins) - 1) do {
   	        scopeName "fillFromBins";
		_newLength = count _newPop;
		if ((_tgtLength - _newLength) == 0) then {
			breakOut "fillFromBins";
		};
		_available = _bins select _i;
		if ((_newLength + (count _available)) <= _tgtLength) then {
			_newPop = _newPop + _available;
		} else {
			_available = ([_self, _bin_ordering_method,
				       _available] +
				      _bin_ordering_params) call fnc_tell;
			_newPop = _newPop +
				  ([_available, 0, _tgtLength - _newLength]
				    call fnc_subseq);
                };
	};
	for "_i" from 0 to ((count _population) - 1) do {
		_p = _population select _i;
		if (({_x == _p} count _newPop) == 0) then {
		        [_p, "hide"] call fnc_tell;
                        deleteVehicle _p;
		};
	};
	[_self, "_setf", "population", _newPop] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Optimizer", "MODE_step") ["_self", "_weight", "_frequency"] DO {
	/* Modified Multi-Objective Differential Evolution */
	if (isNil "_weight") then {
		_weight = 0.35;
	};
	if (isNil "_frequency") then {
		_frequency = 0.8;
	};
	[_self, "moea_step",
	 "de_candidates", [_weight, _frequency],
 	 "fit_terrain", [],
	 "non_dominated_sort", [],
	 "sorted_average_distances_3d", []] call fnc_tell;
} ENDMETHODV;
