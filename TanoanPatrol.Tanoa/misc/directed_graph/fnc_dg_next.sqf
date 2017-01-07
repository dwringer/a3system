////////////////////////////// dg_next.sqf ///////////////////////// 2016-10-19
/*  Take two steps down the DG (one directed edge)  */
//////////////////////////////////////////////////////
private [             //                                         
         "_origin",   // vehicle   [IN]                                //
         "_next   "   // vehicle   [OUT]                              //// 
                      //                                             ////// 
                      //                                            ///  ///  
                      //                                           ///    ///
                      //                                          ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_origin = _this;
_next = [_origin, _origin] call fnc_dg_step;
_next = [_next, _origin] call fnc_dg_step;
_next;  // RETURN /////////////////////////////////////////////////////////////