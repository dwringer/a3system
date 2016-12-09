////////////////////////////// fnc_sorted ////////////////////////// 2016-10-21
/*  Sort an array using the provided comparator function  */
////////////////////////////////////////////////////////////
private [                //
         "_arr",         // Array [IN/A1/B1]
         "_comp",        // Code  [IN/A2/B2]
         "_alen",        // int
         "_extra_vars",  // Array [IN/A3]                              //
         "_acc",         // Array [OUT]                               //// 
         "_best",        // int                                      ////// 
         "_acopy",       // Element                                 ///  ///  
         "_a",           // Element                                ///    ///
         "_b"            // Element                               ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_arr = _this select 0;
_acopy = [];
for "_i" from 0 to ((count _arr) - 1) do {
	_acopy pushBack (_arr select _i);
};
_comp = _this select 1;
_alen = count _arr;
if ((count _this) == 3) then {
	_extra_vars = _this select 2;
} else {
	_extra_vars = [];
};
_acc = [];
for "_i" from 0 to (_alen - 1) do {
	_best = 0;
	for "_j" from 1 to ((count _acopy) - 1) do {
		_a = _acopy select _j;
		_b = _acopy select _best;
		if (([_a, _b] + _extra_vars) call _comp) then {
			_best = _j;
		};
	};
	_acc pushBack (_acopy select _best);
	_acopy set [_best, "#DELETE!"];
	_acopy = _acopy - ["#DELETE!"];
};
_acc;  // RETURN //////////////////////////////////////////////////////////////