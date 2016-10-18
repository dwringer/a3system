
/// GA SECTION:>
fnc_scoreThings = compile preprocessfile "desrc\scoreThings.sqf";
fnc_scoreKnows = compile preprocessfile "desrc\scoreKnows.sqf";
fnc_scoreLOS = compile preprocessfile "desrc\scoreLOS.sqf";
fnc_doScores = compile preprocessfile "desrc\doScores.sqf";
fnc_objectives = compile preprocessfile "desrc\objectives.sqf";
fnc_aggregator = compile preprocessfile "desrc\aggregator.sqf";

////////////////////////
// CONFIG             /
//////////////////////
// Number of targets:
_tgtCount = 0;
// Minimum 'possible' score:
psoGlobalMin = 0;
// Maximum 'possible' score:
psoGlobalMax = 10;
/////////////////////

gaTargets = [];
gaPopulation = [];
for "_i" from 1 to _tgtCount do {
	call compile format [
	     "gaTargets = gaTargets + [tgt_%1];", _i];};

_tmp = createGroup west;
if (isNull _tmp) then {
	createCenter west;
	_tmp = createGroup west;};
deleteGroup _tmp;

////END/GA/SECTION/>
