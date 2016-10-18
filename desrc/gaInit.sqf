private ["_g", "_pop", "_popSize", "_ustring", "_tgt", "_rng"];
{_g = group _x; deleteVehicle _x; deleteGroup _g} forEach gaPopulation;
gaPopulation = [];
_pop = [];

////////////////////////
// CONFIG             /
//////////////////////
// Population size:
_popSize = 42;
// PSO Unit type:
_ustring = "B_Soldier_F";
// Primary target:
_tgt = tgt;
// Exclusion target:
_xtgt = tgt;
// Maximum range:
_rng = 210;
// Minimum range:
_minRng = 1;
// Side of PSO units:
_gaSide = west;
///////////////////////

for "_i" from 0 to (_popSize - 1) do {
    _tmp = (createGroup _gaSide) createUnit [_ustring, position _tgt, [], _rng, "NONE"];
    while {((position _tmp) distance (position _xtgt)) < _minRng} do {
      _gtmp = group _tmp;
      deleteVehicle _tmp;
      _tmp = _gtmp createUnit [_ustring, position _tgt, [], _rng, "NONE"];};
    _tmp setSkill 1.0;
    _tmp setVariable ["gaTries", 0];
    _hdg = [_tmp, position (gaTargets select (floor random (count gaTargets)))] call BIS_fnc_relativeDirTo;
    _tmp setDir _hdg;
    group _tmp setFormDir _hdg;
    _pop = _pop + [_tmp];};

		  
gaPopulation = _pop;
