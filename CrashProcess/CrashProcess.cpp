#include <Windows.h>
#include <ProcessThreadsApi.h>
#include <iostream>

using namespace std;

int wmain(const int argc, const WCHAR* argv[]) {
	if (argc == 2) {
		const DWORD pid = static_cast<DWORD>(_wtoi(argv[1]));
		const HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

		if (process != NULL) {
			// Create a thread in the target process with a NULL start address. The new
			// thread is created and immediately AVs.
			// Incidentally, it is much easier to use CreateRemoteThread to cause a crash
			// than it is to actually serve its intended purpose. A sign of possible bad API design.
			const HANDLE thread = CreateRemoteThread(process, NULL, 0, NULL, NULL, 0, NULL);

			if (thread == NULL) {
				wcerr << L"Unable to inject thread because " << GetLastError() << endl;
			}
		}
		else {
			wcerr << L"Unable to open pid " << pid << L" because " << GetLastError() << endl;
		}
	}
	else {
		wcerr << L"CrashProcess [pid]" << endl;
	}
}

