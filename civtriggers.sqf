///////////////////////////// civtriggers.sqf ////////////////////// 2016-10-18
/*  Create spawn/despawn triggers for ambient civilians   */
////////////////////////////////////////////////////////////
private [                 //
         _logic,          // vehicle [IN/0]
         _lo,             // int     
         _hi,             // int     
         _ct,             // int     [IN/1]
         _size,           // int     [IN/2]                            //
         _rPlacement,     // float   [IN/3]                           //// 
         _rSpawn,         // float   [IN/4]                          ////// 
         _rDespawn,       // float   [IN/5]                         ///  ///  
         _spawnTrigger,   // trigger                               ///    ///
         _despawnTrigger  // trigger                              ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_logic = _this select 0;
_ct = _this select 1;
_size = _this select 2;
_rPlacement = _this select 3;
_rSpawn = _this select 4;
_rDespawn = _this select 5;

waitUntil {not Sentinel_civTriggers};
Sentinel_civTriggers = true;
_lo = Index_civGroups;
_hi = _lo + _ct;
Index_civGroups = _hi + 1;
Sentinel_civTriggers = false;

call compile format ["Bool_civSpawn_%1_%2 = false;", _lo, _hi];

_spawnTrigger = createTrigger ["EmptyDetector", position _logic];
_spawnTrigger setTriggerArea [_rSpawn, _rSpawn, 0, false];
_spawnTrigger setTriggerActivation ["GROUP", "PRESENT", true];
_spawnTrigger triggerAttachVehicle[player];
_spawnTrigger setTriggerStatements [
        format ["(player in thisList) and !Bool_civSpawn_%1_%2", _lo, _hi],
        format ["_nil = [%1, %2, %3, %4, %5]",
                _lo, _hi, _size, _logic, _rPlacement] +
               " call fnc_mkcivs; " +
        format ["Bool_civSpawn_%1_%2 = true;", _lo, _hi],
        ""
];
_despawnTrigger = createTrigger ["EmptyDetector", position _logic];
_despawnTrigger setTriggerArea [_rDespawn, _rDespawn, 0, false];
_despawnTrigger setTriggerActivation ["GROUP", "NOT PRESENT", true];
_despawnTrigger triggerAttachVehicle[player];
_despawnTrigger setTriggerStatements [
        format ["this and Bool_civSpawn_%1_%2", _lo, _hi],
        format ["_nil = [%1, %2, %3] execVM ""rmcivs.sqf""; ",
                _lo, _hi, _size] +
        format ["Bool_civSpawn_%1_%2 = false;", _lo, _hi],
        ""
];  ///////////////////////////////////////////////////////////////////////////