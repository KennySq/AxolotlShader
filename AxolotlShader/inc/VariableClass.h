#pragma once

enum eVariableClass
{
	CLASS_SCALAR = 0,
	CLASS_VECTOR,
	CLASS_MATRIX_ROWS,
	CLASS_MATRIX_COLUMNS,
	CLASS_OBJECT,
	CLASS_STRUCT,
	CLASS_INTERFACE_CLASS,
	CLASS_INTERFACE_POINTER,
	CLASS_FORCE_DWORD = 0x7fffffff
};