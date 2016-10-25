/*
  Dictionary class
      A thin layer of abstraction utilizing the game's built in object 
  namespace storage capabilities and simplifying certain use cases.

  Methods:
   get key       :: look up the value stored in this object by key
   set key value :: set the provided key in object's namespace to value
   keys          :: return a list of all keys stored in this Dictionary
   items         :: return a list of all key, value pairs stored

  Example:
   MyDict = ["Dictionary"] call fnc_new;
   [MyDict, "set", "name", "John Doe"] call fnc_tell;
   [MyDict, "set", "age", 29] call fnc_tell;
   [MyDict, "set", "age", 30] call fnc_tell;

   hint str [MyDict, "get", "age"];
   // ... outputs 30

   hint str ([MyDict, "keys"] call fnc_tell)
   // ... outputs ["name", "age"]

   hint str ([MyDict, "items"] call fnc_tell)
   // ... outputs [["name", "John Doe"], ["age", 30]]
   
*/

DEFCLASS("Dictionary") ["_o"] DO {
	/* Initialize the dictionary with an empty key array */
	_o setVariable ["__keys__", []];
	_o
} ENDCLASS;


DEFMETHOD("Dictionary", "get") ["_o", "_key"] DO {
	/* Lookup method for dictionary values by key */
        _o getVariable [_key, nil]
} ENDMETHOD;


DEFMETHOD("Dictionary", "set") ["_o", "_key", "_value"] DO {
	/* Set a key's value in dictionary's namespace */
	// TODO: _ delete keys for values set to nil
        private ["_keys"];
	_keys = _o getVariable "__keys__";
	if (({_x == _key} count _keys) == 0) then {
	        _keys = _keys + [_key];
		_o setVariable ["__keys__", _keys];
	};
	_o setVariable [_key, _value]
} ENDMETHOD;


DEFMETHOD("Dictionary", "keys") ["_o"] DO {
	/* Return the recorded list of keys stored */
        _o getVariable "__keys__"
} ENDMETHOD;


DEFMETHOD("Dictionary", "items") ["_o"] DO {
	/* Return a list of all stored key, value pairs */
        private ["_keys", "_acc"];
	_keys = [_o, "keys"] call fnc_tell;
	_acc = [[["_k", "_d"],  
                {[_d, "get", _k] call fnc_tell}] call fnc_lambda,
	        _keys, [_o]] call fnc_mapwith;
	[_keys, _acc] call fnc_zip
} ENDMETHOD;

