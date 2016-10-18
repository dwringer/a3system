/* Arma 3 Differential Evolution Engine
      Drives genetic algorithm program making
       naieive extrapolations between generations.

  Updated:   11 March 2013

  Author:    dwringer

  All claimable rights reserved by the author.
*/

for "_i" from 0 to ((count gaPopulation) - 1) do {
    _i spawn {

    _a = _this;
    _b = gaPopulation call BIS_fnc_randomIndex;
    _c = _b;
    _d = _c;
    _marker = format ["gaMkr_%1", _this];
    if ((getMarkerColor _marker) != "") then {
	_marker setMarkerPos (position (gaPopulation select _this));};
    
    ////////////////////////
    // CONFIG             /
    //////////////////////
    // PSO Unit Type:
    _ustring = "B_Soldier_F";
    // Max Range:
    _rng = 520;
    // Min Range:
    _minRng = 200;
    // Primary target:
    _tgt = tgt;
    // Exclusion target:
    _xtgt = tgt;
    // Differential scalar factor:
    _f = 0.7;   
    // Position crossover factor:
    _cf = 0.5;  
    // Heading crossover factor:
    _hcf = 0.5; 
    // How long to wait for AI:
    _sleepDur = 5;
    // Extrapolations allowed at 0:
    _maxTries = 8;
    // Minimum acceptable score:
    _mins = 0.25; // [0.0 - 1.0]
    //////////////////////////

    //this sucks
    while {_b == _a} do {
      _b = gaPopulation call BIS_fnc_randomIndex;};
    while {(_c == _a) || (_c == _b)} do {
      _c = gaPopulation call BIS_fnc_randomIndex;};
    while {(_d == _c) || (_d == _b) || (_d == _a)} do {
      _d = gaPopulation call BIS_fnc_randomIndex;};
    //...but now all four are unique
    //todo: implement shuffled vector

    //type checking is for sissies:
    _a = gaPopulation select _a;
    _b = gaPopulation select _b;
    _c = gaPopulation select _c;
    _d = gaPopulation select _d;
    
    _pa = position _a;
    _pb = position _b;
    _pc = position _c;
    _pd = position _d;

    // get (cx-dx)
    _vd = [_pc, _pd] call BIS_fnc_vectorDiff;
    _hdgd = (getDir _c) - (getDir _d);

    // decisions:
    _np = _pa;
    _nhdg = getDir _a;
    
    // make new vars of pattern bx + f*(cx - dx)
    //  changing a-vars only with _cf probability
    _hdgd = _hdgd * _f;
    for "_i" from 0 to 2 do {
	if ((random 1) < _cf) then {
	    _np set [_i, 
    		     (_pb select _i) 
		     + (_f * (_vd select _i))];};};
    if ((random 1) < _cf) then {
	if ((random 1) < _hcf) then {
	    _nhdg = ((getDir _b) + _hdgd) mod 360;}
	else {
	  _nhdg = random 360;};};

    ///CHECK DOMINATION:
    // Create somebody at the new position.
    _tmp = (createGroup side _a) createUnit [_ustring, _np, [], 0, "NONE"];
    while {((position _tmp) distance (position _xtgt)) < _minRng} do {
      _gtmp = group _tmp;
      deleteVehicle _tmp;
      _tmp = _gtmp createUnit [_ustring, position _tgt, [], _rng, "NONE"];};



    if ((getMarkerColor _marker) != "") then {
	deleteMarker _marker;};
    _marker = createMarker [_marker, (position _a)];
    _marker setMarkerShape "ICON";
    _marker setMarkerType "b_inf";
    _marker setMarkerColor "ColorOrange";


    _tmp setSkill 1.0;
    _hdg = [_tmp, position (gaTargets select (floor random (count gaTargets)))] call BIS_fnc_relativeDirTo;
    _tmp setDir _hdg;
    group _tmp setFormDir _hdg;
    _gatries = 0;

    // Let the AI "wake up":
    sleep _sleepDur;

    // make sure we have something to compare to:
    _asc = _a getVariable "gaScore";
    if ((_asc == 0) || (_asc < 0)) then {
	_a setVariable ["gaScore", 
			([_a, gaTargets] call fnc_objectives) call fnc_aggregator];};

    // Score the new person.
    _stmp = ([_tmp, gaTargets] call fnc_objectives) call fnc_aggregator;
    
    [_this, _a getVariable "gaScore", _stmp] spawn {
      sleep (0.2 * (_this select 0));
      hint format ["sa: %1\nstmp:%2", _this select 1, _this select 2];};

    ///Compare new person score to _a's score.
    // better? replace _a in population with 
    //  the new person
    if ((_a getVariable "gaScore") <= _stmp) then {

        gaPopulation = gaPopulation - [_a];
	_gtmp = group _a;

	_marker setMarkerPos (position _tmp);
	
	if (_stmp < _mins) then {
	    _gatries = _a getVariable "gaTries";

	    _marker setMarkerColor "ColorRed";

	    if (_gatries >= _maxTries) then {

		_marker setMarkerColor "ColorBlack";

		_gtmp2 = group _tmp;
		deleteVehicle _tmp;
		_tmp = _gtmp2 createUnit [_ustring, position _tgt, [], _rng, "NONE"];
		while {((position _tmp) distance (position _xtgt)) < _minRng} do {
		  deleteVehicle _tmp;
		  _tmp = _gtmp2 createUnit [_ustring, position _tgt, [], _rng, "NONE"];};

		_marker setMarkerPos (position _tmp);
		
		_tmp setSkill 1.0;
		_gatries = 0;
		_hdg = [_tmp, position (gaTargets select (floor random (count gaTargets)))] call BIS_fnc_relativeDirTo;
		_tmp setDir _hdg;
		_gtmp2 setFormDir _hdg;
		_stmp = 0;}

	    else {
	      _gatries = _gatries + 1;};}

	else {
	  _marker setMarkerColor "ColorWhite";};
	
	deleteVehicle _a;
	deleteGroup _gtmp;
	_tmp setVariable ["gaScore", _stmp];
	_tmp setVariable ["gaTries", _gatries];
	_marker setMarkerPos (position _tmp);
	gaPopulation = gaPopulation + [_tmp];}

    else {
    // worse? drop it and move on.
      _marker setMarkerColor "ColorGreen";
      _gtmp = group _tmp;
      deleteVehicle _tmp;
      deleteGroup _gtmp;};
    };
};



/*

  TODO:

+ Compartmentalize functions where possible
  \- Generalize agent usage
    \- Decisions
    \+ Spawning
  \_ Assign markers in a manageable way
+  Check "ok" using gamelogic instead of agent
_  Improve computational efficiency of peer select


*/
 
