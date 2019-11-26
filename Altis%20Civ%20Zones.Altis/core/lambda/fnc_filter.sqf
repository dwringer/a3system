/////////////////////////////// fnc_filter ///////////////////////// 2016-10-21
/*  Filter an array by application of a predicate  */
/////////////////////////////////////////////////////
private [                //                                    
         "_fn",          // Function [IN/A0/B0]                        //
         "_arr",         // Array    [IN/A1/B1]                       //// 
         "_extra_vars",  // Array    [IN/A2]                         ////// 
         "_acc",         // Array    [OUT]                          ///  ///  
         "_elt"          // Element                                ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_fn = _this select 0;
_arr = _this select 1;
if ((count _this) == 3) then {
	_extra_vars = _this select 2;
} else {
	_extra_vars = [];
};
_acc = [];
for "_i" from 0 to ((count _arr) - 1) do {
	_elt = _arr select _i;
	if (not isNil "_elt") then {
		if (([_elt] + _extra_vars) call _fn) then {
			_acc pushBack _elt;
		};
        } else {
		if (([nil] + _extra_vars) call _fn) then {
			_acc pushBack _elt;
		};
	};
};
_acc;  // RETURN //////////////////////////////////////////////////////////////