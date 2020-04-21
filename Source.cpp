#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <TCHAR.H>
#include <tlhelp32.h>

using namespace std;

void print_menu() {
	system("cls");
	printf("What do you want to do?\n");
	printf("1. Display list of processes\n");
	printf("2. Display type of processor and amount of kernels\n");
	printf("3. Display system color\n");
	printf("4. \n");
	printf("5. Exit\n");
	printf(">");
}

VOID PrintModuleList(HANDLE CONST hStdOut, DWORD CONST dwProcessId) {
	MODULEENTRY32 meModuleEntry;
	TCHAR szBuff[1024];
	DWORD dwTemp;
	HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE, dwProcessId);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return;
	}

	meModuleEntry.dwSize = sizeof(MODULEENTRY32);
	Module32First(hSnapshot, &meModuleEntry);
	do {
		wsprintf(szBuff, L"  ba: %08X, bs: %08X, %s\r\n",
			meModuleEntry.modBaseAddr, meModuleEntry.modBaseSize,
			meModuleEntry.szModule);
		WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
	} while (Module32Next(hSnapshot, &meModuleEntry));

	CloseHandle(hSnapshot);
}

VOID PrintProcessList(HANDLE CONST hStdOut) {
	PROCESSENTRY32 peProcessEntry;
	TCHAR szBuff[1024];
	DWORD dwTemp;
	HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return;
	}

	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &peProcessEntry);
	do {
		wsprintf(szBuff, L"=== %08X %s ===\r\n",
			peProcessEntry.th32ProcessID, peProcessEntry.szExeFile);
		WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
		PrintModuleList(hStdOut, peProcessEntry.th32ProcessID);
	} while (Process32Next(hSnapshot, &peProcessEntry));

	CloseHandle(hSnapshot);
}

void get_process_list() {
	HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PrintProcessList(hStdOut);
	/*Sleep(100);
	ExitProcess(0);*/
}

void get_processor_type() {
	SYSTEM_INFO sys_Info;

	GetSystemInfo(&sys_Info);

	cout << "Your process type : " << sys_Info.dwProcessorType << endl;

	cout << "Amount of kernel : " << sys_Info.dwNumberOfProcessors << endl;
}

void get_system_color() {
	cout << endl << "System Color (RGB)" << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		DWORD color = GetSysColor(COLOR_HIGHLIGHT);
		cout << "COLOR_HIGHLIGHT - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_HIGHLIGHTTEXT);
		cout << "COLOR_HIGHLIGHTTEXT - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_HOTLIGHT);
		cout << "COLOR_HOTLIGHT - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_HOTLIGHT);
		cout << "COLOR_HOTLIGHT - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_INACTIVEBORDER);
		cout << "COLOR_INACTIVEBORDER - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_INACTIVECAPTION);
		cout << "COLOR_INACTIVECAPTION - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_INACTIVECAPTIONTEXT);
		cout << "COLOR_INACTIVECAPTIONTEXT - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_INFOBK);
		cout << "COLOR_INFOBK - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_INFOTEXT);
		cout << "COLOR_INFOTEXT - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_MENU);
		cout << "COLOR_MENU - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_MENUTEXT);
		cout << "COLOR_MENUTEXT - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_SCROLLBAR);
		cout << "COLOR_SCROLLBAR - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_WINDOW);
		cout << "COLOR_WINDOW - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_WINDOWFRAME);
		cout << "COLOR_WINDOWFRAME - " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
		color = GetSysColor(COLOR_WINDOWTEXT);
		cout << "COLOR_WINDOWTEXT- " << (int)GetRValue(color) << "x" << (int)GetGValue(color) << "x" << (int)GetBValue(color) << endl;
}

void menu() {
	int variant;

	do {
		print_menu();

		scanf_s("%d", &variant);

		switch (variant) {
		case 1:
			get_process_list();
			break;

		case 2:
			get_processor_type();
			break;

		case 3:
			get_system_color();
			break;

		case 4:

			break;
		}

		if (variant != 5)
			system("pause");
	} while (variant != 5);

}


int main() {

	menu();

	system("pause");

	return 0;
}

