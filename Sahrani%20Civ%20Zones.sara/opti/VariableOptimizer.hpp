DEFCLASS("VariableOptimizer") ["_self"] DO {
	SUPER("Optimizer", _self);
	_self
} ENDCLASS;


DEFMETHOD("VariableOptimizer", "add_objective") ["_self",
						"_maximize",
						"_min_range",
						"_max_range",
						"_function",
						"_parameter_string_generator",
						"_generator_parameter_ranges"
						] DO {
	/* Example call:
	 *   [_optimizer, "add_objective",
	 *    false, [0, 0], [1, 1], fnc_normed_obj_foo, 
	 *    {"[_x, _x op var]"}, []] call fnc_tell
         *   This leaves us with variables of min, max, and any parameters at the
         *   end for the parameter generation function (in this case, none)
	 *
	 *   [_optimizer, "add_objective", false, [0.2, 0], [0.8, 1], objective_fn,
	 *    [["_a", "_b", "_c"], {format ["...", _a, _b, _c]}] call fnc_lambda,
	 *    [[0, 1], [20, 30], [300, 50]]] call fnc_tell
	 */
} ENDMETHOD;
