////////////////////////////// dg_step.sqf ///////////////////////// 2016-10-19
/*  Randomly move from one dg node to a reachable node  */
//////////////////////////////////////////////////////////
private [             //                                         
         "_origin",   // vehicle   [IN/0]                              //
         "_last",     // vehicle   [IN/1] (previous node)             //// 
         "_choices",  // vehicle[] [OUT*] (random element)           ////// 
         "_ignore"    //                                            ///  ///  
                      //                                           ///    ///
                      //                                          ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_origin = _this select 0;
_last = _this select 1;
_choices = _origin call fnc_dg_synced;
_choices = _choices - [_last];
if ((count _choices) > 1) then {
	_ignore = [_origin, _choices, 2] call fnc_dg_closest;
	_choices = _choices - _ignore;
};
_choices select floor random count _choices;  // RETURN ///////////////////////