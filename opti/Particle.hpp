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
   set_marker_* :: Marker.set_*

      This class is a generic particle with a multidimensional position vector
  that can be set and retrieved.  A basic extension of the game's 3-dimensional
  position vectors.

  Example:
   N/A - untested - unimplemented

*/

DEFCLASS("Particle") ["_self"] DO {
	/* Initialize the particle */
	SUPER_ARGS("Marker", _self)
	        [position _self, "ELLIPSE", nil, [5, 5]]
	ENDARGS;
	[_self, "_setf", "extraDimensions", []] call fnc_tell;
	[_self, "_setf", "objectives", []] call fnc_tell;
	[_self, "set_color", "ColorOrange"] call fnc_tell;
	[_self, "set_alpha", 0.95] call fnc_tell;
	[_self, "show"] call fnc_tell;
	_self
} ENDCLASS;


ALIAS("Particle", "set_marker_alpha", "Marker", "set_alpha");
ALIAS("Particle", "set_marker_brush", "Marker", "set_brush");
ALIAS("Particle", "set_marker_color", "Marker", "set_color");
ALIAS("Particle", "set_marker_direction", "Marker", "set_direction");
ALIAS("Particle", "set_marker_position", "Marker", "set_position");
ALIAS("Particle", "set_marker_shape", "Marker", "set_shape");
ALIAS("Particle", "set_marker_size", "Marker", "set_size");
ALIAS("Particle", "set_marker_text", "Marker", "set_text");
ALIAS("Particle", "set_marker_type", "Marker", "set_type");


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
			_computed = _computed + [[_self] call _x];
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
		 "_value"];
	_posX = [_self, "get_position"] call fnc_tell;
        _posA = [_other, "get_position"] call fnc_tell;
	_posB = [_adjunct, "get_position"] call fnc_tell;
	_posC = [_moderator, "get_position"] call fnc_tell;
	_acc = [];
	for "_i" from 0 to ((count _posX) - 1) do {
		if ((random 1) < _frequency) then {
			_acc = _acc + [(_posA select _i) +
				       (_weight * ((_posB select _i) -
                                                   (_posC select _i)))];
		} else {
			_acc = _acc + [_posX select _i];
		};
	};
	_candidate = ["Particle"] call fnc_new;
	[_candidate, "set_position", _acc] call fnc_tell;
	[_candidate, "_setf", "objectives",
	 [_self, "_getf", "objectives"] call fnc_tell] call fnc_tell;
	_candidate	
} ENDMETHOD;
