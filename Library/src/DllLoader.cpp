#include "DllLoader.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace ZGF
{
	DllLoader::DllLoader(const char* libfilename)
	{
		if(libfilename == NULL)
			throw "DllLoader::DllLoader() encountered NULL library filename";

		filename = libfilename;
		lptr = NULL;
		error = false;
	}

	DllLoader::~DllLoader()
	{
		Close();
	}

#ifdef WIN32

	bool DllLoader::Load()
	{
		lptr = LoadLibrary(filename.c_str());

		if(lptr != NULL)
		{
			return true;
		}
		else
		{
			error = true;
			return false;
		}
	}

	void* DllLoader::GetAddressForSymbol(const char* symbol)
	{
		void* address = NULL;

		address = GetProcAddress(reinterpret_cast< HMODULE >(lptr), symbol);

		if(address == NULL)
			error = true;

		return address;
	}

	void DllLoader::Close()
	{

		if(lptr != NULL)
		{
			int err = 0;

			err = FreeLibrary(reinterpret_cast< HMODULE >(lptr));

			if(err != 0)
				error = true;
		}
	}


#else

	bool DllLoader::Load()
	{
		lptr = dlopen(filename.c_str(), RTLD_NOW);

		if(lptr != NULL)
		{
			return true;
		}
		else
		{
			error = true;
			return false;
		}
	}

	void* DllLoader::GetAddressForSymbol(const char* symbol)
	{
		void* address = NULL;

		address = dlsym(lptr, symbol);

		if(address == NULL)
			error = true;

		return address;
	}

	void DllLoader::Close()
	{

		if(lptr != NULL)
		{
			int err = 0;

			err = dlclose(lptr);

			if(err != 0)
				error = true;
		}
	}


#endif
}
