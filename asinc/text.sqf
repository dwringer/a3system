_this spawn {
private ["_dialogText", "_camera"];

((uiNamespace getVariable "TalkDisplay") displayCtrl 1000) ctrlSetText (_this getVariable ["dialogName", "Unknown Person"]);

if (!(alive _this) or !(DialogOpen)) exitWith {false};

DialogTarget = _this;

_camera = "camera" camCreate [0,0,0];
_camera attachTo [vehicle player, [0,0,1.7]];
_camera camPrepareTarget _this;
_camera camPrepareFOV 0.2;
_camera camCommitPrepared 0.05;
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
    _dialogText = [_this, 0] call fnc_getText;
  };
  ((uiNamespace getVariable "TalkDisplay") displayCtrl 1001) ctrlSetText _dialogText;
  ((uiNamespace getVariable "TalkDisplay") displayCtrl 1000) ctrlSetText (_this getVariable ["dialogName", "Unknown Person"]);

};
camDestroy _camera;
};

//};