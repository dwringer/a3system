////////////////////////////// fnc_reduce ////////////////////////// 2016-10-21
/*  Reduce an array by recursively applying a given function   */
/////////////////////////////////////////////////////////////////
private [         //                                           
         "_fn",   // Function [IN/0]                                   //
         "_arr",  // Array    [IN/1]                                  //// 
         "_acc"   // Array    [OUT]                                  ////// 
                  //                                                ///  ///  
                  //                                               ///    ///
                  //                                              ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_fn = _this select 0;
_arr = _this select 1;
_acc = _arr select 0;
for "_i" from 1 to ((count _arr) - 1) do {
	_acc = [_acc, _arr select _i] call _fn;
};
_acc;  // RETURN //////////////////////////////////////////////////////////////