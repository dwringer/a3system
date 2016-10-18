private ["_acc", "_rtn"];

_acc = 0;
{
  _acc = _acc + (_x * _x);	
} forEach _this;

_acc = sqrt _acc;

_rtn = (_acc - psoGlobalMin)/
        (psoGlobalMax - psoGlobalMin);
if (_rtn < 0) then {_rtn = 0};

_rtn;

