private ["_man", "_targets", 
	 "_size", "_sum"];
_minRng = 75;
_man = _this select 0;
_targets = _this select 1;
_size = count _targets;
_sumA = {(_man knowsAbout _x) > 1} 
        count _targets;
_sumB = {(_x knowsAbout _man) > 1}
        count _targets;
_sumA = _sumA / _size;
_sumB = _sumB / _size;
_sum = _sumA / (.1 + _sumB);
if (_sumA == 0) then {_sum = 0;};
_rtn = 0;
if (((position _man) distance (position (_targets select 0))) > _minRng) then {
   _rtn = _sum;};
_rtn;