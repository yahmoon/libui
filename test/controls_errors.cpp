// 11 june 2019
#include "test.h"

// TODO once this is filled in, verify against the documentation that this is all the error cases
// TODO add an internal marker to uiEvent as well, just to be safe?

static const struct checkErrorCase casesBeforeOSVtable[] = {
	{
		"uiRegisterControlType() with NULL name",
		[](void) {
			uiRegisterControlType(NULL, NULL, NULL, 0);
		},
		"uiRegisterControlType(): invalid null pointer for name",
	},
	{
		"uiRegisterControlType() with NULL vtable",
		[](void) {
			uiRegisterControlType("name", NULL, NULL, 0);
		},
		"uiRegisterControlType(): invalid null pointer for uiControlVtable",
	},
	{
		"uiRegisterControlType() with vtable with wrong size",
		[](void) {
			uiControlVtable vtable;
	
			memset(&vtable, 0, sizeof (uiControlVtable));
			vtable.Size = 1;
			uiRegisterControlType("name", &vtable, NULL, 0);
		},
		"uiRegisterControlType(): wrong size 1 for uiControlVtable",
	},
#define checkVtableMethod(name) \
	{ \
		"uiRegisterControlType() with NULL " #name " method", \
		[](void) { \
			uiControlVtable vtable; \
			vtable = *testVtable(); \
			vtable.name = NULL; \
			uiRegisterControlType("name", &vtable, NULL, 0); \
		}, \
		"uiRegisterControlType(): required uiControlVtable method " #name "() missing for uiControl type name", \
	}
	checkVtableMethod(Init),
	checkVtableMethod(Free),
	{
		"uiRegisterControlType() with NULL OS vtable",
		[](void) {
			uiRegisterControlType("name", testVtable(), NULL, 0);
		},
		"uiRegisterControlType(): invalid null pointer for uiControlOSVtable",
	},
	{ NULL, NULL, NULL },
};

static const struct checkErrorCase casesAfterOSVtable[] = {
	{
		"uiCheckControlType() with a NULL pointer",
		[](void) {
			uiCheckControlType(NULL, uiControlType());
		},
		"uiCheckControlType(): invalid null pointer for uiControl",
	},
	{
		"uiCheckControlType() with non-control",
		[](void) {
			static char buf[] = "this is not a uiControl";

			uiCheckControlType(buf, uiControlType());
		},
		"uiCheckControlType(): object passed in not a uiControl",
	},
	{
		"uiCheckControlType() with a control with an unknown type",
		[](void) {
			// TODO
		},
		"TODO",
	},
	{
		"uiCheckControlType() asking for an unknown control type",
		[](void) {
			// TODO
		},
		"TODO",
	},
	{
		"uiCheckControlType() with a type mismatch",
		[](void) {
			// TODO
		},
		"TODO",
	},

	{
		"uiNewControl() with uiControlType()",
		[](void) {
			uiNewControl(uiControlType(), NULL);
		},
		"uiNewControl(): uiControlType() passed in when specific control type needed",
	},
	{
		"uiNewControl() with an unknown control type",
		[](void) {
			uiNewControl(5, NULL);
		},
		"uiNewControl(): unknown uiControl type 5 requested",
	},
	// TODO have Init() fail

	// TODO uiControlFree()

	{
		"uiControlImplData() with a NULL uiControl",
		[](void) {
			uiControlImplData(NULL);
		},
		"uiControlImplData(): invalid null pointer for uiControl",
	},
	{ NULL, NULL, NULL },
};

testingTest(ControlErrors)
{
	checkProgrammerErrors(t, casesBeforeOSVtable);
	// OS vtable sizes are tested per-OS
	checkProgrammerErrors(t, casesAfterOSVtable);
}
