////////////////////////////// fnc_closest ///////////////////////// 2016-10-21
/*  Return n nearest neighbors of an object in an array   */
////////////////////////////////////////////////////////////
private [         //
         "_obj",  // Object   [IN/A1/B1]                               //
         "_arr",  // Array    [IN/A2/B2]                              //// 
         "_num",  // int      [IN/A3]                                ////// 
         "_cmp",  // Function                                       ///  ///  
         "_acc",  // Array    [OUT]                                ///    ///
         "_acopy" // Array                                        ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_obj = _this select 0;
_arr = _this select 1;
_acopy = [];
for "_i" from 0 to ((count _arr) - 1) do {
	_acopy pushBack (_arr select _i);
};
if ((count _this) == 3) then {
	_num = _this select 2;
} else {
	_num = 1;
};
_cmp = [["_a", "_b", "_obj"],
        "((_a distance _obj) < (_b distance _obj))"] call fnc_lambdastr;
_acopy  = [_acopy, _cmp, [_obj]] call fnc_sorted;
_acc = [];
for "_i" from 0 to (_num - 1) do {
	_acc pushBack (_acopy select _i);
};
_acc;  // RETURN //////////////////////////////////////////////////////////////
