DEFCLASS("Composition") ["_self"] DO {
	SUPER("ObjectRoot", _this);
	[_self, "_setf", "_classes", []] call fnc_tell;
	[_self, "_setf", "_instances", []] call fnc_tell;
	_self
} ENDCLASS;


DEFMETHOD("Composition", "load") ["_self", "_array_export"] DO {
	_classes = _self getVariable "_classes";
	_instances = _self getVariable "_instances";
	_arrayCount = count _array_export;
	_meanPosition = [[["_p"], {
			  [[["_a", "_b"], {_a + _b}] call fnc_lambda,
			   [[["_c", "_alen"], {_c / _alen}] call fnc_lambda,
			    _p, [_arrayCount]] call fnc_mapwith]
			   call fnc_reduce
		          }] call fnc_lambda,
			  [[["_l"], {_l select 1}] call fnc_lambda,
			   _array_export] call fnc_map] call fnc_map;
	{
		_classname = _x select 0;
		_position = [[["_a", "_b"], {_a - _b}] call fnc_lambda,
			     _meanPosition,
			     (_x select 1)] call fnc_map;
		_objectArray = [_classname, _position] +
			       ([_x, 2, 0] call fnc_subseq);
		if (not (_classname in _classes)) then {
			[_self, "_push_attr", "_classes", _classname]
			 call fnc_tell;
		};
		_package = (_classname splitString "_") select 0;
		if (isNil ([_package, _instances] call fnc_alist_get)) then {
			[_self, "_push_attr", "_instances", [_package, []]]
 			 call fnc_tell;
		};
		_packageInstances = ([_package, self getVariable "_instances"]
				      call fnc_alist_get) + [_objectArray];
		self setVariable ["_instances",
				  [_package, _packageInstances, _instances]
				   call fnc_alist_set];
	} forEach _array_export;
} ENDMETHOD;
