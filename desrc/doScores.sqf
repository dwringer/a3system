private ["_a", "_s"];

{ _a = [_x, gaTargets] call fnc_objectives;
  _s = _a call fnc_aggregator;
  _x setVariable ["gaScore", _s];} forEach gaPopulation;
