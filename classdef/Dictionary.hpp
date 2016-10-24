["Dictionary",
 [["_o"],
  "_o setVariable [""__keys__"", []];
  _o"
  ] call fnc_lambda] call fnc_class;

["Dictionary", "get",
 [["_o", "_key"],
  "_o getVariable [_key, nil]"
  ] call fnc_lambda] call fnc_method;

["Dictionary", "set",
 [["_o", "_key", "_value"],
  "private [""_keys""];
   _keys = _o getVariable ""__keys__"";
   if (({_x == _key} count _keys) == 0) then {
       _keys = _keys + [_key];
       _o setVariable [""__keys__"", _keys];
   };
   _o setVariable [_key, _value]"
  ] call fnc_lambda] call fnc_method;

["Dictionary", "keys",
 [["_o"],
  "_o getVariable ""__keys__"""
  ] call fnc_lambda] call fnc_method;
