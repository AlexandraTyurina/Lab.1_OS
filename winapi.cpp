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



		//���������� ���������� � �������� ������� � ������(�����������).
		if (GetVolumeInformationA("C:\\", drive_Name, sizeof(drive_Name), &serialNumber, &maxFileNameLength, &SystemFlag, SystemName, sizeof(SystemName)))
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
