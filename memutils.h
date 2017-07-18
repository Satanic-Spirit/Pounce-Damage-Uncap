/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * =============================================================================
 * MemoryUtils
 * Copyright (C) 2004-2011 AlliedModders LLC., 2011 ProdigySim
 * All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, the authors give you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 */

#ifndef _INCLUDE_SOURCEMOD_MEMORYUTILS_H_
#define _INCLUDE_SOURCEMOD_MEMORYUTILS_H_

#include <stdio.h>
#include <stdint.h>

#include "sourcehook.h"
#include "sh_memory.h"

#if SH_SYS == SH_SYS_LINUX || SH_SYS == SH_SYS_APPLE
#include <sh_vector.h>
#include "sm_symtable.h"
using SourceHook::CVector;
#endif

#if SH_SYS == SH_SYS_APPLE
#include <CoreServices/CoreServices.h>
#endif

struct DynLibInfo
{
	void *baseAddress;
	size_t memorySize;
};

#if SH_SYS == SH_SYS_LINUX || SH_SYS == SH_SYS_APPLE
struct LibSymbolTable
{
	SymbolTable table;
	uintptr_t lib_base;
	uint32_t last_pos;
};
#endif

class MemoryUtils
{
public:
	MemoryUtils();
	~MemoryUtils();
	void *FindLibPattern(const void *libPtr, const char *pattern, size_t len);
	void *FindPattern(const void *start, const void *end, const char *pattern, size_t len);
	void *ResolveSymbol(void *handle, const char *symbol);
    // Sets protection on the memory
    bool ProtectMemory(void *pAddr, int nLength, int nProt);
    // Allows the memory to be written to
    bool SetMemPatchable(void *pAddr, int nSize);

public:
	bool GetLibraryInfo(const void *libPtr, DynLibInfo &lib);
#if SH_SYS == SH_SYS_LINUX || SH_SYS == SH_SYS_APPLE
private:
	CVector<LibSymbolTable *> m_SymTables;
#if SH_SYS == SH_SYS_APPLE
	struct dyld_all_image_infos *m_ImageList;
	SInt32 m_OSXMajor;
	SInt32 m_OSXMinor;
#endif
#endif
};

extern MemoryUtils g_MemUtils;

#endif // _INCLUDE_SOURCEMOD_MEMORYUTILS_H_
