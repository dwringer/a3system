/*
  UNTESTED:UnitGroup class

  Methods:
    center_pos  :: Get the mean position of all group units
    add unit    :: Add a unit to group
    remove unit :: Remove a unit from group

      This is an abstraction to represent a group of units.  This is distinct
  from unit groups in the typical sense - these groups exist independently and
  are commanded separately through the class method interface.

  Example:
    N/A - not tested

*/

DEFCLASS("UnitGroup") ["_self"] DO {
	/* A group abstraction - distinct from Groups in the engine */
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "units", []] call fnc_tell;
	_self
} ENDCLASS;


DEFMETHOD("UnitGroup", "center_pos") ["_self"] DO {
	/* Get the mean position of all units in this UnitGroup */
	private ["_positions", "_center", "_alen", "_comp"];
	_positions = [[["_u"], {position _u}] call fnc_lambda,
		      [_self, "_getf", "units"] call fnc_tell] call fnc_map;
	_alen = count _positions;
	_center = [];
	for "_i" from 0 to 2 do {
		_comp = 0;
		for "_j" from 0 to (_alen - 1) do {
			_comp = _comp + ((_positions select _j) select _i);
		};
		_center = _center + [_comp / _alen];
	};
	_center
} ENDMETHOD;


DEFMETHOD("UnitGroup", "add") ["_self", "_unit"] DO {
	/* Add a unit to this UnitGroup */
	[_self, "_push_attr", "units", _unit] call fnc_tell;
	[_self, "_getf", "units"] call fnc_tell
} ENDMETHOD;


DEFMETHOD("UnitGroup", "remove") ["_self", "_unit"] DO {
	/* Remove a unit from this UnitGroup */
	private ["_units"];
	_units = [_self, "_getf", "units"] call fnc_tell;
	_units = _units - [_unit];
	[_self, "_setf", "units", _units] call fnc_tell;
	_units
} ENDMETHOD;