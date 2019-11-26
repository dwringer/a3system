_tgt = _this select 0;
_pdist = [player, _tgt] call BIS_fnc_distance2D;

if ((_pdist > 5) || ((getdammage _tgt) == 1.0)) exitWith {};

_tgt setposatl [getposatl _tgt select 0, getposatl _tgt select 1, 0.025];

disableSerialization;

_hdg = 90 - ([player, _tgt] call BIS_fnc_dirTo); 
_tvel = velocity _tgt;
_vx = _tvel select 0;
_vy = _tvel select 1;
_vz = _tvel select 2;
_tgt setvelocity [ ((10 - _pdist + 3 * (random 1)) * (cos _hdg)) / 10 + _vx, 
		   ((10 - _pdist + 3 * (random 1)) * (sin _hdg)) / 10 + _vy, 
   		   1 + (10 - _pdist) / 4 + (random 1) + _vz]; 