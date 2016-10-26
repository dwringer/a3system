DEFCLASS("ObjectRoot") ["_self"] DO {
	/* Initialize base object class instance */
	_self setVariable ["__locals__", []];
	_self
} ENDCLASS;


DEFMETHOD("ObjectRoot", "_setf") ["_self", "_var_name", "_value"] DO {
	/*  Set value of a local variable  */
	private ["_locals"];
	_locals = _self getVariable "__locals__";
	if (not isNil "_value") then {
	        if (({_x == _var_name} count _locals) == 0) then {
  	                _locals = _locals + [_var_name];
		};
	} else {
                if (({_x == _var_name} count _locals) > 0) then {
		        _locals = _locals - [_var_name];
		};
        };
	_self setVariable ["__locals__", _locals];
	_self setVariable [_var_name, _value]
} ENDMETHOD;


DEFMETHOD("ObjectRoot", "_getf") ["_self", "_var_name"] DO {
	/*  Get value of a local variable  */
	_self getVariable [_var_name, nil]
} ENDMETHOD;


DEFMETHOD("ObjectRoot", "_locals") ["_self"] DO {
	/*  Return list of locally stored variable names */
	_self getVariable "__locals__"
} ENDMETHOD;