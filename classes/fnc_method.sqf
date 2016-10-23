/////////////////////////////               ////////////////////////     -  -  
/*   */
//////////////////////////////////////////////////////////////////
private [                                                      
         "_class_name",                                                //
         "_method_name",                                              //// 
         "_method",                                                  ////// 
         "_methods"                                                 ///  ///  
                                                                   ///    ///
                                                                  ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_class_name = _this select 0;
_method_name = _this select 1;
_method = _this select 2;
_methods = [_class_name, Classes] call fnc_alist_get;
_methods = [_method_name, _method, _methods] call fnc_alist_set;
Classes = [_class_name, _methods, Classes] call fnc_alist_set;
