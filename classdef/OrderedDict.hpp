/*
  OrderedDict class
      A gratuitously inefficient and basically pointless class designed to
  show off inheritance and aliasing capabilities of the class system.  You
  are probably better off taking a normal Dictionary and sorting it yourself,
  even with the horribly inefficient sort algorithm I have included.  This 
  does, however, technically conform to its interface.  Mostly.

  Methods:
   get key       :: inherited from Dictionary
   set key value :: inherited from Dictionary
   keys          :: sorted version of keys inherited from Dictionary
   items         :: like Dictionary items, but the keys are sorted first

  Example:
   MyODict = ["OrderedDictionary", 
              [["_a", "_b"], 
               {((toArray _a) select 0) < ((toArray _b) select 0)}
              ] call fnc_lambda] call fnc_new;
   [MyODict, "set", "test", "a test value"] call fnc_tell;
   [MyODict, "set", "a test", "another value"] call fnc_tell;

   hint str ([MyODict, "_keys"] call fnc_tell)
   // ... outputs ["fn_comparator", "test", "a test"]
   //     [This is the aliased dictionary keys method, and is unsorted.
   //      fn_comparator is used internally and is visible as an artifact
   //      of how this class abuses everything about class heirarchy
   //      design principles.  Did I mention not to use this class?]

   hint str([MyODict, "keys"] call fn_tell)
   // ... outputs ["a test", "fn_comparator", "test"]
   //     [At least they are sorted. Sort of.]

*/


DEFCLASS("OrderedDict") ["_self", "_cmp"] DO {
	/* Initialize base object class instance. */
	SUPER("BaseObject", _self);
	[_self, "set", "fn_comparator", _cmp] call fnc_tell;
	_self
} ENDCLASS;


// Make the base class method available under a different name:
ALIAS("OrderedDict", "_keys", "Dictionary", "keys");


DEFMETHOD("OrderedDict", "keys") ["_o"] DO {
	/* Sort the value returned by aliased Dictionary keys method */
	_keys = [_o, "_keys"] call fnc_tell;
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
