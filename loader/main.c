#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>


void log_debug(const char *fmt, ...)
{
	char buffer[0xFF];
	va_list args;
	va_start(args, fmt);
	vsprintf_s(buffer, 0xFF, fmt, args);
	va_end(args);

	char logmessage[0xFF];
	char logtime[0xFF];
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(logtime, sizeof(logtime), "[%H:%M:%S]", &timeinfo);
	sprintf_s(logmessage, 0xFF, "%s %s\n", logtime, buffer);

	printf("%s", logmessage);
}

int main(void)
{
	// get a path of service.exe to pass later
	char service_path[MAX_PATH];
	if (!GetFullPathNameA("service.exe", MAX_PATH, service_path, NULL)) {
		log_debug("could not find service.exe (%x)", GetLastError());
		Sleep(3000);
		return 1;
	}

	// could be anything
	LPCSTR service_name = "5af64758";

	// get a handle to the service manager
	SC_HANDLE sc_manager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!sc_manager) {
		log_debug("could not open sc manager (%x)", GetLastError());
		log_debug("run the loader as administrator!");
		Sleep(3000);
		return 1;
	}

	// create our service, or look for it if it already exists
	SC_HANDLE service;
	if (!(service = CreateServiceA(sc_manager, service_name, service_name, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, service_path, NULL, NULL, NULL, NULL, NULL))
		&& !(service = OpenServiceA(sc_manager, service_name, SERVICE_ALL_ACCESS))) {
		log_debug("could not create service (%x)", GetLastError());
		Sleep(3000);
		return 1;
	}

	log_debug("registered service");

	// move our dll to a known location so the service can inject it
	char dll_path[MAX_PATH];
	GetFullPathNameA("vac.dll", MAX_PATH, dll_path, NULL);
	CopyFileA(dll_path, "c:\\rape.dll", false);

	// the path could be passed as an argument here but we don't have proper service init functions
	StartServiceA(service, 0, NULL);

	log_debug("service started");

	// remove the service once we've injected
	if (!DeleteService(service))
		log_debug("failed to delete service (%x)", GetLastError());

	log_debug("loader finished");
	Sleep(3000);
	return 0;
}