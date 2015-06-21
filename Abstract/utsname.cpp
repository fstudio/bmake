/*
Copyright 2011 Martin T. Sandsmark <sandsmark@samfundet.no>
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include "utsname.h"

typedef struct MachineNameTag{
	int machineId;
	const char *name;
}MachineName;

static MachineName machineList[] = {
	{ PROCESSOR_ARCHITECTURE_INTEL, "x86" },
	{ PROCESSOR_ARCHITECTURE_MIPS , "mips" },
	{ PROCESSOR_ARCHITECTURE_ALPHA,"alpha" },
	{ PROCESSOR_ARCHITECTURE_PPC, "ppc"},
	{ PROCESSOR_ARCHITECTURE_SHX ,"shx"},
	{ PROCESSOR_ARCHITECTURE_ARM, "arm"},
	{ PROCESSOR_ARCHITECTURE_IA64, "ia64"},
	{ PROCESSOR_ARCHITECTURE_ALPHA64, "alpha64" },
	{ PROCESSOR_ARCHITECTURE_MSIL ,"MSIL"},
	{ PROCESSOR_ARCHITECTURE_AMD64,"x86_64" },
	{ PROCESSOR_ARCHITECTURE_IA32_ON_WIN64   ,"ia32onwin64" },
	{ PROCESSOR_ARCHITECTURE_NEUTRAL  ,"neutral"   }
};

extern "C" int uname(struct utsname *name) {
    struct utsname *ret;
    OSVERSIONINFO versionInfo;
    SYSTEM_INFO sysInfo;
    
    // Get Windows version info
    ZeroMemory(&versionInfo, sizeof(OSVERSIONINFO));
    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // wtf
    GetVersionEx(&versionInfo);
    
    // Get hardware info
    ZeroMemory(&sysInfo, sizeof(SYSTEM_INFO));
    GetSystemInfo(&sysInfo);

    strcpy(name->sysname, "Windows");
    itoa(versionInfo.dwBuildNumber, name->release, 10);
    sprintf(name->version, "%i.%i", versionInfo.dwMajorVersion, versionInfo.dwMinorVersion);

    if (gethostname(name->nodename, UTSNAME_LENGTH) != 0) {
        if (WSAGetLastError() == WSANOTINITIALISED) { // WinSock not initialized
            WSADATA WSAData;
            WSAStartup(MAKEWORD(1, 0), &WSAData);
            gethostname(name->nodename, UTSNAME_LENGTH);
            WSACleanup();
        } else
            return WSAGetLastError();
    }
	for (auto &i : machineList)
	{
		if (i.machineId == sysInfo.wProcessorArchitecture)
		{
			strcpy(name->machine, i.name);
			return 0;
		}
	}
	strcpy(name->machine, "unknown");
    return 0;
}
