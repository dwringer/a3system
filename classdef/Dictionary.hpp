#define DEFCLASS(NAME)  [NAME, [
#define DEFMETHOD(CLS, NAME) [CLS, NAME, [
#define DO ,
#define ENDCLASS ] call fnc_lambda] call fnc_class
#define ENDMETHOD ] call fnc_lambda] call fnc_method


DEFCLASS("Dictionary") ["_o"] DO {
	_o setVariable ["__keys__", []];
	_o
} ENDCLASS;


DEFMETHOD("Dictionary", "get") ["_o", "_key"] DO {
        _o getVariable [_key, nil]
} ENDMETHOD;


DEFMETHOD("Dictionary", "set") ["_o", "_key", "_value"] DO {
        private ["_keys"];
	_keys = _o getVariable "__keys__";
	if (({_x == _key} count _keys) == 0) then {
	        _keys = _keys + [_key];
		_o setVariable ["__keys__", _keys];
	};
	_o setVariable [_key, _value]
} ENDMETHOD;


DEFMETHOD("Dictionary", "keys") ["_o"] DO {
        _o getVariable "__keys__"
} ENDMETHOD;


DEFMETHOD("Dictionary", "items") ["_o"] DO {
        private ["_keys", "_acc"];
	_keys = [_o, "keys"] call fnc_tell;
	_acc = [[["_k"], 
		{[_o, "get", _k] call fnc_tell}] call fnc_lambda,
		_keys] call fnc_map;
	[_keys, _acc] call fnc_zip
} ENDMETHOD;

