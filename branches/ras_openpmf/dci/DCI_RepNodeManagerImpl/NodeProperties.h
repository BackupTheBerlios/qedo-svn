//**************************************************************
//
// T-Nova
// Deutsche Telekom Innovationsgesellschaft mbH
// Technologiezentrum Darmstadt
//
// Xavier Testa
//
// NodeProperties.h
//
// Copyright (c) T-Nova Deutsche Telekom
// Innovationsgesellschaft mbH + 2001
//
// "This software is copyrighted. It may only be used for the 
// purposes stipulated in the license agreement, subject to 
// copyright regulations, in particular to §§ 69 a ff. of the 
// German Copyright Act. Any usage not within the scope of 
// Copyright Act without T-Nova's consent is inadmissible and 
// liable to prosecution.
//
// T-Nova has installed the copyright notice stipulated herein
// in the computer program. In the event of a user being
// authorized to duplicate the computer program, this
// copyright notice always is to be included. The copyright
// notice must neither be changed nor destroyed.
//
// All rights reserved. 
// This program is globally copyrighted."
//**************************************************************

#ifndef NODEPROPERTIES
#define NODEPROPERTIES

#ifdef WIN32
#include <pdh.h>
#endif 

#include <vector>

#define TOTALBYTES    8192
#define BYTEINCREMENT 1024

#define CNTR_CPU1 "\\System\\% Total Processor Time"
//Modified by avf
//#define CNTR_CPU2 "\\Processor(_Total)\\%ProcessorTime (%)"
#define CPU_MAIN "Processor"
#define CPU_TIME "% Processor Time"
//#define CNTR_CPU2 "\\Processor(_Total)\\ProcessorTime (%)"
#define CNTR_CPU2 "\\Prozessor(_Total)\\Prozessorzeit (%)"

#define DIFFFLAGLEN 100

#define PERFENUMKEY1 "HARDWARE\\DESCRIPTION\\System\\CentralProcessor"
#define PERFENUMKEY2 "SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName"
#define PERFENUMKEY3 "SOFTWARE\\Microsoft"
#define PERFENUMKEY4 "SYSTEM\\CurrentControlSet\\Services"
#define PERFENUMKEY5 "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"
#define PERFENUMKEY6 "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib"
#define PERFENUMKEY7 "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\009"
#define PERFENUMKEY8 "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkCards"
#define PERFENUMKEY9 "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"
#define PERFENUMKEY10 "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\007"

#define HISTORY 50

//using namespace std;


struct Network_Interface {
	std::string id;							// string to identify the network card
	std::string type;						// ethernet, token-ring...
	std::string network_segment_instance;	// name of the corresponding instance for the network segment object (PDH)
	int network_interface_instance;		// number of the corresponding instance for the network interface object (PDH)
};


class NodeProperties {

private:
	HQUERY m_hQuery;
	int pCounter1;
	HCOUNTER hCounter1;
	int pCounter2;
	HCOUNTER hCounter2;

	bool mem_complete;
	bool cpu_complete;
	bool shutdown_set;

	LPSTR lpNameStrings;
	LPSTR *lpNamesArray;
	
	DWORD lpmszCounters;
	LPSTR lpmszNameStrings;
	LPSTR *lpmszNamesArray;

	// List of the different network interfaces of the computer
	std::vector<Network_Interface> nwi;

	// List of the instances for the network segment object.
	std::vector<std::string> network_segment_instances;

	// Number of instances for the network interface object.
	int network_interface_instances;

	DWORD dwBuffer2;
	
	// Size of the array in which the english names for the counters are stored
	DWORD lpmszNamesArraySize;

	// Returns the string representation of the integer parameter.
	std::string int2string(int);

	// The number of processes running on the computer is stored at the place indicated by the parameter.
	bool processes_number(int *);

	// Returns the CPU Load. The PDH is used to retrieve this value.
	// The method has to be called with the parameter true but if the return value is not correct,
	// parameter false has to be used.
	int CPULoad(bool);

	// This procedure fills the network_segment_instances vector and sets the network_interface_instances integer.
	// This procedure is called only once (in the constructor).
	void CommLoad();

	// Analyzes the string parameter and returns the corresponding network type.
	std::string Identify(std::string);

	// Cut the string parameter line.
	std::vector<std::string> cut(std::string,char);

	// To navigate among the different objects, instances and counters.
	PPERF_OBJECT_TYPE FirstObject(PPERF_DATA_BLOCK);
	PPERF_OBJECT_TYPE NextObject(PPERF_OBJECT_TYPE);
	PPERF_INSTANCE_DEFINITION FirstInstance(PPERF_OBJECT_TYPE);
	PPERF_INSTANCE_DEFINITION NextInstance(PPERF_INSTANCE_DEFINITION);
	PPERF_COUNTER_DEFINITION FirstCounter(PPERF_OBJECT_TYPE);
	PPERF_COUNTER_DEFINITION NextCounter(PPERF_COUNTER_DEFINITION);

	void GetNameStrings();
	void GetLpmszNameStrings();

	void start_AverageFreeMemory();

	void stop_AverageFreeMemory();

	void start_AverageCPULoad();

	void stop_AverageCPULoad();

	int mem_average(int);

	int cpu_average(int);
	
	int get_localized_name(const char* english_name, char* local_name);
	
	std::string translate_name(const char* originalName);

public:
	int *mem_history;
	int *cpu_history;
	int mem_new;
	int cpu_new;
	bool mem;
	bool cpu;

	int mem_incr(int);
	int mem_decr(int);

	int cpu_incr(int);
	int cpu_decr(int);

	int _get_CPULoad();
	int _get_FreeMemory();

	NodeProperties();                         // Constructor
	~NodeProperties();                        // Destructor

	char *get_OSName();                       // Name of the operating system
	char *get_OSVersion();                    // Version of the operating system
	char *get_OSDirectory();                  // Main directory
	char *get_OSVendor();                     // Vendor of the operating system
	int get_ProcessorsNumber();               // Number of processors
	char *get_ProcessorsType();               // Type of the processors
	char *get_ProcessorsVendor();             // Vendor of the processors
	char *get_ProcessorsCompatibilityClass(); // Compatibility class of all the processors
	int get_CPULoad();                        // Total load of the CPU (in percent)
	int get_AverageCPULoad(int);              // Average load of the CPU (in percent)
	int get_NumberOfProcesses();              // Number of running processes
	int get_InstalledMemory();                // Quantity of installed memory (in bytes)
	int get_FreeMemory();                     // Quantity of free memory (in bytes)
	int get_AverageFreeMemory(int);           // Average load of memory (in percent)
	char *get_ComputerName();                 // Name of the computer
	char *get_IPAddresses();                  // List of the IP addresses of the computer
	char *get_NetworkType();                  // List of the types of the network interfaces
	char *get_MaxBandwidth();                 // List of the maximum bandwidths corresponding to the network interfaces (in bit/s)
	char *get_CommunicationLoad();            // List of the load values corresponding to the network interfaces (in percent)
	char *get_Protocols();                    // List of the installed protocols
	char *get_InstalledOrbs();                // List of the installed orbs
	

};

UINT refresh_mem(LPVOID pParam);

UINT refresh_cpu(LPVOID pParam);

#endif