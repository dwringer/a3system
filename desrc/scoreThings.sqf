private ["_man", "_objs"];
_man = _this select 0;
_objs = nearestObjects [_man, [], 4.2];
count _objs;