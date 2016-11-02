MarkerIndex = 0;

DEFCLASS("Marker") ["_self", "_position", "_shape", "_type", "_size"] DO {
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "name",
	 format ["MarkerInstance%1", MarkerIndex]] call fnc_tell;
	MarkerIndex = MarkerIndex + 1;
	[_self, "_setf", "position", _position] call fnc_tell;
	[_self, "_setf", "shape", _shape] call fnc_tell;
	[_self, "_setf", "type", _type] call fnc_tell;
        [_self, "_setf", "size", _size] call fnc_tell;
        _self
} ENDCLASS;


DEFMETHOD("Marker", "set_alpha") ["_self", "_alpha"] DO {
	[_self, "_setf", "alpha", _alpha] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_brush") ["_self", "_brush"] DO {
	[_self, "_setf", "brush", _brush] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_color") ["_self", "_color"] DO {
	[_self, "_setf", "color", _color] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_direction") ["_self", "_direction"] DO {
	[_self, "_setf", "direction", _direction] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_position") ["_self", "_position"] DO {
	[_self, "_setf", "position", _position] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_shape") ["_self", "_shape"] DO {
	[_self, "_setf", "shape", _shape] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_size") ["_self", "_size"] DO {
	[_self, "_setf", "size", _size] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_text") ["_self", "_text"] DO {
	[_self, "_setf", "text", _text] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_type") ["_self", "_type"] DO {
	[_self, "_setf", "type", _type] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "redraw") ["_self"] DO {
	private ["_marker"];
	_marker = [_self, "_getf", "marker"] call fnc_tell;
	if (not isNil "_marker") then {
		[_self, "hide"] call fnc_tell;
		[_self, "show"] call fnc_tell;
	};
} ENDMETHOD;


DEFMETHOD("Marker", "show") ["_self"] DO {
	private ["_marker", "_name", "_position", "_shape", "_type", "_size",
                 "_brush", "_color", "_direction", "_text", "_alpha"];
	_name = [_self, "_getf", "name"] call fnc_tell;
	_position = [_self, "_getf", "position"] call fnc_tell;
	_marker = createMarker [_name, _position];
	_shape = [_self, "_getf", "shape"] call fnc_tell;
	_type = [_self, "_getf", "type"] call fnc_tell;
	_size = [_self, "_getf", "size"] call fnc_tell;
	_brush = [_self, "_getf", "brush"] call fnc_tell;
	_color = [_self, "_getf", "color"] call fnc_tell;
	_direction = [_self, "_getf", "direction"] call fnc_tell;
	_text = [_self, "_getf", "text"] call fnc_tell;
	_alpha = [_self, "_getf", "alpha"] call fnc_tell;
	_marker setMarkerShape _shape;
	if (not isNil "_type") then {
		_marker setMarkerType _type;
	};
	if (not isNil "_size") then {
		_marker setMarkerSize _size;
	};
	if (not isNil "_brush") then {
		_marker setMarkerBrush _brush;
	};
	if (not isNil "_color") then {
		_marker setMarkerColor _color;
	};
	if (not isNil "_direction") then {
		_marker setMarkerDir _direction;
	};
	if (not isNil "_text") then {
		_marker setMarkerText _text;
	};
	if (not isNil "_alpha") then {
		_marker setMarkerAlpha _alpha;
	};
	[_self, "_setf", "marker", _marker] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "hide") ["_self"] DO {
	deleteMarker ([_self, "_getf", "name"] call fnc_tell);
	[_self, "_setf", "marker", nil] call fnc_tell;
} ENDMETHOD;
