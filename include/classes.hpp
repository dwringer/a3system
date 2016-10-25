fnc_class = compile preprocessfile "classes\fnc_class.sqf";
fnc_instance = compile preprocessfile "classes\fnc_instance.sqf";
fnc_new = compile preprocessfile "classes\fnc_new.sqf";
fnc_method = compile preprocessfile "classes\fnc_method.sqf";
fnc_tell = compile preprocessfile "classes\fnc_tell.sqf";

Classes = [];

#define DEFCLASS(NAME)  [NAME, [
#define DEFMETHOD(CLS, NAME) [CLS, NAME, [
#define DO ,
#define ENDCLASS ] call fnc_lambda] call fnc_class
#define ENDMETHOD ] call fnc_lambda] call fnc_method
