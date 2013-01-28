#include "cHardwarePlatform_Win.h"

namespace bmcore
{
	cHardwarePlatform_Win* cHardwarePlatform_Win::sm_pinstance = NULL;

	cHardwarePlatform_Win* cHardwarePlatform_Win::Get()
	{
		if (NULL == sm_pinstance)
			sm_pinstance = new cHardwarePlatform_Win();

		return sm_pinstance;
	}

	cHardwarePlatform_Win::cHardwarePlatform_Win(void)
	{
		m_sysInfo = sPlatformInfo();
		m_sysInfo.CPUSpeed = -1.0;
		m_sysInfo.diskAccess = -1.0;
		m_sysInfo.diskRead = -1.0;
		m_sysInfo.memSize = 0;
		m_sysInfo.name = (tuChar8*)"Unknown";
		m_sysInfo.numCPUs = 0;
		m_sysInfo.numMemBanks = 0;
		initialize();
	}


	cHardwarePlatform_Win::~cHardwarePlatform_Win(void)
	{
		if (NULL != sm_pinstance)
			delete sm_pinstance;
		sm_pinstance = NULL;
	}

	tReal32 cHardwarePlatform_Win::getCPUSpeed(void)
	{
		return m_sysInfo.CPUSpeed;
	}

	tuChar8* cHardwarePlatform_Win::getDevURL(void)
	{
		return (tuChar8*)"https://sourceforge.net/users/michaelkelly322";
	}

	tReal32 cHardwarePlatform_Win::getDiskAccessSpeed(void)
	{
		return m_sysInfo.diskAccess;
	}

	tReal32 cHardwarePlatform_Win::getDiskReadSpeed(void)
	{
		return m_sysInfo.diskRead;
	}

	tuChar8* cHardwarePlatform_Win::getDocsURL(void)
	{
		return (tuChar8*)"./docs";
	}

	tMemSize cHardwarePlatform_Win::getMemorySize(void)
	{
		return m_sysInfo.memSize;
	}

	tuInt32 cHardwarePlatform_Win::getNumCPUs(void)
	{
		return m_sysInfo.numCPUs;
	}

	tuInt32 cHardwarePlatform_Win::getNumMemBanks(void)
	{
		return m_sysInfo.numMemBanks;
	}

	tuChar8* cHardwarePlatform_Win::getPlatform(void)
	{
		return m_sysInfo.name;
	}

	tBool cHardwarePlatform_Win::initialize(void)
	{
		HRESULT hres;

		// Setup WMI Queries
		bstr_t procQuery = bstr_t("SELECT * FROM Win32_Processor");
		bstr_t memQuery = bstr_t("SELECT * FROM Win32_MemoryArray");
		bstr_t memBankQuery = bstr_t("SELECT * FROM Win32_PhysicalMemory");
		bstr_t diskQuery = bstr_t("SELECT * FROM Win32_PerfFormattedData_PerfDisk_PhysicalDisk");
		bstr_t osQuery = bstr_t("SELECT * FROM WIN32_OperatingSystem");
	

		// Step 1: --------------------------------------------------
		// Initialize COM. ------------------------------------------

		hres =  CoInitializeEx(0, COINIT_MULTITHREADED); 
		if (FAILED(hres))
		{
			BMTrace (SID_ERROR("Failed to initialize COM library. Error code = 0x"));// << hres << endl;
			return FALSE;                  // Program has failed.
		}

		// Step 2: --------------------------------------------------
		// Set general COM security levels --------------------------
		// Note: If you are using Windows 2000, you need to specify -
		// the default authentication credentials for a user by using
		// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
		// parameter of CoInitializeSecurity ------------------------

		hres =  CoInitializeSecurity(
			NULL, 
			-1,                          // COM authentication
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities 
			NULL                         // Reserved
			);

                      
		if (FAILED(hres))
		{
			cout << "Failed to initialize security. Error code = 0x" 
				<< hex << hres << endl;
			CoUninitialize();
			return FALSE;                    // Program has failed.
		}
    
		// Step 3: ---------------------------------------------------
		// Obtain the initial locator to WMI -------------------------

		IWbemLocator *pLoc = NULL;

		hres = CoCreateInstance(
			CLSID_WbemLocator,             
			0, 
			CLSCTX_INPROC_SERVER, 
			IID_IWbemLocator, (LPVOID *) &pLoc);
 
		if (FAILED(hres))
		{
			cout << "Failed to create IWbemLocator object."
				<< " Err code = 0x"
				<< hex << hres << endl;
			CoUninitialize();
			return FALSE;                 // Program has failed.
		}

		// Step 4: -----------------------------------------------------
		// Connect to WMI through the IWbemLocator::ConnectServer method

		IWbemServices *pSvc = NULL;
	
		// Connect to the root\cimv2 namespace with
		// the current user and obtain pointer pSvc
		// to make IWbemServices calls.
		hres = pLoc->ConnectServer(
			 _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
			 NULL,                    // User name. NULL = current user
			 NULL,                    // User password. NULL = current
			 0,                       // Locale. NULL indicates current
			 NULL,                    // Security flags.
			 0,                       // Authority (for example, Kerberos)
			 0,                       // Context object 
			 &pSvc                    // pointer to IWbemServices proxy
			 );
    
		if (FAILED(hres))
		{
			cout << "Could not connect. Error code = 0x" 
				 << hex << hres << endl;
			pLoc->Release();     
			CoUninitialize();
			return FALSE;                // Program has failed.
		}

		BMTrace (SID_INFO("Connected to ROOT\\CIMV2 WMI namespace"));


		// Step 5: --------------------------------------------------
		// Set security levels on the proxy -------------------------

		hres = CoSetProxyBlanket(
		   pSvc,                        // Indicates the proxy to set
		   RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		   RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		   NULL,                        // Server principal name 
		   RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		   RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		   NULL,                        // client identity
		   EOAC_NONE                    // proxy capabilities 
		);

		if (FAILED(hres))
		{
			cout << "Could not set proxy blanket. Error code = 0x" 
				<< hex << hres << endl;
			pSvc->Release();
			pLoc->Release();     
			CoUninitialize();
			return FALSE;               // Program has failed.
		}

		// Step 6: --------------------------------------------------
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		IEnumWbemClassObject* pMemEnumerator = NULL;
		IEnumWbemClassObject* pMemBankEnumerator = NULL;
		IEnumWbemClassObject* pProcEnumerator = NULL;
		IEnumWbemClassObject* pDiskEnumerator = NULL;
		IEnumWbemClassObject* pOSEnumerator = NULL;
		HRESULT memRes;
		HRESULT memBankRes;
		HRESULT procRes;
		HRESULT diskRes;
		HRESULT osRes;

    
		memRes = pSvc->ExecQuery(
			bstr_t("WQL"), 
			memQuery,
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pMemEnumerator);

		memBankRes = pSvc->ExecQuery(
			bstr_t("WQL"), 
			memBankQuery,
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pMemBankEnumerator);

		procRes = pSvc->ExecQuery(
			bstr_t("WQL"), 
			procQuery,
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pProcEnumerator);

		diskRes = pSvc->ExecQuery(
			bstr_t("WQL"), 
			diskQuery,
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pDiskEnumerator);

		osRes = pSvc->ExecQuery(
			bstr_t("WQL"), 
			osQuery,
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
			NULL,
			&pOSEnumerator);
    
		if (FAILED(memRes) || FAILED(procRes) || FAILED(diskRes) || FAILED(osRes))
		{
			cout << "WMI Query Failed." << hex << hres << endl;

			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return FALSE;               // Program has failed.
		}

		//	Mem space enumeration
    
    
   
		while (pMemEnumerator)
		{
			IWbemClassObject *pclsObj;
			ULONG uReturn = 0;
			HRESULT hr = pMemEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);

			if(0 == uReturn)
			{
				break;
			}
		
			VARIANT vtProp;

			// Get the value of the Name property
			hr = pclsObj->Get(L"EndingAddress", 0, &vtProp, 0, 0);
			m_sysInfo.memSize = (tMemSize)vtProp.vt * 1024;
			VariantClear(&vtProp);

			pclsObj->Release();
		}

		//	Mem hardware enumeration
		tuInt32 numBanks = 0;
		ULONG uReturn = 0;
		while (pMemBankEnumerator)
		{
			IWbemClassObject *pclsObj;
			HRESULT hr = pMemBankEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);

			if(0 == uReturn || FAILED(hr))
			{
				break;
			}

			numBanks++;

			pclsObj->Release();
		}
		m_sysInfo.numMemBanks = numBanks;

		//	Processor query enumeration
		while (pProcEnumerator)
		{
			IWbemClassObject *pclsObj;
			ULONG uReturn = 0;
			HRESULT hr = pProcEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);

			if(0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;

			// Get the value of the Name property
			hr = pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
			m_sysInfo.CPUSpeed = (tReal32)vtProp.intVal / 1024;
			VariantClear(&vtProp);

			hr = pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
			m_sysInfo.numCPUs = (tuInt32)vtProp.intVal;
			VariantClear(&vtProp);

			pclsObj->Release();
		}

		//	Disk query Enumeration
		while (pDiskEnumerator)
		{
			IWbemClassObject *pclsObj;
			ULONG uReturn = 0;
			HRESULT hr = pDiskEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);

			if(0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;

			// Get the value of the Name property
			hr = pclsObj->Get(L"DiskBytesPerSec", 0, &vtProp, 0, 0);
			m_sysInfo.diskAccess = (tReal32)vtProp.intVal / (1024*1024);
			VariantClear(&vtProp);

			hr = pclsObj->Get(L"DiskReadBytesPerSec", 0, &vtProp, 0, 0);
			m_sysInfo.diskRead = (tReal32)vtProp.intVal / (1024*1024);
			VariantClear(&vtProp);

			pclsObj->Release();
		}

		//	OS query enumeration
		while (pOSEnumerator)
		{
			IWbemClassObject *pclsObj;
			ULONG uReturn = 0;
			HRESULT hr = pOSEnumerator->Next(WBEM_INFINITE, 1, 
				&pclsObj, &uReturn);

			if(0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;

			// Get the value of the Name property
			hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
			m_sysInfo.name = (tuChar8*)_com_util::ConvertBSTRToString(vtProp.bstrVal);
			VariantClear(&vtProp);

			pclsObj->Release();
		}

		// Cleanup
		// ========
    
		pSvc->Release();
		pLoc->Release();
		pMemEnumerator->Release();
		pProcEnumerator->Release();
		pOSEnumerator->Release();
		pDiskEnumerator->Release();
		//pclsObj->Release();
		CoUninitialize();

		return TRUE;   // Program successfully completed.
	
	}
}