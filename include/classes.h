#ifndef __CLASSES_H__
#define __CLASSES_H__
fnc_class = compile preprocessfile "classes\fnc_class.sqf";
fnc_instance = compile preprocessfile "classes\fnc_instance.sqf";
fnc_new = compile preprocessfile "classes\fnc_new.sqf";
fnc_method = compile preprocessfile "classes\fnc_method.sqf";
fnc_tell = compile preprocessfile "classes\fnc_tell.sqf";
fnc_tells = compile preprocessfile "classes\fnc_tells.sqf";

Classes = [];


#define DEFCLASS(NAME)  [NAME, [
#define DEFMETHOD(CLS, NAME)  [CLS, NAME, [
#define DO  ,
#define ENDCLASS  ] call fnc_lambda] call fnc_class
#define ENDMETHOD  ] call fnc_lambda] call fnc_method
#define ENDCLASSV  ] call fnc_vlambda] call fnc_class
#define ENDMETHODV  ] call fnc_vlambda] call fnc_method
#define SUPER(SUP, BASE)  [BASE, SUP] call fnc_instance
#define SUPER_ARGS(SUP, BASE)  ([BASE, SUP] + 
#define ENDARGS  ) call fnc_instance
#define ALIAS(CLS, METH, SUP, SUPMETH)		\
	[CLS, METH,  \
         [SUPMETH, [SUP, Classes] call fnc_alist_get] call fnc_alist_get  \
	] call fnc_method
#endif
