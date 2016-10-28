/*
  Dictionary class
    :: Dictionary -> ObjectRoot

  Methods:
   get key       :: look up the value stored in this object by key
   set key value :: set the provided key in object's namespace to value
   keys          :: return a list of all keys stored in this Dictionary
   items         :: return a list of all key, value pairs stored

      This class uses an instance's attribute storage as a dictionary,
  prefixing keys with an identifier so they can be distinguished from class
  internals.  The interface is simple and based on Python methods.

  Example:
   MyDict = ["Dictionary"] call fnc_new;
   [MyDict, "set", "name", "John Doe"] call fnc_tell;
   [MyDict, "set", "age", 29] call fnc_tell;
   [MyDict, "set", "age", 30] call fnc_tell;

   hint str ([MyDict, "get", "age"] call fnc_tell)
   // ... outputs 30

   hint str ([MyDict, "keys"] call fnc_tell)
   // ... outputs ["name", "age"]

   hint str ([MyDict, "items"] call fnc_tell)
   // ... outputs [["name", "John Doe"], ["age", 30]]
   
*/

DEFCLASS("Dictionary") ["_self"] DO {
	/* Initialize the dictionary */
	SUPER("ObjectRoot", _self);
	_self
} ENDCLASS;


DEFMETHOD("Dictionary", "set") ["_self", "_key", "_value"] DO {
	/* Set a key's value in dictionary's namespace */
	_key = format ["%1%2", "__dictValue_", _key];
	[_self, "_setf", _key, _value] call fnc_tell
} ENDMETHOD;


DEFMETHOD("Dictionary", "get") ["_self", "_key"] DO {
	/* Lookup method for dictionary values by key */
	_key = format ["%1%2", "__dictValue_", _key];
	[_self, "_getf", _key] call fnc_tell
} ENDMETHOD;


DEFMETHOD("Dictionary", "keys") ["_self"] DO {
	/* Return the recorded list of keys stored */
	private ["_locals", "_keys", "_k", "_substr"];
	_locals = [_self, "_locals"] call fnc_tell;
	_keys = [];
	{
		_k = toArray _x;
		if ((count _k) > 12) then {
			_substr = [_k, 0, 12] call fnc_subseq;
			if ((toString _substr) isEqualTo
			    "__dictValue_") then {
				_substr = [_k, 12, 0] call fnc_subseq;
				_keys = _keys + [toString _substr];
			};
		};
	} forEach _locals;
	_keys
} ENDMETHOD;


DEFMETHOD("Dictionary", "items") ["_self"] DO {
	/* Return a list of all stored key, value pairs */
        private ["_keys", "_acc"];
	_keys = [_self, "keys"] call fnc_tell;
	_acc = [[["_k", "_d"],  
                {[_d, "get", _k] call fnc_tell}] call fnc_lambda,
	        _keys, [_self]] call fnc_mapwith;
	[_keys, _acc] call fnc_zip
} ENDMETHOD;
