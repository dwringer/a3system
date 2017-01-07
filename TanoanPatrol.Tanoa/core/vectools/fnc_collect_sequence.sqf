////////////////////////// fnc_collect_sequence /////////////////// 2016-12-21
/* Gather a numbered (<var>_1, ...) sequence of vars by name  */
////////////////////////////////////////////////////////////////
private [                                                      
         "_next",                                                      //
         "_acc",                                                      //// 
         "_name",                                                    ////// 
         "_i"                                                       ///  ///  
                                                                   ///    ///
                                                                  ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_name = _this;
_acc = [];

_i = 1;
_next = call compile format ["%1_%2", _name, _i];
while {not isNil "_next"} do {
	_acc pushBack _next;
        _i = _i + 1;
        _next = call compile format ["%1_%2", _name, _i];
};
_acc
