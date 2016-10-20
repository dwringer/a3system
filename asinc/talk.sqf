_this spawn {

private ["_dUnit", "_dialogText", "_dialogR1", "_dialogR2", "_dialogR3", "_camera"];


_dUnit = player;
if (typeName _this == "ARRAY") then {
	_dUnit = _this select 1; 
	_this = _this select 0;
};

if (_dUnit == player) then {
  ((findDisplay 1987) displayCtrl 1000) ctrlSetText (_this getVariable ["dialogName", "Unknown Person"]);
} else {
  ((findDisplay 1987) displayCtrl 1000) ctrlSetText (_dUnit getVariable ["dialogName", "Unknown Person"]);
};

if (!(alive _this) or !(DialogOpen)) exitWith {false};

DialogTarget = _this;

_camera = "camera" camCreate [0,0,0];
_camera attachTo [vehicle player, [0,0,1.7]];
_camera camPrepareTarget _this;
_camera camPrepareFOV 0.2;
_camera camCommitPrepared 0;
_camera cameraEffect ["INTERNAL", "BACK", "camrender0"];

_camera cameraEffect ["internal","back"];

SelectionClick = true;
while {(alive player) and (alive _this) and (DialogOpen)} do {
  _ppos = position player;
  _tpos = position _this; 
  _dist = [_ppos, _tpos] call BIS_fnc_distance2d;
  _dist = _dist * -0.01 - 1;
  _tht = 90 - ([player, _tpos] call BIS_fnc_dirTo) + (direction _this);
  if ((vehicle _this) == _this) then {
    _camera attachTo [vehicle _this,
  	              [_dist*cos(_tht),_dist*sin(_tht),1.7]];
    _camera camPrepareFOV 0.2;
  } else {
    if ((vehicle player) == (vehicle _this)) then { 
      _tht = _tht - 32.8;
    };
    _camera attachTo [vehicle _this,
  	              [_dist*cos(_tht),(_dist-3)*sin(_tht),0.33]];
    _camera camPrepareFOV 0.42;
  };
  _camera camPrepareTarget _this;
  _camera camCommitPrepared 0.05;
  _camera cameraEffect ["INTERNAL", "BACK", "camrender0"];

  if (SelectionClick) then {
    SelectionClick = false;
    _dialogText = "";
    _dialogR1 = "";
    _dialogR2 = "";
    _dialogR3 = "";
    if (_dUnit == player) then {
      _dialogText = [_this, 0] call fnc_getText;
      _dialogR1 = [_this, 1] call fnc_getText;
      _dialogR2 = [_this, 2] call fnc_getText;
      _dialogR3 = [_this, 3] call fnc_getText;
    } else {
      _dialogText = [_dUnit, 0] call fnc_getText;
      _dialogR1 = [_dUnit, 1] call fnc_getText;
      _dialogR2 = [_dUnit, 2] call fnc_getText;
      _dialogR3 = [_dUnit, 3] call fnc_getText;
  
    };
    _dialogText = format ["%1\n\n%2\n%3\n%4", _dialogText, _dialogR1, _dialogR2, _dialogR3];
  };

  ((findDisplay 1987) displayCtrl 1001) ctrlSetText _dialogText;
  if (_dUnit == player) then {
    ((findDisplay 1987) displayCtrl 1000) ctrlSetText (_this getVariable ["dialogName", "Unknown Person"]);
  } else {
    ((findDisplay 1987) displayCtrl 1000) ctrlSetText (_dUnit getVariable ["dialogName", "Unknown Person"]);
  };



};

camDestroy _camera;

};