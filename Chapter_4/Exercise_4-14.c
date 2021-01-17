/**
 * Exercise 4-14 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * swap:  swap arguments using a macro
 * -----------------------------------
 */

/*
 * By using braces to define a new block, we confine these variables to the
 * scope of this block, preventing problems with similar named variables.
 *
 * This macro will work as long as no input argument is named '_temp'.
 */
#define swap(t,x,y) { \
	t _temp;          \
	_temp = y;        \
	y     = x;        \
	x     = _temp;    \
}