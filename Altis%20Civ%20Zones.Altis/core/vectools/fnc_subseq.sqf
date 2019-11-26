////////////////////////////// fnc_subseq ////////////////////////// 2016-10-21
/*  Pythonic subsequence of an array from [lo .. hi)  */
////////////////////////////////////////////////////////
private [                 //                                   
         "_arr",          // Array [IN/A0/B0]                          //
         "_lower_bound",  // int   [IN/A1]                            //// 
         "_upper_bound",  //       [IN/A2/B1]                        ////// 
         "_acc"           //                                        ///  ///  
                          //                                       ///    ///
                          //                                      ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_arr = _this select 0;
switch (count _this) do {
	case 2: {
		_lower_bound = 0;
		_upper_bound = _this select 1;
	};
	case 3: {
		_lower_bound = _this select 1;
		_upper_bound = _this select 2;
	};
};
if (_lower_bound < 0) then {
	_lower_bound = (count _arr) + _lower_bound;
};
if (_upper_bound <= 0) then {
	_upper_bound = (count _arr) + _upper_bound;
};
_acc = [];
for "_i" from _lower_bound to (_upper_bound - 1) do {
	_acc set [count _acc, _arr select _i];
};
_acc;  // RETURN //////////////////////////////////////////////////////////////