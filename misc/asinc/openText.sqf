if (DialogOpen) then {
  closeDialog 0;
  waitUntil {!DialogOpen};
};
_unit = _this select 0;
DialogOpen = true;
waitUntil {DialogOpen};
_unit spawn fnc_text;


_this spawn {
  _unit = _this select 0;
  DialogTarget = _unit;
  _ok = 0 cutRsc ["TalkDisplay","PLAIN"];
  for "_i" from 1 to ((count _this)-1) step 2 do {
    _unit setVariable ["dialogState", _this select _i];
    SelectionClick = true;
    sleep (_this select (_i+1));
  };
  _clear = 0 cutRsc ["Default","PLAIN"];
  DialogOpen = false;
  _unit setVariable ["dialogState", _unit getVariable "dialogStart"];
};