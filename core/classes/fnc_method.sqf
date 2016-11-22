////////////////////////////// fnc_method ////////////////////////// 2016-10-23
/*  Add a method to a class  */
///////////////////////////////
private [                 //                                   
         "_class_name",   // String   [IN/0]                           //
         "_method_name",  // String   [IN/1]                          //// 
         "_method",       // Function [IN/2]                         ////// 
         "_methods"       // alist                                  ///  ///  
                          //                                       ///    ///
                          //                                      ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_class_name = _this select 0;
_method_name = _this select 1;
_method = _this select 2;
_methods = [_class_name, Classes] call fnc_alist_get;
_methods = [_method_name,
            _method,
            _methods] call fnc_alist_set;
Classes = [_class_name, _methods, Classes] call fnc_alist_set;
///////////////////////////////////////////////////////////////////////////////