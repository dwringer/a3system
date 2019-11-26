////////////////////////////// fnc_reduce ////////////////////////// 2016-10-21
/*  Reduce an array by recursively applying a given function   */
/////////////////////////////////////////////////////////////////
private [                //                                           
         "_fn",          // Function [IN/A0/B0]                        //
         "_arr",         // Array    [IN/A1/B1]                       //// 
         "_extra_vars",  // Array    [IN/A2]                         ////// 
         "_acc"          // Array    [OUT]                          ///  ///  
                         //                                        ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_fn = _this select 0;
_arr = _this select 1;
_acc = _arr select 0;
if ((count _this) == 3) then {
	_extra_vars = _this select 2;
} else {
	_extra_vars = [];
};
for "_i" from 1 to ((count _arr) - 1) do {
	_acc = ([_acc, _arr select _i] + _extra_vars) call _fn;
};
_acc;  // RETURN //////////////////////////////////////////////////////////////

/*
 A rather convoluted example:
    [([["_a", "_b"], {_a + _b}] call fnc_lambda),
     [[["_x"], {_x * _x}] call fnc_lambda,
      [[["_x", "_y"], {(_x + _y) % 2 == 1)} call fnc_lambda,
       [10] call fnc_range,
       [2]] call fnc_filter] call fnc_map] call fnc_reduce
*/