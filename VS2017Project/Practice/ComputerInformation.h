#pragma once
#include <iostream> 
#include <string>
#include <string.h>
#include <winsock2.h> // include must before window.h
#include <iphlpapi.h>  //它提供了一些非常实用的获取网络信息(网卡、tcp/ip等)的函数
#include <windows.h>  
using namespace std;

//动态链接库都是使用静态加载方式。若是使用动态加载方式，则需要使用LoadLibrary等函数方式加载具体的函数。
#pragma comment(lib, "iphlpapi.lib")
#pragma warning(disable: 4996) // avoid GetVersionEx to be warned



//获取网卡信息，可能会有很多网卡 //
void getNetworkInfo()
{
	// PIP_ADAPTER_INFO struct contains network information
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	unsigned long adapter_size = sizeof(IP_ADAPTER_INFO);
	int ret = GetAdaptersInfo(pIpAdapterInfo, &adapter_size);

	if (ret == ERROR_BUFFER_OVERFLOW)
	{
		// overflow, use the output size to recreate the handler
		delete pIpAdapterInfo;
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[adapter_size];
		ret = GetAdaptersInfo(pIpAdapterInfo, &adapter_size);
	}

	if (ret == ERROR_SUCCESS)
	{
		int card_index = 0;

		// may have many cards, it saved in linklist
		while (pIpAdapterInfo)
		{
			std::cout << "---- " << "NetworkCard " << ++card_index << " ----" << std::endl;

			std::cout << "Network Card Name: " << pIpAdapterInfo->AdapterName << std::endl;
			std::cout << "Network Card Description: " << pIpAdapterInfo->Description << std::endl;

			// get IP, one card may have many IPs
			PIP_ADDR_STRING pIpAddr = &(pIpAdapterInfo->IpAddressList);
			while (pIpAddr)
			{
				char local_ip[128] = { 0 };
				strcpy(local_ip, pIpAddr->IpAddress.String);
				std::cout << "Local IP: " << local_ip << std::endl;

				pIpAddr = pIpAddr->Next;
			}

			char local_mac[128] = { 0 };
			int char_index = 0;
			for (int i = 0; i < pIpAdapterInfo->AddressLength; i++)
			{
				char temp_str[10] = { 0 };
				sprintf(temp_str, "%02X-", pIpAdapterInfo->Address[i]); // X for uppercase, x for lowercase
				strcpy(local_mac + char_index, temp_str);
				char_index += 3;
			}
			local_mac[17] = '\0'; // remove tail '-'

			std::cout << "Local Mac: " << local_mac << std::endl;

			
			//break;
			 //iterate next
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}

	if (pIpAdapterInfo)
		delete pIpAdapterInfo;
	cout << "-----------------------------------------------" << endl;
}

void getSysInfo()
{
	SYSTEM_INFO  sysInfo;    //该结构体包含了当前计算机的信息：计算机的体系结构、中央处理器的类型、系统中中央处理器的数量、页面的大小以及其他信息。
	OSVERSIONINFOEX osvi;
	GetSystemInfo(&sysInfo);
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	if (GetVersionEx((LPOSVERSIONINFOW)&osvi))
	{
		printf("操作系统版本 :      %u.%u.%u\n", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
		printf("Service Pack :      %u.%u\n", osvi.wServicePackMajor, osvi.wServicePackMinor);
	}
	printf("处理器架构 :        %u\n", sysInfo.wProcessorArchitecture);
	printf("处理器级别 :        %u\n", sysInfo.wProcessorLevel);
	printf("处理器版本 :        %u\n", sysInfo.wProcessorRevision);
	printf("处理器掩码 :        %u\n", sysInfo.dwActiveProcessorMask);
	printf("处理器数量 :        %u\n", sysInfo.dwNumberOfProcessors);
	printf("处理器类型 :        %u\n", sysInfo.dwProcessorType);
	printf("页面大小 :          %u\n", sysInfo.dwPageSize);
	printf("应用程序最小地址 :  %u\n", sysInfo.lpMinimumApplicationAddress);
	printf("应用程序最大地址 :  %u\n", sysInfo.lpMaximumApplicationAddress);
	printf("虚拟内存分配粒度 :  %u\n", sysInfo.dwAllocationGranularity);
	printf("OemId :             %u\n", sysInfo.dwOemId);
	printf("wReserved :         %u\n", sysInfo.wReserved);
	cout << "-----------------------------------------------" << endl;
}

//获取在用的网络地址
void getIP()
{
	WSADATA WSAData;                                //WSADATA结构被用来储存调用AfxSocketInit全局函数返回的Windows Sockets初始化信息。
	if (WSAStartup(MAKEWORD(2, 0), &WSAData))        // 初始化Windows sockets API
	{
		printf("WSAStartup failed %s\n", WSAGetLastError());
		exit(-1);        //异常退出 
	}

	char hostName[256];
	if (gethostname(hostName, sizeof(hostName)))        //获取主机名
	{
		printf("Error: %u\n", WSAGetLastError());
		exit(-1);        //异常退出 
	}
	printf("主机名：             %s\n", hostName);

	hostent *host = gethostbyname(hostName);    // 根据主机名获取主机信息. 
	if (host == NULL)
	{
		printf("Error: %u\n", WSAGetLastError());
		exit(-1);
	}

	cout << "主机地址类型:        " << host->h_addrtype << endl
		<< "地址清单:            " << host->h_addr_list << endl
		<< "别名列表:            " << host->h_aliases << endl
		<< "地址长度:            " << host->h_length << endl
		<< "正式的主机名:        " << host->h_name << endl;

	for (int i = 0; host->h_addr_list[i] != 0; i++)
	{
		cout << "该主机IP" << i + 1 << ":           " << inet_ntoa(*(struct in_addr*)*host->h_addr_list) << endl;
	}
	cout << "-----------------------------------------------" << endl;
	WSACleanup();
}

//获取cpu的频率等信息
#ifdef _WIN64

// method 2: usde winapi, works for x86 and x64
#include <intrin.h>
void getCpuInfo()
{
	int cpuInfo[4] = { -1 };
	char cpu_manufacture[32] = { 0 };
	char cpu_type[32] = { 0 };
	char cpu_freq[32] = { 0 };

	__cpuid(cpuInfo, 0x80000002);
	memcpy(cpu_manufacture, cpuInfo, sizeof(cpuInfo));
	
	__cpuid(cpuInfo, 0x80000003);
	memcpy(cpu_type, cpuInfo, sizeof(cpuInfo));
	__cpuid(cpuInfo, 0x80000004);
	memcpy(cpu_freq, cpuInfo, sizeof(cpuInfo));
	std::cout << "CPU 制造商: " << cpu_manufacture << std::endl;
	std::cout << "CPU 类型: " << cpu_type << std::endl;
	std::cout << "CPU 主频: " << cpu_freq << std::endl;
	cout << "-----------------------------------------------" << endl;
}

#else

// mothed 1: this kind asm embedded in code only works in x86 build
// save 4 register variables
DWORD deax;
DWORD debx;
DWORD decx;
DWORD dedx;

// init cpu in assembly language
void initCpu(DWORD veax)
{
	__asm
	{
		mov eax, veax
		cpuid
		mov deax, eax
		mov debx, ebx
		mov decx, ecx
		mov dedx, edx
	}
}

long getCpuFreq()
{
	int start, over;
	_asm
	{
		RDTSC
		mov start, eax
	}
	Sleep(50);
	_asm
	{
		RDTSC
		mov over, eax
	}
	return (over - start) / 50000;
}

std::string getManufactureID()
{
	char manuID[25];
	memset(manuID, 0, sizeof(manuID));

	initCpu(0);
	memcpy(manuID + 0, &debx, 4); // copy to array
	memcpy(manuID + 4, &dedx, 4);
	memcpy(manuID + 8, &decx, 4);

	return manuID;
}

std::string getCpuType()
{
	const DWORD id = 0x80000002; // start 0x80000002 end to 0x80000004
	char cpuType[49];
	memset(cpuType, 0, sizeof(cpuType));

	for (DWORD t = 0; t < 3; t++)
	{
		initCpu(id + t);

		memcpy(cpuType + 16 * t + 0, &deax, 4);
		memcpy(cpuType + 16 * t + 4, &debx, 4);
		memcpy(cpuType + 16 * t + 8, &decx, 4);
		memcpy(cpuType + 16 * t + 12, &dedx, 4);
	}

	return cpuType;
}

void getCpuInfo()
{
	std::cout << "CPU 制造商: " << getManufactureID() << std::endl;
	std::cout << "CPU 类型: " << getCpuType() << std::endl;
	std::cout << "CPU 主频: " << getCpuFreq() << "MHz" << std::endl;
	cout << "-----------------------------------------------" << endl;
}

#endif
static const int MaxBuffer = 256;
#define  GB  1073741824  
#define  MB  1048576  
#define  KB  1024  
#define  DOUBLE_KB 1024.0  
//内存
void getMemoryInfo()
{
	std::string memory_info;
	MEMORYSTATUSEX statusex;
	statusex.dwLength = sizeof(statusex);
	if (GlobalMemoryStatusEx(&statusex))
	{
		unsigned long long total = 0, remain_total = 0, avl = 0, remain_avl = 0;
		double decimal_total = 0, decimal_avl = 0;
		remain_total = statusex.ullTotalPhys % GB;
		total = statusex.ullTotalPhys / GB;
		avl = statusex.ullAvailPhys / GB;
		remain_avl = statusex.ullAvailPhys % GB;
		if (remain_total > 0)
			decimal_total = (remain_total / MB) / DOUBLE_KB;
		if (remain_avl > 0)
			decimal_avl = (remain_avl / MB) / DOUBLE_KB;

		decimal_total += (double)total;
		decimal_avl += (double)avl;
		char  buffer[MaxBuffer];
		sprintf_s(buffer, MaxBuffer, "totalMemory %.2f GB (%.2f GB available)", decimal_total, decimal_avl);
		memory_info.append(buffer);
	}
	std::cout << memory_info << std::endl;
	cout << "-----------------------------------------------" << endl;
}

//硬盘
std::string execCmd(const char *cmd)
{
	char buffer[128] = { 0 };
	std::string result;
	FILE *pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("_popen() failed!");
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	_pclose(pipe);

	return result;
}
void getHardDiskInfo()
{
	std::string hd_seiral = execCmd("wmic path win32_physicalmedia get SerialNumber");
	std::cout << "HardDisk Serial Number: " << hd_seiral << std::endl;
	cout << "-----------------------------------------------" << endl;
}
void getHardDiskInfo2()
{
	int rtn =system("wmic path win32_physicalmedia get SerialNumber");
	cout << "-----------------------------------------------" << endl;
}




