//**************************************************************
//
//**************************************************************

#ifdef WIN32
#include <afxwin.h>
#endif

#include "NodeProperties.h"
#include <string>

#ifdef WIN32
#include <winperf.h>
#include <pdhmsg.h>
#endif

#include <iostream>
#include <fstream>
#include <list>


// Returns the string representation of the integer parameter num.
using namespace std;

std::string NodeProperties::int2string(int num) {
	std::string ret = "";
	if (num < 0)
		return(std::string("-")+int2string(-num));
	else {
		int number = num;
		char chara;
		while (number > 9) {
			int temp = number % 10;
			chara = '0' + temp;
			ret = chara + ret;
			number = number - temp;
			number = number/10;
		} // end while
		chara = '0' + number;
		ret = chara + ret;
	} // end else
	return(ret);
} // end int2string


// The number of processes running on the computer is stored at the place indicated by the
// parameter. PDH is used to retrieve this information.

bool NodeProperties::processes_number(int *proc_numb) {
	PDH_STATUS pdhStatus = ERROR_SUCCESS;
	LPTSTR szCounterListBuffer = NULL;
	DWORD dwCounterListSize = 0;
	LPTSTR szInstanceListBuffer = NULL;
	DWORD dwInstanceListSize = 0;
	LPTSTR szThisInstance = NULL;

	// Determine the required buffer size for the data. 
	pdhStatus = PdhEnumObjectItems (NULL,NULL,TEXT("Process"),szCounterListBuffer,&dwCounterListSize,szInstanceListBuffer,&dwInstanceListSize,PERF_DETAIL_WIZARD,0);
	if (pdhStatus == ERROR_SUCCESS) {
		// Allocate the buffers and try the call again.
		szCounterListBuffer = (LPTSTR)malloc((dwCounterListSize*sizeof(TCHAR)));
		szInstanceListBuffer = (LPTSTR)malloc((dwInstanceListSize*sizeof(TCHAR)));
		if ((szCounterListBuffer != NULL) && (szInstanceListBuffer != NULL)) {
			pdhStatus = PdhEnumObjectItems(NULL,NULL,TEXT("Process"),szCounterListBuffer,&dwCounterListSize,szInstanceListBuffer,&dwInstanceListSize,PERF_DETAIL_WIZARD,0);
			if (pdhStatus == ERROR_SUCCESS) {
				*proc_numb = 0;
				// Walk the return instance list.
				for (szThisInstance = szInstanceListBuffer;*szThisInstance != 0;szThisInstance += lstrlen(szThisInstance) + 1) {
					(*proc_numb)++;
				} // end for
				if (szCounterListBuffer != NULL)
					free(szCounterListBuffer);
				if (szInstanceListBuffer != NULL)
					free(szInstanceListBuffer);
				return(true);
			} // end if
		} // end if
		if (szCounterListBuffer != NULL)
			free(szCounterListBuffer);
		if (szInstanceListBuffer != NULL)
			free(szInstanceListBuffer);
	} // end if
	return(false);
} // end processes_number

std::string NodeProperties::translate_name(const char* originalName) {
    std::string rtnStr;
	char* localized_name = (char *)malloc(256*sizeof(char));		
	int found = this ->get_localized_name(originalName,localized_name);		

    if(found != 0)
    {
        rtnStr = "";
    } else{
     std::string tmp(localized_name);
     rtnStr = tmp ;
     }
     return rtnStr;
}

int NodeProperties::CPULoad(bool syst) {
	HCOUNTER *hCounter;


	if (syst) { // The System object is used (PDH)
		//std::cout << "Counter path: "<< CNTR_CPU1 << "\n";
   	PdhAddCounter(m_hQuery,strdup(CNTR_CPU1),(DWORD)&pCounter1,&hCounter1);
		hCounter = &hCounter1;
	} else { // The Processor object is used (PDH)
		//std::cout << "Counter path: "<< CNTR_CPU2 << "\n";
		char* localized_name = (char *)malloc(256*sizeof(char));
		
		//std::string cpu_time_str = "\\" + this->translate_name(CPU_MAIN) + "(_Total)\\" + this->translate_name(CPU_TIME);		

    	PdhAddCounter(m_hQuery,strdup(CNTR_CPU2),(DWORD)&pCounter2,&hCounter2);
		hCounter = &hCounter2;

	//PdhAddCounter(m_hQuery,strdup(cpu_time_str.data()),(DWORD)&pCounter2,&hCounter2);
	//	hCounter = &hCounter2;
		
		if(localized_name != NULL)
		    free(localized_name);
	} //end else

   PPDH_RAW_COUNTER ppdhRawCounter1 = new PDH_RAW_COUNTER;
	PPDH_RAW_COUNTER ppdhRawCounter2 = new PDH_RAW_COUNTER;

	Sleep(50);
	if (PdhCollectQueryData(m_hQuery) != ERROR_SUCCESS)
	{
		//std::cerr << "ERROR: PdhCollectQueryData 1\n";
		return(-1);
	}

	// AVF: For debugging purpose
	 // std::cout << "PdhCollectQueryData 1: Successful\n";

	Sleep(50);
	if (PdhGetRawCounterValue(*hCounter,NULL,ppdhRawCounter1) != ERROR_SUCCESS)
	{
		//std::cerr << "ERROR: PdhGetRawCounterValue 1\n";
		return(-1);
	}

	Sleep(50);
	if (PdhCollectQueryData(m_hQuery) != ERROR_SUCCESS)
	{
		//std::cerr << "ERROR: PdhCollectQueryData\n";
		return(-1);
	}


	// AVF: For debugging purpose
	//std::cout << "PdhCollectQueryData 2: Successful\n";

	Sleep(50);
	if (PdhGetRawCounterValue(*hCounter,NULL,ppdhRawCounter2) != ERROR_SUCCESS)
	{
		//std::cerr << "ERROR: PdhGetRawCounterValue 2\n";
		return(-1);
	}

	PDH_FMT_COUNTERVALUE pdhFormattedValue;
	if (PdhCalculateCounterFromRawValue(*hCounter,PDH_FMT_LONG,ppdhRawCounter2,ppdhRawCounter1,&pdhFormattedValue) != ERROR_SUCCESS)
	{
		//std::cerr << "ERROR: PdhCalculateCounterFromRawValue\n";
		return(-1);
	}

	delete(ppdhRawCounter1);
	delete(ppdhRawCounter2);

	return(pdhFormattedValue.longValue);
} // end CPULoad


PPERF_OBJECT_TYPE NodeProperties::FirstObject(PPERF_DATA_BLOCK PerfData) {
	return((PPERF_OBJECT_TYPE)((PBYTE)PerfData + PerfData->HeaderLength));
} // end FirstObject


PPERF_OBJECT_TYPE NodeProperties::NextObject(PPERF_OBJECT_TYPE PerfObj) {
	return((PPERF_OBJECT_TYPE)((PBYTE)PerfObj + PerfObj->TotalByteLength));
} // end NextObject


PPERF_INSTANCE_DEFINITION NodeProperties::FirstInstance(PPERF_OBJECT_TYPE PerfObj) {
	return((PPERF_INSTANCE_DEFINITION)((PBYTE)PerfObj + PerfObj->DefinitionLength));
} // end FirstInstance


PPERF_INSTANCE_DEFINITION NodeProperties::NextInstance(PPERF_INSTANCE_DEFINITION PerfInst) {
	PPERF_COUNTER_BLOCK PerfCntrBlk;
	PerfCntrBlk = (PPERF_COUNTER_BLOCK)((PBYTE)PerfInst + PerfInst->ByteLength);
	return((PPERF_INSTANCE_DEFINITION)((PBYTE)PerfCntrBlk + PerfCntrBlk->ByteLength));
} // end NextInstance


PPERF_COUNTER_DEFINITION NodeProperties::FirstCounter(PPERF_OBJECT_TYPE PerfObj) {
	return((PPERF_COUNTER_DEFINITION)((PBYTE)PerfObj + PerfObj->HeaderLength));
} // end FirstCounter


PPERF_COUNTER_DEFINITION NodeProperties::NextCounter(PPERF_COUNTER_DEFINITION PerfCntr) {
	return((PPERF_COUNTER_DEFINITION)((PBYTE)PerfCntr + PerfCntr->ByteLength));
} // end NextCounter


void NodeProperties::GetNameStrings(){
	HKEY hKeyPerflib;      // handle to registry key
	HKEY hKeyPerflib009;   // handle to registry key
	DWORD dwMaxValueLen;   // maximum size of key values
	DWORD dwBuffer;        // bytes to allocate for buffers
	DWORD dwBufferSize;    // size of dwBuffer
	LPSTR lpCurrentString; // pointer for enumerating data strings
	DWORD dwCounter;       // current counter index

	// Get the number of Counter items.
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,PERFENUMKEY6,0,KEY_READ,&hKeyPerflib);
	dwBufferSize = sizeof(dwBuffer);
	RegQueryValueEx(hKeyPerflib,"Last Counter",NULL,NULL,(LPBYTE)&dwBuffer,&dwBufferSize);
	RegCloseKey(hKeyPerflib);

	dwBuffer2 = dwBuffer;

	// Allocate memory for the names array.
	if (lpNamesArray != NULL)
		free (lpNamesArray);
	lpNamesArray = (LPSTR *)malloc((dwBuffer+1)*sizeof(LPSTR));

	// Open key containing counter and object names.
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,PERFENUMKEY7,0,KEY_READ,&hKeyPerflib009);

	// Get the size of the largest value in the key (Counter or Help).
	RegQueryInfoKey(hKeyPerflib009,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,&dwMaxValueLen,NULL,NULL);

	// Allocate memory for the counter and object names.
	dwBuffer = dwMaxValueLen + 1;
	if (lpNameStrings != NULL)
		free (lpNameStrings);
	lpNameStrings = (LPSTR)malloc(dwBuffer*sizeof(CHAR));

	// Read Counter value.
	RegQueryValueEx(hKeyPerflib009,"Counter",NULL,NULL,(unsigned char *)lpNameStrings,&dwBuffer);

	// Load names into an array, by index.
	for(lpCurrentString=lpNameStrings;*lpCurrentString;lpCurrentString+=(lstrlen(lpCurrentString)+1)) {
		dwCounter = atol( lpCurrentString );
		lpCurrentString += (lstrlen(lpCurrentString)+1);
		lpNamesArray[dwCounter] = (LPSTR)lpCurrentString;
	} // end for

} // end GetNameStrings

void NodeProperties::GetLpmszNameStrings(){
	HKEY hKeyPerflib;      // handle to registry key
	HKEY hKeyPerflib009;   // handle to registry key
	DWORD dwMaxValueLen;   // maximum size of key values
	DWORD dwBuffer;        // bytes to allocate for buffers
	DWORD dwBufferSize;    // size of dwBuffer
	LPSTR lpCurrentString; // pointer for enumerating data strings
	DWORD dwCounter;       // current counter index

	// Get the number of Counter items.
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,PERFENUMKEY6,0,KEY_READ,&hKeyPerflib);
	dwBufferSize = sizeof(dwBuffer);
	RegQueryValueEx(hKeyPerflib,"Last Counter",NULL,NULL,(LPBYTE)&dwBuffer,&dwBufferSize);
	RegCloseKey(hKeyPerflib);


	// Open key containing counter and object names.
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,PERFENUMKEY7,0,KEY_READ,&hKeyPerflib009);

	// Get the size of the largest value in the key (Counter or Help).
	RegQueryInfoKey(hKeyPerflib009,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,&dwMaxValueLen,NULL,NULL);

	// Allocate memory for the counter and object names.
	dwBuffer = dwMaxValueLen + 1;
	if (lpmszNameStrings != NULL)
		free (lpmszNameStrings);
	lpmszNameStrings = (LPSTR)malloc(dwBuffer*sizeof(CHAR));
	

	// Read Counter value.
	while(RegQueryValueEx(HKEY_PERFORMANCE_DATA,"Counter 009",NULL,NULL,(unsigned char *)lpmszNameStrings,&dwBuffer) == ERROR_MORE_DATA) {
		// Get a buffer that is big enough.
		dwBufferSize += BYTEINCREMENT;
		lpmszNameStrings = (LPSTR)realloc(lpmszNameStrings, dwBufferSize);
	} // end while

	// Allocate memory for the names array.
	if (lpmszNamesArray != NULL)
		free (lpmszNamesArray);
	lpmszNamesArray = (LPSTR *)malloc((dwBuffer+1)*sizeof(LPSTR));

    lpmszNamesArraySize = dwBuffer;

	for(int i=0; i<lpmszNamesArraySize; i++){
	    lpmszNamesArray[i] = NULL;
	}
	//RegQueryValueEx(HKEY_PERFORMANCE_DATA,"Counter 009",NULL,NULL,(unsigned char *)lpmszNameStrings,&dwBuffer);

	// Load names into an array, by index.
	for(lpCurrentString=lpmszNameStrings;*lpCurrentString;lpCurrentString+=(lstrlen(lpCurrentString)+1)) {
		dwCounter = atol( lpCurrentString );
		lpCurrentString += (lstrlen(lpCurrentString)+1);
		std::cout << "dwCounter: " << dwCounter << " lpCurrentString: " << lpCurrentString << std::endl;
		lpmszNamesArray[dwCounter] = lpCurrentString;
	} // end for
	
	lpmszNamesArraySize = dwCounter+1;

} // end GetLpsmzNameStrings


void NodeProperties::CommLoad() {
	PPERF_DATA_BLOCK PerfData = NULL;
	PPERF_OBJECT_TYPE PerfObj;
	PPERF_INSTANCE_DEFINITION PerfInst;
	PPERF_COUNTER_DEFINITION PerfCntr;
	DWORD BufferSize = TOTALBYTES;
	DWORD i, k;

	// Get the name strings through the registry.
	GetNameStrings();

	// Allocate the buffer for the performance data.
	PerfData = (PPERF_DATA_BLOCK)malloc(BufferSize);
	while(RegQueryValueEx(HKEY_PERFORMANCE_DATA,"Global",NULL,NULL,(LPBYTE)PerfData,&BufferSize) == ERROR_MORE_DATA) {
		// Get a buffer that is big enough.
		BufferSize += BYTEINCREMENT;
		PerfData = (PPERF_DATA_BLOCK)realloc(PerfData, BufferSize);
	} // end while

	// Get the first object type.
	PerfObj = FirstObject(PerfData);

	// Process all objects.
	for(i=0 ; i < PerfData->NumObjectTypes ; i++) {
		if (PerfObj->ObjectNameTitleIndex < dwBuffer2) {
			if (strcmp(lpNamesArray[PerfObj->ObjectNameTitleIndex], "Network Segment") == 0) {
				// Get the first counter.
				PerfCntr = FirstCounter(PerfObj);
				if(PerfObj->NumInstances > 0) {
					// Get the first instance.
					PerfInst = FirstInstance(PerfObj);
					// Retrieve all instances.
					for(k=0;k < PerfObj->NumInstances;k++) {
						// Display the instance by name.
						char buffer[20];
						sprintf(buffer,"%S",((PBYTE)PerfInst + PerfInst->NameOffset));
						network_segment_instances.push_back(std::string(buffer));
						// Get the next instance.
						PerfInst = NextInstance(PerfInst);
					} // end for
				} // end if
			} else if (strcmp(lpNamesArray[PerfObj->ObjectNameTitleIndex], "Network Interface") == 0) {
				// Get the first counter.
				PerfCntr = FirstCounter(PerfObj);
				network_interface_instances = PerfObj->NumInstances;
			} // end else
		} // end if
		// Get the next object type.
		PerfObj = NextObject(PerfObj);
	} // end for
} // end CommLoad


std::string NodeProperties::Identify(std::string desc) {
	int n = desc.size();
	int i;

	i =  desc.find("Ether");
	if ((i >= 0) && (i < n))
		return(std::string("ethernet"));
	i = desc.find("ether");
	if ((i >= 0) && (i < n))
		return(std::string("ethernet"));
	i = desc.find("ETHER");
	if ((i >= 0) && (i < n))
		return(std::string("ethernet"));
	i = desc.find("Token");
	if ((i >= 0) && (i < n))
		return(std::string("token-ring"));
	i = desc.find("Ring");
	if ((i >= 0) && (i < n))
		return(std::string("token-ring"));
	i = desc.find("tok");
	if ((i >= 0) && (i < n))
		return(std::string("token-ring"));
	i = desc.find("ring");
	if ((i >= 0) && (i < n))
		return(std::string("token-ring"));
	i = desc.find("TOKEN");
	if ((i >= 0) && (i < n))
		return(std::string("token-ring"));
	i = desc.find("RING");
	if ((i >= 0) && (i < n))
		return(std::string("token-ring"));
	i = desc.find("atm");
	if ((i >= 0) && (i < n))
		return(std::string("atm"));
	i = desc.find("Atm");
	if ((i >= 0) && (i < n))
		return(std::string("atm"));
	i = desc.find("ATM");
	if ((i >= 0) && (i < n))
		return(std::string("atm"));
	i = desc.find("ISDN");
	if ((i >= 0) && (i < n))
		return(std::string("isdn"));
	i = desc.find("Isdn");
	if ((i >= 0) && (i < n))
		return(std::string("isdn"));
	i = desc.find("isdn");
	if ((i >= 0) && (i < n))
		return(std::string("isdn"));
	return(std::string("Undefined"));
} // end Identify


// Cut the string parameter line.

std::vector<std::string> NodeProperties::cut(std::string line,char separator) {
	std::vector<std::string> ret;
	std::string store = line;
	int siz = store.size();
	int pos = store.find(separator);
	while ((pos >= 0) && (pos < siz)) {
		std::string store2 = store;
		store2.replace(pos,siz-pos,"");
		ret.push_back(store2);
		store = store.replace(0,pos+1,"");
		siz = store.size();
		pos = store.find(separator);
	}
	if (store.size() > 0)
		ret.push_back(store);
	return(ret);
}


void NodeProperties::start_AverageFreeMemory() {
	mem = true;
	AfxBeginThread(refresh_mem,this); // Creation of an Afx thread.
}


void NodeProperties::stop_AverageFreeMemory() {
	mem = false;
}


int NodeProperties::mem_incr(int i) {
	if (i == HISTORY-1) {
		mem_complete = true;
		return(0);
	} else
		return(i+1);
}


int NodeProperties::mem_decr(int i) {
	if (i == 0) {
		if (mem_complete)
			return(HISTORY-1);
		else
			return(-1);
	} else
		return(i-1);
}


void NodeProperties::start_AverageCPULoad() {
	cpu = true;
	AfxBeginThread(refresh_cpu,this); // Creation of an Afx thread.
}


void NodeProperties::stop_AverageCPULoad() {
	cpu = false;
}


int NodeProperties::cpu_incr(int i) {
	if (i == HISTORY-1) {
		cpu_complete = true;
		return(0);
	} else
		return(i+1);
}


int NodeProperties::cpu_decr(int i) {
	if (i == 0) {
		if (cpu_complete)
			return(HISTORY-1);
		else
			return(-1);
	} else
		return(i-1);
}


int NodeProperties::mem_average(int timeinterval) {
	int ti = timeinterval;
	if (ti > HISTORY)
		ti = HISTORY;
	if (ti == 0)
		ti = 1;
	int sum = 0;
	int pos = mem_decr(mem_new);
	if (pos == -1)
		return(0);
	for (int i=0 ; i<ti ; i++) {
		sum += mem_history[pos];
		pos = mem_decr(pos);
		if (pos == -1)
			return(sum/(i+1));
	}
	return(sum/ti);
}


int NodeProperties::cpu_average(int timeinterval) {
	int ti = timeinterval;
	if (ti > HISTORY)
		ti = HISTORY;
	int sum = 0;
	int pos = cpu_decr(cpu_new);
	if (pos == -1)
		return(0);
	for (int i=0 ; i<ti ; i++) {
		sum += cpu_history[pos];
		pos = cpu_decr(pos);
		if (pos == -1)
			return(sum/(i+1));
	}
	return(sum/ti);
}


// The return value is an integer (between 0 and 100) and represents the CPU load in percent.
// If the value can't be retreaved, -1 is returned.

int NodeProperties::_get_CPULoad() {
	int ret = CPULoad(true);  // Retrieval of the CPU load with the System object.
	if (ret < 0) {			  // If the System object can't be used,
		//std::cout << "Other !!!!\n";
		ret = CPULoad(false); // the Processor object is used.
	}
	return(ret);
} // end _get_CPULoad


// Returns an integer representing the quantity of free memory in bytes.
// If the value can't be retrieved, -1 is returned.

int NodeProperties::_get_FreeMemory() {
	MEMORYSTATUS Buffer;
	GlobalMemoryStatus(&Buffer);
	return(Buffer.dwAvailPhys);
} // end get_FreeMemory


// Constructor.

NodeProperties::NodeProperties() {
	DWORD rc;
	DWORD dwType;
	DWORD dwIndex;
	DWORD dwBufSize;
	HKEY hObject;
	HKEY hCounter;
	char szCounter[MAX_PATH];
	char Ident[DIFFFLAGLEN];
	char Title[DIFFFLAGLEN];
	char Desc[DIFFFLAGLEN];

	lpNameStrings = NULL;
	lpNamesArray = NULL;

	lpmszNameStrings = NULL;
	lpmszNamesArray = NULL;

//	HQUERY m_hQuery;
	PdhOpenQuery(NULL, 1, &m_hQuery);

	pCounter1 = 0;
//	HCOUNTER hCounter1;
	pCounter2 = 0;
//	HCOUNTER hCounter2;

    //GetLpmszNameStrings();

	CommLoad();

	rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY8, 0, KEY_READ, &hObject);
	if (rc == ERROR_SUCCESS) {
		dwIndex = 0;
		dwBufSize = MAX_PATH;
		while(RegEnumKeyEx(hObject,dwIndex++,szCounter,&dwBufSize,NULL,NULL,NULL,NULL) == ERROR_SUCCESS) {
			rc = RegOpenKeyEx(hObject, szCounter, 0, KEY_READ, &hCounter);
			if ( rc == ERROR_SUCCESS) {
				dwBufSize = DIFFFLAGLEN;
				rc = RegQueryValueEx(hCounter,"ServiceName",NULL,&dwType,(unsigned char *)Ident,&dwBufSize);
				if (rc == ERROR_SUCCESS) {
					Network_Interface card;
					card.id = std::string(Ident);
					dwBufSize = DIFFFLAGLEN;
					rc = RegQueryValueEx(hCounter,"Description",NULL,&dwType,(unsigned char *)Desc,&dwBufSize);
					if (rc == ERROR_SUCCESS) {
						card.type = Identify(std::string(Desc));
					} else
						card.type = "Undefined";
					if (card.type == std::string("Undefined")) {
						dwBufSize = DIFFFLAGLEN;
						rc = RegQueryValueEx(hCounter,"Title",NULL,&dwType,(unsigned char *)Title,&dwBufSize);
						if (rc == ERROR_SUCCESS)
							card.type = Identify(std::string(Title));
					} // end if
					int i = 0;
					int j;
					bool found = false;
					while ((i < network_segment_instances.size()) && (! found)) {
						j = (network_segment_instances[i]).find(Ident);
						if ((j >= 0) && (j < network_segment_instances[i].size()))
							found = true;
						i++;
					} // end while
					if (found == true)
						card.network_segment_instance = network_segment_instances[i-1];
					else
						card.network_segment_instance = std::string("Undefined");
					nwi.push_back(card);
				} // end if
			} // end if
			RegCloseKey(hCounter);
			dwBufSize = MAX_PATH;
		} // end while
		int count = 1;
		for (int i = 0 ; i < nwi.size() ; i++) {
			if (nwi[i].network_segment_instance != std::string("Undefined"))
				count++;
		} // end for
		if (count == network_interface_instances) {
			std::list<std::string> lst;
			for (i = 0 ; i < nwi.size() ; i++) {
				if (nwi[i].network_segment_instance != std::string("Undefined"))
					lst.push_back(nwi[i].id);
			} // end for
			if (lst.size() > 0)
				lst.sort();
			for (i = 0 ; i < nwi.size() ; i++) {
				int j = 0;
				bool fnd = false;
				while ((j < lst.size()) && (!fnd)) {
					std::list<std::string>::iterator it = lst.begin();
					for (int k = 0 ; k < j ; k++)
						it++;
					if (*it == nwi[i].id)
						fnd = true;
					j++;
				} // end while
				if (fnd)
					nwi[i].network_interface_instance = j+1;
				else
					nwi[i].network_interface_instance = -1;
			} // end for
		} else { // There is a problem to give a number to the network card
			for (i = 0 ; i < nwi.size() ; i++)
				nwi[i].network_interface_instance = -1;
		} // end else
		RegCloseKey(hObject);
	} // end if
	mem_history = new int[HISTORY];
	mem_new = 0;
	mem_complete = false;
	mem = false;
	start_AverageFreeMemory();
	cpu_history = new int[HISTORY];
	cpu_new = 0;
	cpu_complete = false;
	cpu = false;
	start_AverageCPULoad();
} // end NodeProperties


// Destructor.

NodeProperties::~NodeProperties() {
	nwi.clear();
	network_segment_instances.clear();
	free(lpNameStrings);
	free(lpNamesArray);
	free(lpmszNameStrings);
	free(lpmszNamesArray);
	stop_AverageFreeMemory();
	delete(mem_history);
	stop_AverageCPULoad();
	delete(cpu_history);
	PdhRemoveCounter(hCounter1);
	PdhRemoveCounter(hCounter2);
	PdhCloseQuery(&m_hQuery);
} // end ~NodeProperties


// The possible return values are :
//		"Windows NT"
//		"Windows 2000"
//		"Undefined"

char *NodeProperties::get_OSName() {
	DWORD rc;
	DWORD dwType;
	DWORD dwBufSize;
	HKEY hObject;
	char Type[DIFFFLAGLEN];
	OSVERSIONINFO info;
	info.dwOSVersionInfoSize = sizeof(info);
	if (GetVersionEx(&info)) {
		if (info.dwPlatformId == VER_PLATFORM_WIN32_NT) {
			rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY5, 0, KEY_READ, &hObject);
			if (rc == ERROR_SUCCESS) {
				rc = RegQueryValueEx(hObject,"ProductName",NULL,&dwType,(unsigned char *)Type,&dwBufSize);
				if (rc == ERROR_SUCCESS) {
					if (strcmp(Type,"Microsoft Windows 2000") == 0)
						return(strdup("Windows 2000"));
				} // end if
			} // end if
			return(strdup("Windows NT"));
		} // end if
	} // end if
	return(strdup("Undefined"));
} // end get_OSName


// The return value is a string which represents the version of the OS, the build number and the service pack installed.
// Examples of returned value :
//		""
//		"Undefined"

char *NodeProperties::get_OSVersion() {
	OSVERSIONINFO info;
	info.dwOSVersionInfoSize = sizeof(info);
	if (GetVersionEx(&info)) {
		std::string version = int2string(info.dwMajorVersion);
		version = version + ".";
		version = version + int2string(info.dwMinorVersion);
		version = version + " (Build: ";
		version = version + int2string(info.dwBuildNumber);
		std::string details = info.szCSDVersion;
		if ((details != std::string("")) && (details != std::string("x"))) {
			version = version + " ";
			version = version + details;
		} // end if
		version = version + ")";
		return(strdup(version.c_str()));
	} // end if
	return(strdup("Undefined"));
} // end get_OSVersion


// The return value is a string which represents the main directory of the operating system.

char *NodeProperties::get_OSDirectory() {
	DWORD rc;
	DWORD dwBufSize;
	DWORD dwType;
	HKEY hObject;
	char directory[DIFFFLAGLEN];
	bool found = false;

	rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY5, 0, KEY_READ, &hObject);
	if (rc == ERROR_SUCCESS) {
		dwBufSize = DIFFFLAGLEN;
		rc = RegQueryValueEx(hObject,"SystemRoot",NULL,&dwType,(unsigned char *)directory,&dwBufSize);
		if (rc == ERROR_SUCCESS)
			found = true;
	} // end if
	RegCloseKey(hObject);
	if (found)
		return(strdup(directory));
	else
		return(strdup("Undefined"));
} // end get_OSDirectory


// The return value is a string which represents the vendor of the operating system.

char *NodeProperties::get_OSVendor() {
	return(strdup("Microsoft"));
} // end get_OSVendor


// The return value is an integer. If the value is -1, it signifies the number of processors
// can't be retrieved.

int NodeProperties::get_ProcessorsNumber() {
	DWORD rc;
	DWORD dwIndex2;
	DWORD dwBufSize;
	HKEY hObject;
	HKEY hCounter;
	char szCounter[MAX_PATH];
	int number = 0;

	rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY1, 0, KEY_READ, &hObject);
	if (rc == ERROR_SUCCESS) {
		dwIndex2 = 0;
		dwBufSize = MAX_PATH;
		while(RegEnumKeyEx(hObject,dwIndex2++,szCounter,&dwBufSize,NULL,NULL,NULL,NULL) == ERROR_SUCCESS) {
			rc = RegOpenKeyEx(hObject, szCounter, 0, KEY_READ, &hCounter);
			if ( rc == ERROR_SUCCESS)
				number++;
			RegCloseKey(hCounter);
			dwBufSize = MAX_PATH;
		} // end while
		RegCloseKey(hObject);
	} else
		return(-1);
	return(number);
} // end get_ProcessorsNumber


// Returns a string representing the list of the processors. The processor names are separated
// by a '|' character. If the types of the processors can't be retrieved, the string "Undefined"
// is returned. Examples of returned value :
//		"Celeron|Celeron|"
//		"Pentium|Undefined|"
//		"Pentium III|"
//		"Undefined|"
//		"Undefined"

char *NodeProperties::get_ProcessorsType() {
	DWORD rc;
	DWORD dwIndex;
	DWORD dwType;
	DWORD dwBufSize;
	HKEY hObject;
	HKEY hCounter;
	char szCounter[MAX_PATH];
	char Ident[DIFFFLAGLEN];
	std::string rt = "";
	std::string proc_type("Undefined");

	rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY1, 0, KEY_READ, &hObject);
	if (rc == ERROR_SUCCESS) {
		dwIndex = 0;
		dwBufSize = MAX_PATH;
		while(RegEnumKeyEx(hObject,dwIndex++,szCounter,&dwBufSize,NULL,NULL,NULL,NULL) == ERROR_SUCCESS) {
			rc = RegOpenKeyEx(hObject, szCounter, 0, KEY_READ, &hCounter);
			if ( rc == ERROR_SUCCESS) {
				dwBufSize = DIFFFLAGLEN;
				rc = RegQueryValueEx(hCounter,"Identifier",NULL,&dwType,(unsigned char *)Ident,&dwBufSize);
				if (rc == ERROR_SUCCESS)
					proc_type = Ident;
				else
					proc_type = "Undefined"; // The type of this processor can't be determined
			} else
				proc_type = "Undefined"; // The type of this processor can't be determined
			rt = rt + proc_type;
			rt = rt + std::string("|");
			RegCloseKey(hCounter);
			dwBufSize = MAX_PATH;
		} // end while
		RegCloseKey(hObject);
	} else
		return(strdup("Undefined")); // No access to the informations on the processor(s)
	return(strdup(rt.c_str()));
} // end get_ProcessorsType


// Returns a string representing the list of the processors vendors. The vendor names are separated
// by a '|' character. If the vendor of the processors can't be retrieved, the string "Undefined"
// is returned. Examples of returned value :
//		"GenuineIntel|GenuineIntel|"
//		"GenuineIntel|Undefined|"
//		"GenuineIntel|"
//		"Undefined|"
//		"Undefined"

char *NodeProperties::get_ProcessorsVendor() {
	DWORD rc;
	DWORD dwIndex;
	DWORD dwType;
	DWORD dwBufSize;
	HKEY hObject;
	HKEY hCounter;
	char szCounter[MAX_PATH];
	char Ident[DIFFFLAGLEN];
	std::string rt = "";
	std::string proc_type("Undefined");

	rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY1, 0, KEY_READ, &hObject);
	if (rc == ERROR_SUCCESS) {
		dwIndex = 0;
		dwBufSize = MAX_PATH;
		while(RegEnumKeyEx(hObject,dwIndex++,szCounter,&dwBufSize,NULL,NULL,NULL,NULL) == ERROR_SUCCESS) {
			rc = RegOpenKeyEx(hObject, szCounter, 0, KEY_READ, &hCounter);
			if ( rc == ERROR_SUCCESS) {
				// do processing on open counter key using hCounter
				dwBufSize = DIFFFLAGLEN;
				rc = RegQueryValueEx(hCounter,"VendorIdentifier",NULL,&dwType,(unsigned char *)Ident,&dwBufSize);
				if (rc == ERROR_SUCCESS)
					proc_type = Ident;
				else
					proc_type = "Undefined";
			} else
				proc_type = "Undefined";
			rt = rt + proc_type;
			rt = rt + std::string("|");
			RegCloseKey(hCounter);
			dwBufSize = MAX_PATH;
		} // end while
		RegCloseKey(hObject);
	} else
		return(strdup("Undefined"));
	return(strdup(rt.c_str()));
} // end get_ProcessorsVendor


// Returns a string representing the list of the processors vendors. The vendor names are separated
// by a '|' character. If the vendor of the processors can't be retrieved, the string "Undefined"
// is returned. Examples of returned value :
//		"GenuineIntel|GenuineIntel|"
//		"GenuineIntel|Undefined|"
//		"GenuineIntel|"
//		"Undefined|"
//		"Undefined"

char *NodeProperties::get_ProcessorsCompatibilityClass() {
	std::string type = get_ProcessorsType();
	char * store = (char *)malloc(256*sizeof(char));
	std::string store2, store3;
	std::ifstream input("compatibility.txt", std::ios::in);
	if (!input) {
		if (store != NULL)
			free(store);
		return(strdup("Undefined"));
	}
	do {
		input.getline(store,256,'\n');
		store2 = std::string(store);
		std::vector<std::string> strvec = cut(store2,':');
		if (strvec.size() == 2) {
			store2 = strvec[0];
			store3 = strvec[1];
			std::vector<std::string> strvec2 = cut(store3,',');
			int siz = strvec2.size();
			for (int i=0 ; i<siz ; i++) {
				int pos = type.find(strvec2[i]);
				if ((pos >= 0)&&(pos < type.size())) {
					input.close();
					if (store != NULL)
						free(store);
					return(strdup(store2.c_str()));
				}
			}
		}
	} while (! input.eof()); // end do while
	input.close();
	if (store != NULL)
		free(store);
	return(strdup("Undefined"));
} // end get_ProcessorsCompatibilityClass


// The return value is an integer (between 0 and 100) and represents the CPU load in percent.
// If the value can't be retreaved, -1 is returned.

int NodeProperties::get_CPULoad() {
	int pos = cpu_decr(cpu_new);
	if (pos < 0)
		return(0);
	return(cpu_history[pos]);
} // end get_CPULoad


// Returns an integer representing the average cpu load (in percent).
// If the value can't be retrieved, -1 is returned.
int NodeProperties::get_AverageCPULoad(int timeinterval) {
	return(cpu_average(timeinterval/1000));
}


// The return value is an integer. If the number of processes can't be retrieved, -1 is returned.

int NodeProperties::get_NumberOfProcesses() {
	int number;
	if (processes_number(&number))
		return(number);
	return(-1);
} // end get_NumberOfProcesses


// Returns an integer representing the quantity of installed memory in bytes.
// If the value can't be retrieved, -1 is returned.

int NodeProperties::get_InstalledMemory() {
	MEMORYSTATUS Buffer;
	GlobalMemoryStatus(&Buffer);
	return(Buffer.dwTotalPhys);
} // end get_InstalledMemory


// Returns an integer representing the quantity of free memory in bytes.
// If the value can't be retrieved, -1 is returned.

int NodeProperties::get_FreeMemory() {
	int pos = mem_decr(mem_new);
	if (pos < 0)
		return(0);
	return(mem_history[pos]);
} // end get_FreeMemory


// Returns an integer representing the average free memory (in bytes).
// If the value can't be retrieved, -1 is returned.
int NodeProperties::get_AverageFreeMemory(int timeinterval) {
	return(mem_average(timeinterval/1000));
}


// Returns a string which is the name of the computer.
// If the value can't be retrieved, "Undefined" is returned.

char *NodeProperties::get_ComputerName() {
	DWORD rc;
	DWORD dwBufSize;
	DWORD dwType;
	HKEY hObject;
	char host[DIFFFLAGLEN];
	bool found = false;

	rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY9, 0, KEY_READ, &hObject);
	if (rc == ERROR_SUCCESS) {
		dwBufSize = DIFFFLAGLEN;
		rc = RegQueryValueEx(hObject,"HostName",NULL,&dwType,(unsigned char *)host,&dwBufSize);
		if (rc == ERROR_SUCCESS)
			found = true;
	} // end if
	RegCloseKey(hObject);

	if (!found) {
		rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY2, 0, KEY_READ, &hObject);
		if (rc == ERROR_SUCCESS) {
			dwBufSize = DIFFFLAGLEN;
			rc = RegQueryValueEx(hObject,"ComputerName",NULL,&dwType,(unsigned char *)host,&dwBufSize);
			if (rc == ERROR_SUCCESS)
				found = true;
		} // end if
		RegCloseKey(hObject);
	}
	if (found)
		return(strdup(host));
	else
		return(strdup("Undefined"));
} // end get_ComputerName


// Returns a string representing the list of the addresses. The addresses are separated by
// a '|' character. If the addresses can't be retrieved, the string "Undefined" is returned.
// Examples of returned value :
//		"194.94.243.114|194.94.92.111|"
//		"Undefined|194.94.243.114|"
//		"194.94.243.114|"
//		"Undefined|"
//		"Undefined"

char *NodeProperties::get_IPAddresses() {
	std::string rt = "";
	DWORD rc;
	DWORD dwType;
	DWORD dwBufSize;
	HKEY hObject;
	HKEY hCounter;
	HKEY hCounter2;
	char Address[DIFFFLAGLEN];

	rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY4, 0, KEY_READ, &hObject);
	if (rc == ERROR_SUCCESS) {
		for	(int i = 0 ; i < nwi.size() ; i++) {
			rc = RegOpenKeyEx(hObject, strdup((nwi[i].id).c_str()), 0, KEY_READ, &hCounter);
			if (rc == ERROR_SUCCESS) {
				rc = RegOpenKeyEx(hCounter, "Parameters\\Tcpip", 0, KEY_READ, &hCounter2);
				if (rc == ERROR_SUCCESS) {
					dwBufSize = DIFFFLAGLEN;
					rc = RegQueryValueEx(hCounter2,"IPAddress",NULL,&dwType,(unsigned char *)Address,&dwBufSize);
					if ( rc == ERROR_SUCCESS) {
						rt = rt + Address;
						rt = rt + "|";
					} else
						rt = rt + "Undefined|";
				} else
					rt = rt + "Undefined|";
			} else
				rt = rt + "Undefined|";
		} // end for
	} // end if
	if (rt == std::string(""))
		rt = "Undefined";
	return(strdup(rt.c_str()));
} // end get_IPAddresses


// Returns a string representing the list of the different network interfaces. The addresses are
// separated by a '|' character. If the addresses can't be retrieved, the string "Undefined" is
// returned. Examples of returned values :
//		"ethernet|token-ring|"
//		"Undefined|ethernet|"
//		"token-ring|"
//		"Undefined|"
//		"Undefined"

char *NodeProperties::get_NetworkType() {
	std::string ret = "";
	for (int i=0 ; i < nwi.size() ; i++) {
		ret = ret + nwi[i].type;
		ret = ret + "|";
	} // end for
	if (ret == std::string(""))
		ret = "Undefined";
	return(strdup(ret.c_str()));
} // end get_NetworkType


// Returns a string representing the list of the maximum bandwidthes (bits/second) for the different network interfaces.
// The valued are separated by a '|' character. If the bandwidth for a paticular network interface can't
// be retreaved, the value "-1" is associated to this network interface. If all the maximum bandwidths can't
// be retrieved, the string "Undefined" is returned. Examples of returned values :
//		"10000000|100000000|"
//		"-1|10000000|"
//		"100000000|"
//		"-1|"
//		"Undefined"

char *NodeProperties::get_MaxBandwidth() {
	std::string rt = "";
	HQUERY m_hQuery2;

	if (PdhOpenQuery(NULL, 3, &m_hQuery2) != ERROR_SUCCESS)
		return(strdup("Undefined"));
	for (int k = 0 ; k < nwi.size() ; k++) {
		int inst = nwi[k].network_interface_instance;
		if (inst != -1) {
			std::string counter = "\\Network Interface(";
			counter = counter + int2string(inst);
			counter = counter + ")\\Current Bandwidth";
//			HQUERY m_hQuery;
			if (PdhOpenQuery(NULL, 3, &m_hQuery2) != ERROR_SUCCESS)
				rt = rt + "-1|";
			else {
				int pCounter = 0;
				HCOUNTER hCounter;
//				PDH_STATUS ret;

				if (PdhAddCounter(m_hQuery2,strdup(counter.c_str()),(DWORD)&pCounter,&hCounter) != ERROR_SUCCESS)
					rt = rt + "-1|";
				else {
				    PPDH_RAW_COUNTER ppdhRawCounter1 = new PDH_RAW_COUNTER;
					PPDH_RAW_COUNTER ppdhRawCounter2 = new PDH_RAW_COUNTER;

					if (PdhCollectQueryData(m_hQuery2) != ERROR_SUCCESS)
						rt = rt + "-1|";
					else {
						PDH_FMT_COUNTERVALUE pdhFormattedValue;
						PdhGetFormattedCounterValue(hCounter,PDH_FMT_LONG,NULL,&pdhFormattedValue);
						rt = rt + int2string(pdhFormattedValue.longValue);
						rt = rt + "|";
					} // end else
				} // end else
				PdhRemoveCounter(hCounter);
			} // end else
		} else
			rt = rt + "-1|";
	} // end for
	PdhCloseQuery(&m_hQuery2);
	if (rt == std::string(""))
		rt = "Undefined";
	return(strdup(rt.c_str()));
} // end get_MaxBandwidth


// Returns a string representing the list of the communication loads (percent) for the different network interfaces.
// The values are separated by a '|' character. If the communication load for a paticular network interface can't
// be retreaved, the value "-1" is associated to this network interface. If all the communication loads can't
// be retrieved, the string "Undefined" is returned. Examples of returned values :
//		"12|2|"
//		"-1|11|"
//		"9|"
//		"-1|"
//		"Undefined"

char *NodeProperties::get_CommunicationLoad() {
	std::string rt = "";

	HQUERY m_hQuery3;
	if (PdhOpenQuery(NULL, 2, &m_hQuery3) != ERROR_SUCCESS)
		return(strdup("Undefined"));

	int pCounter = 0;
	HCOUNTER hCounter;
//	PDH_STATUS ret;

	for (int i = 0 ; i < nwi.size() ; i++) {
		std::string counter = "\\Network Segment(";
		std::string dev = nwi[i].network_segment_instance;
		if (dev == std::string("Undefined"))
			rt = rt + "-1|";
		else {
			counter = counter + dev;
			counter = counter + ")\\% Network utilization";
			if (PdhAddCounter(m_hQuery3,strdup(counter.c_str()),(DWORD)&pCounter,&hCounter) != ERROR_SUCCESS)
				rt = rt + "-1|";
			else {
			    PPDH_RAW_COUNTER ppdhRawCounter1 = new PDH_RAW_COUNTER;
				PPDH_RAW_COUNTER ppdhRawCounter2 = new PDH_RAW_COUNTER;

				if (PdhCollectQueryData(m_hQuery3) != ERROR_SUCCESS)
					rt = rt + "-1|";
				else {
					if (PdhGetRawCounterValue(hCounter,NULL,ppdhRawCounter1) != ERROR_SUCCESS)
						rt = rt + "-1|";
					else {
						Sleep(100);
						if (PdhCollectQueryData(m_hQuery3) != ERROR_SUCCESS)
							rt = rt + "-1|";
						else {
							if (PdhGetRawCounterValue(hCounter,NULL,ppdhRawCounter2) != ERROR_SUCCESS)
								rt = rt + "-1|";
							else {
								PDH_FMT_COUNTERVALUE pdhFormattedValue;

								if (PdhCalculateCounterFromRawValue(hCounter,PDH_FMT_LONG,ppdhRawCounter2,ppdhRawCounter1,&pdhFormattedValue) != ERROR_SUCCESS)
									rt = rt + "-1|";
								else {
									rt = rt + int2string(pdhFormattedValue.longValue);
									rt = rt + "|";
								} // end else
							} // end else
						} // end else
					} // end else
				} // end else
			} // end else
			PdhRemoveCounter(hCounter);
		} // end else
	} // end for

	PdhCloseQuery(&m_hQuery3);

	if (rt == std::string(""))
		return(strdup("Undefined"));
	return(strdup(rt.c_str()));
} // end get_CommunicationLoad


// Returns a string representing the list of the different network protocols. The protocols are
// separated by a '|' character. If the protocols can't be retrieved, the string "Undefined" is
// returned. Examples of returned values :
//		"IPX/SPX|TCP/IP|"
//		"Undefined|TCP/IP|"
//		"TCP-IP|"
//		"Undefined|"
//		"Undefined"

char *NodeProperties::get_Protocols() {
	std::vector<std::string> rep;
	std::string rt = "";
	DWORD rc;
	DWORD dwIndex;
	DWORD dwType;
	DWORD dwBufSize;
	HKEY hObject;
	HKEY hCounter;
	HKEY hCounter2;
	char szCounter[MAX_PATH];
	char Type[DIFFFLAGLEN];
	char Protocol[DIFFFLAGLEN];
	bool nt = false;

	if (strcmp(get_OSName(),"Windows NT") == 0)
		nt = true;

	if (nt)
		rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY3, 0, KEY_READ, &hObject);
	else
		rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PERFENUMKEY4, 0, KEY_READ, &hObject);
	if (rc == ERROR_SUCCESS) {
		dwIndex = 0;
		dwBufSize = MAX_PATH;
		while(RegEnumKeyEx(hObject,dwIndex++,szCounter,&dwBufSize,NULL,NULL,NULL,NULL) == ERROR_SUCCESS) {
			rc = RegOpenKeyEx(hObject, szCounter, 0, KEY_READ, &hCounter);
			if (rc == ERROR_SUCCESS) {
				if (nt) { // Windows NT
					rc = RegOpenKeyEx(hCounter, "CurrentVersion", 0, KEY_READ, &hCounter2);
					if (rc == ERROR_SUCCESS) {
						dwBufSize = DIFFFLAGLEN;
						rc = RegQueryValueEx(hCounter2,"SoftwareType",NULL,&dwType,(unsigned char *)Type,&dwBufSize);
						if ((rc == ERROR_SUCCESS) && (strcmp(Type,"transport") == 0)) {
							dwBufSize = DIFFFLAGLEN;
							rc = RegQueryValueEx(hCounter2,"Title",NULL,&dwType,(unsigned char *)Protocol,&dwBufSize);
							if (rc == ERROR_SUCCESS) {
								int i = 0;
								bool found = false;
								while ((!found) && (i < rep.size())) {
									if (rep[i] == std::string(Protocol))
										found = true;
									i++;
								} // end while
								if (!found) {
									rep.push_back(std::string(Protocol));
									rt = rt + std::string(Protocol);
									rt = rt + std::string("|");
								} // end if
							} // end if
						} // end if
					} // end if
				} else { // Windows 2000
					rc = RegOpenKeyEx(hCounter, "ServiceProvider", 0, KEY_READ, &hCounter2);
					if (rc == ERROR_SUCCESS) {
						dwBufSize = DIFFFLAGLEN;
						rc = RegQueryValueEx(hCounter2,"Name",NULL,&dwType,(unsigned char *)Protocol,&dwBufSize);
						if (rc == ERROR_SUCCESS) {
							int i = 0;
							bool found = false;
							while ((!found) && (i < rep.size())) {
								if (rep[i] == std::string(Protocol))
									found = true;
								i++;
							} // end while
							if (!found) {
								rep.push_back(std::string(Protocol));
								rt = rt + std::string(Protocol);
								rt = rt + std::string("|");
							} // end if
						} // end if
					} // end if
				} // end else
			} // end if
			dwBufSize = MAX_PATH;
		} // end while
		RegCloseKey(hCounter);
		RegCloseKey(hCounter2);
	} // end if
	RegCloseKey(hObject);
	if (rep.size() == 0)
		rt = std::string("Undefined");
	rep.clear();
	return(strdup(rt.c_str()));
} // end get_Protocols


// This property has not been implemented and returns "Undefined".

char *NodeProperties::get_InstalledOrbs() {
	return(strdup("Undefined"));
} // end get_InstalledOrbs


UINT refresh_mem(LPVOID pParam) {
	NodeProperties *np = (NodeProperties *)pParam;
	while(np->mem) {
		int value = np->_get_FreeMemory();
		np->mem_history[np->mem_new] = value;
		np->mem_new = np->mem_incr(np->mem_new);
		Sleep(1000);
	}
	return(0);
}


UINT refresh_cpu(LPVOID pParam) {
	NodeProperties *np = (NodeProperties *)pParam;
	while(np->cpu) {
		int value = np->_get_CPULoad();
		np->cpu_history[np->cpu_new] = value;
		np->cpu_new = np->cpu_incr(np->cpu_new);
		Sleep(800);
	}
	return(0);
}

//Added by avf: This method takes a counter name in english and translate it to
//the localized name, so that PDH would find it in the registry
int NodeProperties::get_localized_name(const char* english_name,char* local_name) {
 	PDH_STATUS pdhStatus = ERROR_SUCCESS;
	LPTSTR szNameBuffer = (LPTSTR)malloc(256*sizeof(CHAR));
    char* currentName = (char *)malloc(256*sizeof(char));
	DWORD pcchNameBufferSize = sizeof(szNameBuffer);
	DWORD dwIndex = NULL;
	int rtn;
 
    for(int i=0; i < lpmszNamesArraySize ; i++){
        //std::cout << "current index : " << i << std::endl;
        // this does not work!!
        //TODO: Fix this !
         currentName = lpmszNamesArray[i];
        
        if(currentName != NULL) {
    	    if (strcmp(english_name,currentName) == 0) {
    	        dwIndex = i;
    	        break;
            }
        }
    }
    
    if(dwIndex == NULL)
        return -1;
 
    pdhStatus = PdhLookupPerfNameByIndex("localhost", dwIndex, szNameBuffer,&pcchNameBufferSize);
    if(pdhStatus == ERROR_SUCCESS){
        std::cout << "Found localized name for " << english_name << ": " << szNameBuffer << std::endl;
        strncpy(local_name,szNameBuffer,pcchNameBufferSize);
        rtn = 0;
    }else{
        if(pdhStatus == PDH_MORE_DATA)
            std::cerr << "ERROR: PDH_MORE_DATA" << std::endl;
        if(pdhStatus == PDH_INVALID_ARGUMENT)
            std::cerr << "ERROR: PDH_INVALID_ARGUMENT"  << std::endl;
        rtn = -1;
    }
    if(szNameBuffer != NULL)
        free(szNameBuffer);
  
    //if(currentName != NULL)
    //    free(currentName);
    //              
    return rtn;

}
