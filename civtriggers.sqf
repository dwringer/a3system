///////////////////////////// civtriggers.sqf ////////////////////// 2016-10-18
/*  Create spawn/despawn triggers for ambient civilians   */
////////////////////////////////////////////////////////////
private [                 //
         _logic,          // [IN/0]
         _lo,             // [IN/1]
         _hi,             // [IN/2]
         _size,           // [IN/3]                                    //
         _rPlacement,     // [IN/4]                                   //// 
         _rSpawn,         // [IN/5]                                  ////// 
         _rDespawn,       // [IN/6]                                 ///  ///  
         _spawnTrigger,   //                                       ///    ///
         _despawnTrigger  //                                      ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_logic = _this select 0;
_lo = _this select 1;
_hi = _this select 2;
_size = _this select 3;
_rPlacement = _this select 4;
_rSpawn = _this select 5;
_rDespawn = _this select 6;

call compile format ["Bool_civSpawn_%1_%2 = false;", _lo, _hi];

_spawnTrigger = createTrigger ["EmptyDetector", position _logic];
_spawnTrigger setTriggerArea [_rSpawn, _rSpawn, 0, false];
_spawnTrigger setTriggerActivation ["ANY", "PRESENT", true];
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