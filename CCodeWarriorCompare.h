// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CCodeWarriorCompare wrapper class

class CCodeWarriorCompare : public COleDispatchDriver
{
public:
	CCodeWarriorCompare(){} // Calls COleDispatchDriver default constructor
	CCodeWarriorCompare(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCodeWarriorCompare(const CCodeWarriorCompare& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICodeWarriorCompare methods
public:
	void CompareFilesByFileSpec(LPDISPATCH srcFile, LPDISPATCH destFile, BOOL ignoreCase, BOOL ignoreSpace)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcFile, destFile, ignoreCase, ignoreSpace);
	}
	void CompareFiles(LPCTSTR srcFile, LPCTSTR destFile, BOOL ignoreCase, BOOL ignoreSpace)
	{	
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcFile, destFile, ignoreCase, ignoreSpace);
	}
	void CompareFolders(LPCTSTR srcFolder, LPCTSTR destFolder, BOOL inIgnoreCase, BOOL inIgnoreSpace, BOOL showDifferentFiles, BOOL compareTextFileContents)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcFolder, destFolder, inIgnoreCase, inIgnoreSpace, showDifferentFiles, compareTextFileContents);
	}

	// ICodeWarriorCompare properties
public:

};
