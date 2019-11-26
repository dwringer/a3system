/*
  Particle class
    :: Particle -> Marker -> ObjectRoot

  Methods:
   set_position position      :: Update position vector (thru position length)
   get_position position      :: Return position vector
   add_objective objective_fn :: Add objective function to list
   evaluate_objectives        :: Collect evaluation of each objective function
   differential_evolve other adjunct moderator weight frequency
                              :: Create new particle via differential evolution

  Aliases:
   set_marker_position :: Marker.set_position

      This class is a generic particle with a multidimensional position vector
  that can be set and retrieved.  A basic extension of the game's 3-dimensional
  position vectors.

  Example:
   N/A - untested - unimplemented

*/

DEFCLASS("Particle") ["_self", "_color"] DO {
	/* Initialize the particle */
	// private ["_markerColor"];
	SUPER_ARGS("Marker", _self)
	        [position _self, "ELLIPSE", nil, [5, 5]]
	ENDARGS;
	[_self, "_setf", "extraDimensions", []] call fnc_tell;
	[_self, "_setf", "objectives", []] call fnc_tell;
	// if (isNil "_color") then {
	// 	_markerColor = "ColorOrange";
	// } else {
	// 	_markerColor = _color;
	// };
	// [_self, "set_color", _markerColor] call fnc_tell;
	// [_self, "set_alpha", 0.95] call fnc_tell;
	// [_self, "show"] call fnc_tell;
	_self
} ENDCLASS;


ALIAS("Particle", "set_marker_position", "Marker", "set_position");


DEFMETHOD("Particle", "items") ["_self"] DO {
	/* Return a list of copiable key, value pairs for general attributes */
        private ["_keys", "_acc"];
	_keys = [_self, "_locals"] call fnc_tell;
	_keys = _keys - ["marker",
			 "name",
			 "_NSGA_dominates",
			 "_NSGA_domByN",
			 "computedObjectives"];
	_acc = [[["_k", "_d"],  
                {[_d, "_getf", _k] call fnc_tell}] call fnc_lambda,
	        _keys, [_self]] call fnc_mapwith;
	[_keys, _acc] call fnc_zip
} ENDMETHOD;


DEFMETHOD("Particle", "set_position") ["_self", "_position"] DO {
	/* Set particle's position vector up to position length */
	private ["_currentExtras", "_newExtras"];
	_currentExtras = [_self, "_getf", "extraDimensions"] call fnc_tell;
	_newExtras = [_position, 3, 0] call fnc_subseq;
	if ((count _newExtras) < (count _currentExtras)) then {
		_newExtras = _newExtras +
			([_currentExtras, count _newExtras, 0] call fnc_subseq);
	};
	_self setPos ([_position, 0, 3] call fnc_subseq);
	[_self, "_setf", "extraDimensions", _newExtras] call fnc_tell;
	[_self, "set_marker_position", _position] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Particle", "get_position") ["_self"] DO {
	/* Return particle's full position vector */
	(position _self) + ([_self, "_getf", "extraDimensions"] call fnc_tell)
} ENDMETHOD;


DEFMETHOD("Particle", "add_objective") ["_self", "_objective_fn"] DO {
	/* Add an objective function to this particle's list */
	[_self, "_push_attr", "objectives", _objective_fn] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Particle", "evaluate_objectives") ["_self"] DO {
	/* Evaluate this particle's list of objective functions */
	private ["_computed"];
	_computed = _self getVariable "computedObjectives";
	if (isNil "_computed") then {
		_computed = [];
		{
			_computed pushBack ([_self] call _x);
		} forEach (_self getVariable "objectives");
		_self setVariable ["computedObjectives", _computed];
	};
	_computed
} ENDMETHOD;


DEFMETHOD("Particle", "differential_evolve") ["_self", "_other",
                                              "_adjunct", "_moderator",
                                              "_weight", "_frequency"] DO {
	/* Differential evolve given three other particles and params */
        private ["_posX", "_posA", "_posB", "_posC", "_acc", "_candidate",
		 "_key", "_value", "_changes"];
	_posX = [_self, "get_position"] call fnc_tell;
        _posA = [_other, "get_position"] call fnc_tell;
	_posB = [_adjunct, "get_position"] call fnc_tell;
	_posC = [_moderator, "get_position"] call fnc_tell;
	_changes = 0;
	_acc = [];
	while {_changes == 0} do {
		for "_i" from 0 to ((count _posX) - 1) do {
			if ((random 1) < _frequency) then {
				_acc pushBack ((_posA select _i) +
					       (_weight *
						((_posB select _i) -
						 (_posC select _i))));
				_changes = _changes + 1;
			} else {
				_acc pushBack (_posX select _i);
			};
		};
		if (_changes == 0) then {
			_acc = [];
		};
	};
	_candidate = ["Particle"] call fnc_new;
	{
		_key = _x select 0;
		_value = _x select 1;
		if (not isNil "_value") then {
			[_candidate, "_setf", _key, _value] call fnc_tell;
		};
	} forEach ([_self, "items"] call fnc_tell);
	[_candidate, "set_position", _acc] call fnc_tell;
	_candidate	
} ENDMETHOD;
