///////////////////////////// civtriggers.sqf ////////////////////// 2019-09-28
/*  Create spawn/despawn triggers for ambient civilians   */
////////////////////////////////////////////////////////////
private [                   //
         "_logic",          // vehicle [IN/0]
         "_lo",             // int     
         "_hi",             // int     
         "_ct",             // int     [IN/1]
         "_size",           // int     [IN/2]                          //
         "_rPlacement",     // float   [IN/3]                         //// 
         "_rSpawn",         // float   [IN/4]                        ////// 
         "_rDespawn",       // float   [IN/5]                       ///  ///  
         "_alsoFollow",     // [units] [IN/B6]
         "_spawnTrigger",   // trigger                             ///    ///
         "_despawnTrigger", // trigger                            ///      ///
         "_othersCheckOr"   // string
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_logic = _this select 0;
_ct = _this select 1;
_size = _this select 2;
_rPlacement = _this select 3;
_rSpawn = _this select 4;
_rDespawn = _this select 5;
if (6 < count _this) then {
	_alsoFollow = _this select 6;
} else {
	_alsoFollow = [];
};
_othersCheckOr = "";
{_othersCheckOr = format ["%1 or ((vehicle %2) in thisList)", _othersCheckOr, _x];} forEach _alsoFollow;
waitUntil {not isNil "Mutex_civTriggers"};
waitUntil {not Mutex_civTriggers};
Mutex_civTriggers = true;
_lo = Index_civGroups;
_hi = _lo + _ct;
Index_civGroups = _hi + 1;
Mutex_civTriggers = false;

call compile format ["Bool_civSpawn_%1_%2 = false;", _lo, _hi];

_spawnTrigger = createTrigger ["EmptyDetector", position _logic];
_spawnTrigger setTriggerArea [_rSpawn, _rSpawn, 0, false];
_spawnTrigger setTriggerActivation ["ANY", "PRESENT", true];
_spawnTrigger setTriggerStatements [
        format ["(((vehicle player) in thisList)" + _othersCheckOr + ") and !Bool_civSpawn_%1_%2", _lo, _hi],
        format ["_nil = [%1, %2, %3, %4, %5]",
                _lo, _hi, _size, _logic, _rPlacement] +
               " spawn fnc_mkcivs; " +
        format ["Bool_civSpawn_%1_%2 = true;", _lo, _hi],
        ""
];
_despawnTrigger = createTrigger ["EmptyDetector", position _logic];
_despawnTrigger setTriggerArea [_rDespawn, _rDespawn, 0, false];
_despawnTrigger setTriggerActivation ["ANY", "PRESENT", true];
_despawnTrigger setTriggerStatements [
        format ["(not (((vehicle player) in thisList)" + _othersCheckOr + ")) and Bool_civSpawn_%1_%2", _lo, _hi],
        format ["_nil = [%1, %2, %3] execVM ""mkcivs\rmcivs.sqf""; ",
                _lo, _hi, _size] +
        format ["Bool_civSpawn_%1_%2 = false;", _lo, _hi],
        ""
];  ///////////////////////////////////////////////////////////////////////////