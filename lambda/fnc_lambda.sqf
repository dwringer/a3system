////////////////////////////// fnc_lambda ////////////////////////// 2016-10-21
/*  Create and compile an anonymous function   */
/////////////////////////////////////////////////
private [                //  NOT TESTED ! NOT TESTED ! NOT TESTED ! NOT TESTED
         "_parameters",  // Array  [IN/0]                              //
         "_code",        // String [IN/1]                             //// 
         "_context",     // String                                   ////// 
         "_func"         // Code   [OUT]                            ///  ///  
                         //                                        ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_parameters = _this select 0;
_code = _this select 1;
_context = "";
for "_i" from 0 to ((count _parameters) - 1) do {
        _context = format ["%1 %2 = _this select %3; ",
	                   _context, _parameters select _i, _i];
};
_func = compile format ["%1 %2;", _context, _code];
_func;  // RETURN /////////////////////////////////////////////////////////////

/* EX:
    _sum = [3, 4, 5] call ([["_x", "_y", "_z"], 
                            "_x + _y + _z"] call fnc_lambda);
*/