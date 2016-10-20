private["_logic"];
_this = _this select 3;
if (typeName _this == "ARRAY") then {
  _logic = _this select 1;
  _this  = _this select 0;
} else {
  _logic = _this;
};


if (DialogOpen) exitWith {false};
DialogOpen = true;
[_this,_logic] spawn fnc_talk; 
[_this,_logic] spawn {
  private ["_logic"];
  _logic = _this select 1;
  _this = _this select 0;
  DialogTarget = _this;
  _ok = createDialog "TalkDialog";
  waitUntil { !dialog }; 
  _logic setVariable ["dialogState", _logic getVariable "dialogStart"];
  DialogOpen = false;
};
