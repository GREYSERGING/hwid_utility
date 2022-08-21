#include <stdio.h>
#include <windows.h>

char* get_hwid(char hwid[]) {
	HW_PROFILE_INFOA hwProfileInfo;
	GetCurrentHwProfileA(&hwProfileInfo);
	strcpy(hwid, hwProfileInfo.szHwProfileGuid);
	return hwid;
}

void usage() {
	printf("HWID Usage:\r\n\t-h | show the current window\n\t-g | get the hwid of the computer\r\n\t-b [to_file] | make a backup of hwid\r\n\t-s [new_hwid] | install a new hwid\r\n\t\tConsists of a range of: a-f and 0-9\r\n\t\tExample: \"{01234567-89ab-cdef-0123-456789abcdef}\"");
}

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		usage();
		return -1;
	}
	char hwid[38];
	get_hwid(hwid);
	for (int a = 0; a < argc; a++) {
		if (strcmp(argv[a], "-h") == 0) {
			usage();
			break;
		}
		if (strcmp(argv[a], "-g") == 0) {
			printf("%s", hwid);
			break;
		}
		if (strcmp(argv[a], "-b") == 0) {
			char to_file[255];
			strcpy(to_file, argv[a + 1]);
			
			HANDLE file = CreateFileA(to_file, FILE_WRITE_DATA, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			if (file == INVALID_HANDLE_VALUE) {
				printf("[-] ERROR: Could not open the file");
				return -1;
			}
			DWORD write;
			int write_file = WriteFile(file, hwid, 38, &write, 0);
			CloseHandle(file);
			if (write_file == 1 && write == 38)
				printf("[+] SUCCESS: Backup was made successfully");
			else
				printf("[-] ERROR: Failed to create backup");
			break;
		}
		//HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\IDConfigDB\Hardware Profiles\0001
		if (strcmp(argv[a], "-s") == 0) {
			char new_hwid[38];
			strcpy(new_hwid, (argv[a + 1] != 0) ? argv[a + 1] : "");
			if (strlen(new_hwid) != 38 || new_hwid == 0) {
				printf("[-] ERROR: Invalid HWID");
				break;
			}
			HKEY hkey;
			if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Control\\IDConfigDB\\Hardware Profiles\\0001", 0, KEY_SET_VALUE, &hkey) != ERROR_SUCCESS) {
				RegCloseKey(hkey);
				printf("[-] ERROR: The registry key could not be opened");
				break;
			}
			if (RegSetValueExA(hkey, "HwProfileGuid", 0, REG_SZ, (LPBYTE)new_hwid, 38) != ERROR_SUCCESS) {
				RegCloseKey(hkey);
				printf("[-] ERROR: Failed to set value");
				break;
			}
			RegCloseKey(hkey);
			printf("[+] SUCCESS: HWID changed");
		}
	}
	return 0;
}