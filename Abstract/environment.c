/**/
#include <stdint.h>
#include <typedefs.h>
#include <Windows.h>

ssize_t readlink(const char *path, char *buf, size_t bufsiz)
{
	return 0;
}

/// if overwrite=0 and getenv TRUE return 0
int setenv(const char *name, const char * value, int overwrite)
{
	//SetEnvironmentVariableA
	DWORD dRet = 0;
	if (!(name&&value))
		return -1;
	if (overwrite == 0){
		if (GetEnvironmentVariableA(name, NULL, 0) == 0){
			if (ERROR_ENVVAR_NOT_FOUND == GetLastError()){
				return 0;
			}
			return -1;
		}
	}
	if(SetEnvironmentVariableA(name, value))
		return 0;
	return -1;
}

int unsetenv(const char *name)
{
	if (!name)
		return -1;
	SetEnvironmentVariableA(name, NULL);///When SetEnvironmentVariableA second value is NULL,delete it
	return 0;
}