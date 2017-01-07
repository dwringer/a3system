///////////////////////////// fnc_alist_set //////////////////////// 2016-12-09
/*  Return copy of pair-array with a given key/val pair set  */
///////////////////////////////////////////////////////////////
private [           //                                         
         "_key",    // Object [IN/0]                                   //
         "_value",  // Object [IN/1]                                  //// 
         "_alist",  // Array  [IN/2]                                 ////// 
         "_test",   // Object                                       ///  ///  
         "_copy"    // Array  [OUT]                                ///    ///
                    //                                            ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_key = _this select 0;
_value = _this select 1;
_alist = _this select 2;
_test = [_key, _alist] call fnc_alist_get;
if (not isNil "_test") then {
	_copy = _alist - [[_key, _test]];
} else {
	_copy = _alist;
};
_copy pushBack [_key, _value];
_copy;  // RETURN ////////////////////////////////////////////////////////////