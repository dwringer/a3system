// TODO: Test this to establish basic inheritance setup.

DEFCLASS("BaseObject") ["_self"] DO {
	/* * *
	 * Initialize base object class instance.
         * * */
	SUPER("Dictionary", _self);
	_self
} ENDCLASS;

