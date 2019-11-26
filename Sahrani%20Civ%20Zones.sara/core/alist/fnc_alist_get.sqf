///////////////////////////// fnc_alist_get //////////////////////// 2016-10-22
/*  Look up a value associated with a key in an array of pairs   */
///////////////////////////////////////////////////////////////////
private [           //                                         
         "_key",    // Object                                          //
         "_arr",    // Array                                          //// 
         "_value",  // Object                                        ////// 
         "_index",  // int                                          ///  ///  
         "_test"    // Object                                      ///    ///
                    //                                            ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_key = _this select 0;
_arr = _this select 1;
_value = nil;
_index = 0;
while {_index < count _arr} do {
        _test = _arr select _index;
        if ((_test select 0) == _key) then {
	        _value = _test select 1;
		_index = count _arr;
        } else {
                _index = _index + 1;
        };
};
if (not isNil "_value") then {
	_value;
};  // RETURN /////////////////////////////////////////////////////////////////