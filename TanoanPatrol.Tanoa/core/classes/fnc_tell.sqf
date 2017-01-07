/////////////////////////////// fnc_tell /////////////////////////// 2016-10-23
/*  Send a message to an object, collecting the result   */
///////////////////////////////////////////////////////////
private [                //                                    
         "_instance",    // Vehicle  [IN/0]                            //
         "_message",     // String   [IN/1]                           //// 
         "_parameters",  // Array    [IN/2[,3..]]                    ////// 
         "_classes",     // alists                                  ///  ///  
         "_methods",     // alist                                  ///    ///
         "_result"       // Element [OUT]                         ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_instance = _this select 0;
_message = _this select 1;
_parameters = [_this, 2, 0] call fnc_subseq;
_classes = [[["_cname"],
             "[_cname, Classes] call fnc_alist_get"] call fnc_lambdastr,
            _instance getVariable ["class_names", []]] call fnc_map;
_methods = [[["_method_list", "_msg"],
             "[_msg, _method_list] call fnc_alist_get"] call fnc_lambdastr,
            _classes, [_message]] call fnc_mapwith;
_methods = [[["_x"], "not isNil ""_x"""] call fnc_lambdastr,
            _methods] call fnc_filter;
_result = ([_instance] + _parameters) call (_methods select 0);
if (not isNil "_result") then {
	_result;
};  // RETURN //////////////////////////////////////////////////////////