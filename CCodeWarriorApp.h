// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CCodeWarriorApp wrapper class

class CCodeWarriorApp : public COleDispatchDriver
{
public:
	CCodeWarriorApp(){} // Calls COleDispatchDriver default constructor
	CCodeWarriorApp(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCodeWarriorApp(const CCodeWarriorApp& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICodeWarriorApp methods
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_FullName()
	{
		CString result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Projects()
	{
		LPDISPATCH result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CreatableItems()
	{
		LPDISPATCH result;
		InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Documents()
	{
		LPDISPATCH result;
		InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ActiveDocument()
	{
		LPDISPATCH result;
		InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_DefaultProjectDocument()
	{
		LPDISPATCH result;
		InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_DefaultProject()
	{
		LPDISPATCH result;
		InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_AllowUserInteraction(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x7c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_VersionControl()
	{
		LPDISPATCH result;
		InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_UserTrees()
	{
		LPDISPATCH result;
		InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Debugger()
	{
		LPDISPATCH result;
		InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CompareInterface()
	{
		LPDISPATCH result;
		InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH CreateProject(LPCTSTR filePath, LPCTSTR linkerName, LPCTSTR designName, LPCTSTR targetName, BOOL fMakeVisible)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL ;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, filePath, linkerName, designName, targetName, fMakeVisible);
		return result;
	}
	LPDISPATCH CreateProjectByFileSpec(LPDISPATCH projectFileSpec, LPCTSTR linkerName, LPCTSTR designName, LPCTSTR targetName, LPDISPATCH stationeryFileSpec, BOOL fMakeVisible)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_BSTR VTS_BSTR VTS_BSTR VTS_DISPATCH VTS_BOOL ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, projectFileSpec, linkerName, designName, targetName, stationeryFileSpec, fMakeVisible);
		return result;
	}
	LPDISPATCH ImportProject(LPCTSTR textFilePath, LPCTSTR projectFilePath, BOOL fMakeVisible)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL ;
		InvokeHelper(0x80, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, textFilePath, projectFilePath, fMakeVisible);
		return result;
	}
	LPDISPATCH ImportProjectByFileSpec(LPDISPATCH textFileSpec, LPDISPATCH projectFileSpec, BOOL fMakeVisible)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_BOOL ;
		InvokeHelper(0x81, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, textFileSpec, projectFileSpec, fMakeVisible);
		return result;
	}
	LPDISPATCH OpenProject(LPCTSTR filePath, BOOL fMakeVisible, long convertOption, long revertOption)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, filePath, fMakeVisible, convertOption, revertOption);
		return result;
	}
	LPDISPATCH OpenProjectByFileSpec(LPDISPATCH FileSpec, BOOL fMakeVisible, long convertOption, long revertOption)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileSpec, fMakeVisible, convertOption, revertOption);
		return result;
	}
	void AddCreatableItem(LPUNKNOWN Item)
	{
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Item);
	}
	void RemoveCreatableItem(LPUNKNOWN Item)
	{
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Item);
	}
	LPDISPATCH FindLogicalFolder(LPCTSTR folderName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, folderName);
		return result;
	}
	LPDISPATCH FindDesignForDataModel(LPUNKNOWN DataModel)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0x71, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, DataModel);
		return result;
	}
	LPUNKNOWN GetNamedPluginData(LPCTSTR resourceName)
	{
		LPUNKNOWN result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, parms, resourceName);
		return result;
	}
	void SetNamedPluginData(LPCTSTR resourceName, LPUNKNOWN pluginData)
	{
		static BYTE parms[] = VTS_BSTR VTS_UNKNOWN ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms, resourceName, pluginData);
	}
	void RemoveNamedPluginData(LPCTSTR resourceName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_EMPTY, NULL, parms, resourceName);
	}
	VARIANT GetSetting(LPCTSTR settingsName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, settingsName);
		return result;
	}
	void SetSetting(LPCTSTR settingsName, VARIANT pval)
	{
		static BYTE parms[] = VTS_BSTR VTS_VARIANT ;
		InvokeHelper(0x76, DISPATCH_METHOD, VT_EMPTY, NULL, parms, settingsName, &pval);
	}
	LPDISPATCH OpenTextDocumentByFileSpec(LPDISPATCH FileSpec, BOOL create)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL ;
		InvokeHelper(0x79, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileSpec, create);
		return result;
	}
	LPDISPATCH OpenTextDocument(LPCTSTR inPath, BOOL create)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, inPath, create);
		return result;
	}
	LPDISPATCH OpenUntitledTextDocument()
	{
		LPDISPATCH result;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void AttemptModify(LPDISPATCH FileSpec, long uiParameter, LPDISPATCH Project)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x7e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileSpec, uiParameter, Project);
	}
	void DoCommand(long commandID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, commandID);
	}
	void QueueDeferredAction(LPUNKNOWN action)
	{
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0x82, DISPATCH_METHOD, VT_EMPTY, NULL, parms, action);
	}
	BOOL IsBuildInProgress()
	{
		BOOL result;
		InvokeHelper(0x85, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void AddUserTree(LPDISPATCH pval)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pval);
	}
	void RemoveUserTree(LPDISPATCH pval)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pval);
	}
	LPDISPATCH CreateUserTree(LPCTSTR displayName, LPCTSTR value, long Type, LPCTSTR KeyName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x8c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, displayName, value, Type, KeyName);
		return result;
	}
	LPDISPATCH OpenProjectWithOptions(LPCTSTR filePath, BOOL fMakeVisible, long convertOption, long revertOption, long projectOption)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, filePath, fMakeVisible, convertOption, revertOption, projectOption);
		return result;
	}
	LPDISPATCH OpenProjectByFileSpecWithOptions(LPDISPATCH FileSpec, BOOL fMakeVisible, long convertOption, long revertOption, long projectOption)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileSpec, fMakeVisible, convertOption, revertOption, projectOption);
		return result;
	}
	void Quit(long val)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, val);
	}
	void OpenDocument(LPCTSTR filePath)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, filePath);
	}

	// ICodeWarriorApp properties
public:

};
