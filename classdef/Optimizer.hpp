DEFCLASS("Optimizer") ["_self", "_n"] DO {
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "population", []] call fnc_tell;
	private ["_p", "_position"];
	for "_i" from 1 to _n do {
		_p = ["Particle"] call fnc_new;
		if (isNil "_position") then {
			_position = position _p;
		};
		[_self, "_push_attr", "population", _p] call fnc_tell;
	 };
	[_self, "_setf", "position", _position] call fnc_tell;
	_self
} ENDCLASS;


DEFMETHOD("Optimizer", "position_deltas") ["_self"] DO {
	private ["_position", "_population", "_deltas", "_p", "_delta"];
	_position = [_self, "_getf", "position"] call fnc_tell;
	_population = [_self, "_getf", "population"] call fnc_tell;
	_deltas = [];
	for "_i" from 0 to ((count _population) - 1) do {
		_p = _population select _i;
		_delta = [[["_a", "_b"], {_a - _b}] call fnc_lambda,
			  position _p,
			  _position] call fnc_map;
		_deltas = _deltas + _delta;
	};
	_deltas
} ENDMETHOD;
