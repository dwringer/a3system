/*
  Particle class
    :: Particle -> Marker -> ObjectRoot

  Methods:
   set_position position :: Update position vector (through position length)
   get_position position :: Return position vector

      This class is a generic particle with a multidimensional position vector
  that can be set and retrieved.  A basic extension of the game's 3-dimensional
  position vectors.

  Example:
   N/A - untested - unimplemented

*/

DEFCLASS("Particle") ["_self"] DO {
	/* Initialize the particle */
	SUPER_ARGS("Marker", _self)
	        [position _self, "ELLIPSE", nil, [1, 1]]
	ENDARGS;
	[_self, "_setf", "extraDimensions", []] call fnc_tell;
	[_self, "show"] call fnc_tell;
	_self
} ENDCLASS;


ALIAS("Particle", "set_marker_position", "Marker", "set_position");


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
