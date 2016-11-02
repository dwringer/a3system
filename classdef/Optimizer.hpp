/*
  Optimizer class
    :: Optimizer -> ObjectRoot

  Methods:
   __init__ n particle_classname :: Initialize w/ population of n particles
   get_position                  :: Determine mean position vector of population
   position_offsets              :: Get population position offsets from mean
   set_position position         :: Move population center and reposition all
   uniform_position position     :: Move all population to the same position
   report_position               :: Report all population positions and mean
   conform_positions positions   :: Distribute population across positions
   conform_units units           :: Distribute population across unit positions
   perturb n radius              :: Perturb population by n-dimensional radius

      This class represents a generic optimization algorithm implementation.  A
  population of individuals is kept over which various evolutionary algorithms
  can be applied.

  Example:
   N/A - untested - unimplemented

*/

DEFCLASS("Optimizer") ["_self", "_n", "_particle_classname"] DO {
	/* Instantiate optimizer population with n particles */
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "population", []] call fnc_tell;
	private ["_p", "_position"];
	for "_i" from 1 to _n do {
		_p = [_particle_classname] call fnc_new;
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
		_position = _position + [_component];
	};
	_self setPos ([_position, 0, 3] call fnc_subseq);
	_position
} ENDMETHOD;


DEFMETHOD("Optimizer", "position_offsets") ["_self"] DO {
	/* Return each population member's distance from group center */
	private ["_position", "_population", "_offsets", "_p", "_offset"];
	_position = [_self, "get_position"] call fnc_tell;
	_population = [_self, "_getf", "population"] call fnc_tell;
	_offsets = [];
	for "_i" from 0 to ((count _population) - 1) do {
		_p = _population select _i;
		_offset = [[["_a", "_b"], {_a - _b}] call fnc_lambda,
			  [_p, "get_position"] call fnc_tell,
			  _position] call fnc_map;
		_offsets = _offsets + [_offset];
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


DEFMETHOD("Optimizer", "perturb") ["_self", "_n", "_radius"] DO {
	/* Randomly perturb each population member up to radius in n-dims */
	private ["_population", "_position", "_constants", "_variables",
	         "_newPos"];
	_population = [_self, "_getf", "population"] call fnc_tell;
	for "_i" from 0 to ((count _population) - 1) do {
		_position = [_population select _i,
		             "get_position"] call fnc_tell;
		_constants = [_position, _n, 0] call fnc_subseq;
		_variables = [_position, 0, _n] call fnc_subseq;
		while (true) do {
			scopeName "randomPlacement";
			_newPos = [];
			for "_j" from 0 to ((count _variables) - 1) do {
				_newPos = _newPos +
                                          [(_variables select _j) -
                    		           _radius +
                                           random (2 * _radius)];
       			};
			if ((sqrt ([[["_a", "_b"],
		                     {_a + _b}] call fnc_lambda,
                                    [[["_x"],
                                      {_x * _x}] call fnc_lambda,
                                     _newPos] call fnc_map
			           ] call fnc_reduce)) <=
			    _radius) then {
				breakOut "randomPlacement";
                        };
		};
		_newPos = _newPos + _constants;
		[_population select _i, "set_position", _newPos] call fnc_tell;
	};
} ENDMETHOD;
