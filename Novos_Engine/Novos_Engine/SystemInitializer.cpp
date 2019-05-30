#include "stdafx.h"
#include "SystemInitializer.h"
#include "EngineSystem.h"


SystemInitializer::SystemInitializer()
{

}


bool SystemInitializer::Run()
{
	
		GCA = new GameCodeApp();
		if (GCA->InitInstance(proj) == false)
		{
			return false;
		}
		GCA->CheckStorage(checkSpace);
		GCA->CheckMemory(checkPhysMem, checkVirtualMem);
		GCA->ReadCPUSpeed();
		GCA->CheckArchitecture();
		return true;
}
