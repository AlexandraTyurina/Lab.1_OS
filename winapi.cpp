#include "winapi.h"

void DisksList()
{
	std::cout << " Used GetLogicalDrives() : \n" ;
	int n = 0;
	char letter;
	DWORD dr = GetLogicalDrives(); // ���������� �����-������� ����� � ������� ��������� ��� ��������� �����

	for (int i = 0; i < 26; i++)  // ��������� �� �����
	{
		n = ((dr >> i) & 0x1); // ���������� �������� �������� ����
		if (n == 1) 
		{
			letter = char(65 + i);  // �������� ������ �����
			std::cout << " " << letter << std::endl;
		}
	}
	/*
	*GetLogicalDriveStrings(nBufferLength,lpBuffer) - ���������� ����� �� ���������� � ��������� �� �������� �������� ��������� � ������ lpBuffer
	*nBufferLength - ������������ ������ ������ � TCHAR, �� ������� ��������� lpBuffer
	*lpBuffer - ����� ������, ������� �������� ������������������ ������������� ����� �� ����� �� ���������� + ���.������� ������. ������ ������ � ��� ��� ����������.*/
	std::cout << "\n Used GetLogicalDriveStrings() : \n";  //
	TCHAR szDrives[MAX_PATH + 1];
	GetLogicalDriveStrings(MAX_PATH, szDrives);
	TCHAR* pletter = szDrives;
		while (*pletter)
		{
			_tprintf(_T(" %s \n"), pletter);  // ��� �������� ���� TCHAR

			while (*++pletter);
			pletter++;
		}
	std::cout << std::endl;
}
void InfSpace()
{
	//GetDriveType() ���������� ���� ������ (removable, fixed, CD-ROM, RAM disk, ��� network drive) �� ����������.

	char drive_Name[MAX_PATH];
	char SystemName[MAX_PATH];
	DWORD serialNumber;
	DWORD maxFileNameLength;
	DWORD SystemFlag;

	int d;

	d = GetDriveType(L"C:\\");
	if (d == DRIVE_UNKNOWN) std::cout << "C:\\" << " IS UNKNOWN" << std::endl;
	if (d == DRIVE_NO_ROOT_DIR) std::cout << "C:\\" << " IS DRIVE NO ROOT DIR" << std::endl;
	if (d == DRIVE_REMOVABLE) std::cout << "C:\\" << " IS REMOVABLE" << std::endl;
	if (d == DRIVE_FIXED) std::cout << "C:\\" <<  " IS FIXED" << std::endl;
	if (d == DRIVE_REMOTE) std::cout << "C:\\" << " IS REMOTE" << std::endl;
	if (d == DRIVE_CDROM) std::cout << "C:\\" << " IS CDROM" << std::endl;
	if (d == DRIVE_RAMDISK) std::cout << "C:\\" << " IS RAMDISK" << std::endl;



		//GetVolumeInformationA - ���������� ���������� � �������� ������� � ������(�����������).
		if (GetVolumeInformationA ("C:\\", drive_Name, sizeof(drive_Name), &serialNumber, &maxFileNameLength, &SystemFlag, SystemName, sizeof(SystemName)))
		{
			std::cout << " ��� ����� : " << drive_Name << std::endl;
			std::cout << " �������� ����� : " << serialNumber << std::endl;
			std::cout << " ��� �������� ������� : " << SystemName << std::endl;
			std::cout << " ��������� ����� : " << SystemFlag << std::endl;
			//SystemFlag - ����������, ������� �������� ������, ��������� � ��������� �������� ��������.�������� ����� ���������� �������.
			if (SystemFlag & FILE_CASE_PRESERVED_NAMES)
				std::cout << " FILE_CASE_PRESERVED_NAMES" << std::endl;

			if (SystemFlag & FILE_CASE_SENSITIVE_SEARCH)
				std::cout << " FILE_CASE_SENSITIVE_SEARCH" << std::endl;

			if (SystemFlag & FILE_DAX_VOLUME)
				std::cout << " FILE_DAX_VOLUME" << std::endl;

			if (SystemFlag & FILE_FILE_COMPRESSION)
				std::cout << " FILE_FILE_COMPRESSION" << std::endl;
			else if (SystemFlag & FILE_VOLUME_IS_COMPRESSED)
				std::cout << " FILE_VOLUME_IS_COMPRESSED" << std::endl;

			if (SystemFlag & FILE_NAMED_STREAMS)
				std::cout << " FILE_NAMED_STREAMS" << std::endl;

			if (SystemFlag & FILE_PERSISTENT_ACLS)
				std::cout << " FILE_PERSISTENT_ACLS" << std::endl;

			if (SystemFlag & FILE_READ_ONLY_VOLUME)
				std::cout << " FILE_READ_ONLY_VOLUME" << std::endl;
			std::cout << std:: endl;
		}
		else 
		{
			std::cout << "������ � ������ GetVolumeInformation!" << std::endl;
		}
		// ����� �������� � ��������, ����� ���� � �������, ����� ��������� ���������, ����� ����� ���������
		DWORD sectorsPerCluster;
		DWORD bytesPerSector;
		DWORD numberOfFreeClusters;
		DWORD totalNumberOfClusters;
		if (GetDiskFreeSpace(L"C:\\", &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters, &totalNumberOfClusters))
		{
			std::cout << "�������� � �������� : " << sectorsPerCluster << std::endl;
			std::cout << "������ � ������� : " << bytesPerSector << std::endl;
			std::cout << "��������� ��������� : " << numberOfFreeClusters << std::endl;
			std::cout << "���������� ��������� : " << totalNumberOfClusters << std::endl;
			double frspace = (double)sectorsPerCluster * (double)bytesPerSector * (double)numberOfFreeClusters / 1024 / 1024;
			std::cout << "���������� ���������� ����� � ���������� : " << frspace << '\n';
		}
		else 
		{
			std::cout << "������ � ������ GetDiskFreeSpace" << std::endl;
		}
		std::cout << std::endl;
}

void CreateAndDelete()
{
	std::cout << "0 � ��������" << std::endl;
	std::cout << "1 � ��������" << std::endl;
	int choice;
	std::cin >> choice;
	// ���� � ������� ���� ��� ������������� ���� LPCWSTR. 
	std::cout << "������� ���� : ";
	std::wstring path;
	std::wcin >> path;
	LPCWSTR pcwstr;
	pcwstr = path.c_str();

	if (choice == 0)
	{
		if (CreateDirectory(pcwstr, NULL)) std::cout << " ���������� �������" << std::endl; //"C:\\Test"
		else std::cout << " ������ �������� ����������" << std::endl;
	}

	if (choice == 1)
	{
		if (RemoveDirectory(pcwstr)) std::cout << " ���������� �������" << std::endl;
		else std::cout << " ������ �������� ����������" << std::endl;

	}
}

void Create_File()
{
	HANDLE hndl;
	std::cout << "������� ���� : ";

	LPCWSTR pcwstr;
	std::wstring path;
	std::wcin >> path;

	pcwstr = path.c_str();
	
	/*GENERIC_WRITE - ����������� ��� ������, 
	0 -��������� �� ������������, 
	NULL - ������ �� ���������, 
	CREATE_ALWAYS - ������������ ������������, 
	FILE_ATTRIBUTE_NORMAL -������� ����, 
	NULL -��������� ������� ���*/
	hndl = CreateFile(pcwstr, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hndl != INVALID_HANDLE_VALUE) 
	{
		std::wcout << " ���� " << path << " ������ " << std::endl;
	}
	else 
	{
		std::cout << "������ � �������� �����";
	}
	//CloseHandle ��������� ���������� ��������� �������.
	CloseHandle(hndl);
	std::cout << std::endl;
}

void CopyAndMove()
{
	std::cout << "0 � ����������" << std::endl;
	std::cout << "1 � �����������" << std::endl;
	int ch;
	std::cin >> ch;

	LPCWSTR path_before, path_after;
	std::wstring path1, path2;

	std::cout << "������� ���� ������ ���������� / ����������: ";
	std::wcin >> path1;
	std::cout << "������� ���� ���� ���������� / ����������: ";
	std::wcin >> path2;
	path_before = path1.c_str();
	path_after = path2.c_str();

	if (ch == 0)
	{
		if (CopyFile(path_before, path_after, false)) 
		{
			std::cout << "���� ������� ���������� " << std::endl;
		}
		else 
		{
			std::cout << "������ ����������� ����� " << GetLastError() << std::endl;
		}
	}
	if (ch == 1)
	{
		if (MoveFile(path_before, path_after))
		{
			std::cout << " ���� ������� ��������� " << std::endl;
		}
		else
		{
			std::cout << " ������ ����������� ����� " << GetLastError() << std::endl;
		}
	}
	std::cout << std::endl;
}

void Getattrib()
{
	LPCWSTR pcwstr;
	std::wstring path;

	std::cout << "0 � �������� ���������� �� ����� �����/�������� (GetFileAttributes)" << std::endl;
	std::cout << "1 - �������� ���������� �� ����������� �����/�������� (GetFileInformationByHandle+GetFileTime) " << std::endl;
	int ch;
	std::cin >> ch;

	std::cout << " ������� ���� : ";
	std::wcin >> path;
	pcwstr = path.c_str();

	if (ch == 0)
	{
		//GetFileAttributes ���������� �������� ����� ��� �����. ��� ������ ���������� 0, ���� ���� ��� ����� �� �������, �� ������������ -1.

		DWORD attribs = GetFileAttributes(pcwstr);

		if (attribs != INVALID_FILE_ATTRIBUTES)
		{
			switch (attribs)
			{
			case FILE_ATTRIBUTE_ARCHIVE:
				std::cout << " ���� ����� ���� �������������" << std::endl;
				break;
			case FILE_ATTRIBUTE_COMPRESSED:
				std::cout << " ���� ��� ���������� ����" << std::endl;
				break;
			case FILE_ATTRIBUTE_DEVICE:
				std::cout << " ���������������; �� ������������" << std::endl;
				break;
			case FILE_ATTRIBUTE_DIRECTORY:
				std::cout << " ���������� �������������� ����������" << std::endl;
				break;
			case FILE_ATTRIBUTE_ENCRYPTED:
				std::cout << " ���� ��� ���������� ����������" << std::endl;
				break;
			case FILE_ATTRIBUTE_HIDDEN:
				std::cout << " ���� ��� ���������� �������" << std::endl;
				break;
			case FILE_ATTRIBUTE_NORMAL:
				std::cout << " ���� ��� ����������, ������� �� ����� ������ ������������� ���������" << std::endl;
				break;
			case FILE_ATTRIBUTE_NOT_CONTENT_INDEXED:
				std::cout << " ���� �� ������������� ���������� ������� ��������������" << std::endl;
				break;
			case FILE_ATTRIBUTE_OFFLINE:
				std::cout << " ���� ��� ���������� ������������� ������ ��� ������" << std::endl;
				break;
			case FILE_ATTRIBUTE_REPARSE_POINT:
				std::cout << " ���� ��� ����������, ������� ����� ���������� � reparse ������" << std::endl;
				break;
			case FILE_ATTRIBUTE_SPARSE_FILE:
				std::cout << " ����, ������� �������� ����������� ������" << std::endl;
				break;
			case FILE_ATTRIBUTE_SYSTEM:
				std::cout << " ���� ��� ����������, ������� ������������ ������� ���������� ��� ����� ����, ��� ���������� ���������" << std::endl;
				break;
			case FILE_ATTRIBUTE_TEMPORARY:
				std::cout << " ���� ����� ����������� ��� ���������� ��������" << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "������ ��� ������ ���������" << GetLastError << std::endl;
		}
	}
	if (ch == 1)
	{
		HANDLE hfile = CreateFile(pcwstr, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hfile == NULL) 
		{
			std::cout << " ������ � ��������� ����������� " << std::endl;
		}
		else
		{
			BY_HANDLE_FILE_INFORMATION info;
			/*GetFileInformationByHandle ��������� ���������� � ����� ��� ���������� �����.
			���� ���������� �� ������ ���� ������������ ������ (������������ �����). 
			������� GetFileInformationByHandle �� �������� � ������������� �������*/
			GetFileInformationByHandle(hfile, &info);
			/* dwFileAttributes - �������� �����
			dwVolumeSerialNumber - ���������� ����� ����, ������� �������� ����
			nFileIndexHigh - ������� ����� ������� �����
			nFileSizeLow - ������� ����� ������� �����
			nFileIndexHigh - ������� ����� ����������� �������������� ����� � ������
			nFileIndexLow - ������� ����� ����������� �������������� ����� � ������
			nNumberOfLinks - ����� ������ � ���� ������. ��� �������� ������� NTFS, ��� ����� ���� ������ ��� 1.
			*/
			std::cout << "���������� GetFileInformationByHandle:" << std::endl;
			std::cout << "File attributes " << info.dwFileAttributes << std::endl;
			std::cout << "Volume serial number " << info.dwVolumeSerialNumber << std::endl;
			std::cout << "File index high " << info.nFileIndexHigh << std::endl;
			std::cout << "File index low " << info.nFileIndexLow << std::endl;
			std::cout << "File size high " << info.nFileSizeHigh << std::endl;
			std::cout << "File size low " << info.nFileSizeLow << std::endl;
			std::cout << "Number of links " << info.nNumberOfLinks << std::endl;

			SYSTEMTIME CreationTime, LastAccessTime, LastWriteTime;
			//FileTimeToSystemTime ����������� �������� ����� � ������ ���������� �������
			FileTimeToSystemTime(&info.ftCreationTime, &CreationTime);
			FileTimeToSystemTime(&info.ftLastAccessTime, &LastAccessTime);
			FileTimeToSystemTime(&info.ftLastWriteTime, &LastWriteTime);

			std::cout << " ����� �� GetFileInformationByHandle " << std::endl;
			std::cout <<  " ����� ��������:  "  << CreationTime.wDay << "." << CreationTime.wMonth << "." << CreationTime.wYear << " " << CreationTime.wHour << " : " << CreationTime.wMinute << " : " << CreationTime.wSecond << std::endl;
			std::cout << " ����� ���������� �������:  " << LastAccessTime.wDay << "." << LastAccessTime.wMonth << "." << LastAccessTime.wYear << " " << LastAccessTime.wHour << " : " << LastAccessTime.wMinute << " : " << LastAccessTime.wSecond << std::endl;
			std::cout << " ����� ��������� ������ � ����:  " << LastWriteTime.wDay << "." << LastWriteTime.wMonth << "." << LastWriteTime.wYear << " " << LastWriteTime.wHour << " : " << LastWriteTime.wMinute << " : " << LastWriteTime.wSecond << std::endl;
			std::cout << std::endl;

			std::cout << " ����� �� GetFileTime " << std::endl;

			FILETIME creationTime, lastAccessTime, lastWriteTime;

			GetFileTime(hfile, &creationTime, &lastAccessTime, &lastWriteTime);

			SYSTEMTIME screationTime, slastAccessTime, slastWriteTime;

			FileTimeToSystemTime(&creationTime, &screationTime);
			FileTimeToSystemTime(&lastAccessTime, &slastAccessTime);
			FileTimeToSystemTime(&lastWriteTime, &slastWriteTime);

			std::cout << " ����� ��������:  " << screationTime.wDay << "." << screationTime.wMonth << "." << screationTime.wYear << " " << screationTime.wHour << " : " << screationTime.wMinute << " : " << screationTime.wSecond << std::endl;
			std::cout << " ����� ���������� �������:  " << slastAccessTime.wDay << "." << slastAccessTime.wMonth << "." << slastAccessTime.wYear << " " << slastAccessTime.wHour << " : " << slastAccessTime.wMinute << " : " << slastAccessTime.wSecond << std::endl;
			std::cout << " ����� ��������� ������ � ����:  " << slastWriteTime.wDay << "." << slastWriteTime.wMonth << "." << slastWriteTime.wYear << " " << slastWriteTime.wHour << " : " << slastWriteTime.wMinute << " : " << slastWriteTime.wSecond << std::endl;
			CloseHandle(hfile);

		}
	} 


	std::cout << std::endl;
}

void Setattrib()
{
	LPCWSTR pcwstr;
	std::wstring path;

	std::cout << "0 � ���������� �������� �����" << std::endl;
	std::cout << "1 - ���������� ����� " << std::endl;

	int ch;
	std::cin >> ch;

	std::cout << " ������� ���� : ";
	std::wcin >> path;
	pcwstr = path.c_str();

	if (ch == 0)
	{
		DWORD attribs;
		std::cout << " ������� �������� : ";
		std::cin >> attribs;
		if (SetFileAttributes(pcwstr, attribs))
		{
			std::cout << " �������� ������� �����������" << std::endl;
		}
		else
		{
			std::cout << " ������ � ������������ ���������" << std::endl;
		}

	}
	if (ch==1)
	{
		HANDLE hndl = CreateFile(pcwstr, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		FILETIME file;
		SYSTEMTIME sys;

		if (hndl == NULL) {
			std::cout << "������ � ��������� ����������� " << std::endl;
		}
		else {
			GetSystemTime(&sys);
			std::cout << "������� ���� : ";
			std::cin >> sys.wDay;
			std::cout << std::endl;
			std::cout << "������� ����� : ";
			std::cin >> sys.wMonth;
			std::cout << std::endl;
			std::cout << "������� ���: ";
			std::cin >> sys.wYear;
			std::cout << std::endl;
			SystemTimeToFileTime(&sys, &file);
			//SetFileTime ������������� ���� � �����, ����� ���� ����������, ��������� ������ ��� ��������� ���������
			if (SetFileTime(hndl, &file, &file, &file)) {
				std::cout << " ���� ����������� " << std::endl;
			}
			else {
				std::cout << "������ � ������������ ���� " << std::endl;
			}
		}
	}

	}
