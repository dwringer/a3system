DEFCLASS("OrderedDict") ["_self", "_cmp"] DO {
	/* Initialize base object class instance. */
	SUPER("BaseObject", _self);
	[_self, "set", "fn_comparator", _cmp] call fnc_tell;
	_self
} ENDCLASS;


ALIAS("OrderedDict", "_keys", "Dictionary", "keys");


DEFMETHOD("OrderedDict", "keys") ["_o"] DO {
	/* Sort the value returned by aliased Dictionary keys method */
	_keys = _o getVariable "__keys__";
	_keys = [_keys,
                 [_o, "get", "fn_comparator"] call fnc_tell] call fnc_sorted;
	_o setVariable ["__keys__", _keys];
	_keys
} ENDMETHOD;


DEFMETHOD("OrderedDict", "items") ["_o"] DO {
	/* Implicitly override the items method with sorted keys */
	private ["_keys", "_acc"];
        _keys = [_o, "keys"] call fnc_tell;
	_acc = [[["_k", "_d"],
                {[_d, "get", _k] call fnc_tell}] call fnc_lambda,
	        _keys, [_o]] call fnc_mapwith;
	[_keys, _acc] call fnc_zip
} ENDMETHOD;
