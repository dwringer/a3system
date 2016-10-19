////////////////////////////// dg_next.sqf ///////////////////////// 2016-10-19
/*  Randomly move from one dg node to a reachable node  */
//////////////////////////////////////////////////////////
private [                                                      
         _origin,                                                      //
         _choices,                                                    //// 
         _ignore                                                     ////// 
                                                                    ///  ///  
                                                                   ///    ///
                                                                  ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
#define EPSILON_RADIUS 2.0
_origin = _this select 0;

_choices = _origin execVM "dg_synced.sqf";
_choices = _choices - [_origin];
_ignore = [_origin, _choices, EPSILON_RADIUS] execVM "dg_closest.sqf";
_choices = _choices - _ignore;

_choices select floor random count _choices;  // RETURN ///////////////////////