DEFCLASS("ObjectRoot") ["_self"] DO {
	/* * *
	 * Initialize base object class instance.
         * * */
	SUPER("Dictionary", _self);
	_self
} ENDCLASS;


// Retain dictionary methods under special aliases:
ALIAS("ObjectRoot", "_set", "Dictionary", "set");
ALIAS("ObjectRoot", "_get", "Dictionary", "get");
ALIAS("ObjectRoot", "_keys", "Dictionary", "keys");
ALIAS("ObjectRoot", "_items", "Dictionary", "items");


// Override Dictionary methods:
DEFMETHOD("ObjectRoot", "set") ["_self", "_key", "_value"] DO {
	/*  Set value of a local variable  */
	_key = format ["%1%2", "_local_", _key];
	[_self, "_set", _key, _value] call fnc_tell
} ENDMETHOD;


DEFMETHOD("ObjectRoot", "get") ["_self", "_key"] DO {
	/*  Get value of a local variable  */
	_key = format ["%1%2", "_local_", _key];
	[_self, "_get", _key] call fnc_tell
} ENDMETHOD;


DEFMETHOD("ObjectRoot", "keys") ["_self"] DO { nil } ENDMETHOD;


DEFMETHOD("ObjectRoot", "items") ["_self"] DO { nil } ENDMETHOD;


// ObjectRoot methods:
DEFMETHOD("ObjectRoot", "locals") ["_self"] DO {
	/* Return a list of all local variables */
	private ["_keys", "_locals", "_k", "_substr"];
	_keys = [_self, "_keys"] call fnc_tell;
	_locals = [];
	{
		_k = toArray _x;
		_substr = [_k, 0, 7] call fnc_subseq;
		if (_substr isEqualTo "_local_") then {
			_substr = [_k, 7, 0] call fnc_subseq;
		        _locals = _locals + [_substr];
		};
	} forEach _keys;
	_locals
} ENDMETHOD;
