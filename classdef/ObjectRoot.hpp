/*
  ObjectRoot class

  Methods:
   _setf   :: setVariable in object's namespace, and record key
   _getf   :: simple getVariable interface
   _locals :: list of all recorded keys that have been stored

      This class is meant to act as the root of an object heirarchy, providing
  a standard interface for keeping instance variables in a namespace unique
  to each instance.  This is just a thin layer of abstraction over the built-in
  setVariable and getVariable functions (which are already object-oriented in
  nature and provide a simple way of bootstrapping on top of the engine).

  Example:
      Obj = ["ObjectRoot"] call fnc_new;
      [Obj, "_setf", "a key", "associated data"] call fnc_tell;
      
      hint str [Obj, "_getf", "a key"] call fnc_tell
      // ... outputs "associated data"

      hint str [Obj, "_locals"] call fnc_tell
      // ... outputs ["a key"]

  Subclass example:
      ["ANewClass", ["_self"], {
          [_self, "ObjectRoot"] call fnc_instance;
          ... rest of init ...
      } call fnc_lambda] call fnc_class;
     
   w/macros:
      DEFCLASS("HeaderDefinedClass") ["_self"] DO {
          SUPER("ObjectRoot", _self);
          ... rest of init ...
      } ENDCLASS;
*/

DEFCLASS("ObjectRoot") ["_self"] DO {
	/* Initialize base object class instance */
	_self setVariable ["__locals__", []];
	_self
} ENDCLASS;


DEFMETHOD("ObjectRoot", "_setf") ["_self", "_var_name", "_value"] DO {
	/* Set value of a local variable */
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
	/* Get value of a local variable */
	_self getVariable [_var_name, nil]
} ENDMETHOD;


DEFMETHOD("ObjectRoot", "_locals") ["_self"] DO {
	/* Return list of locally stored variable names */
	_self getVariable "__locals__"
} ENDMETHOD;