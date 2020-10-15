#include "winapi.h"

void DisksList()
{
	std::cout << " Used GetLogicalDrives() : \n" ;
	int n = 0;
	char letter;
	DWORD dr = GetLogicalDrives(); // возвращает число-битовую маску в которой храняться все доступные диски

	for (int i = 0; i < 26; i++)  // прогоняем по битам
	{
		n = ((dr >> i) & 0x1); // определяем значение текущего бита
		if (n == 1) 
		{
			letter = char(65 + i);  // получаем литеру диска
			std::cout << " " << letter << std::endl;
		}
	}
	/*
	*GetLogicalDriveStrings(nBufferLength,lpBuffer) - определяет диски на компьютере и размещает их названия корневых каталогов в строку lpBuffer
	*nBufferLength - максимальный размер буфера в TCHAR, на который указывает lpBuffer
	*lpBuffer - адрес буфера, который получает последовательность завершающихся строк по одной на устройство + доп.нулевой символ. Каждая строка – это имя устройства.*/
	std::cout << "\n Used GetLogicalDriveStrings() : \n";  //
	TCHAR szDrives[MAX_PATH + 1];
	GetLogicalDriveStrings(MAX_PATH, szDrives);
	TCHAR* pletter = szDrives;
		while (*pletter)
		{
			_tprintf(_T(" %s \n"), pletter);  // для символов типа TCHAR

			while (*++pletter);
			pletter++;
		}
	std::cout << std::endl;
}
void InfSpace()
{
	//GetDriveType() определяет типы дисков (removable, fixed, CD-ROM, RAM disk, или network drive) на компьютере.

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



		//GetVolumeInformationA - возвращает информацию о файловой системе и дисках(директориях).
		if (GetVolumeInformationA ("C:\\", drive_Name, sizeof(drive_Name), &serialNumber, &maxFileNameLength, &SystemFlag, SystemName, sizeof(SystemName)))
		{
			std::cout << " Имя диска : " << drive_Name << std::endl;
			std::cout << " Серийный номер : " << serialNumber << std::endl;
			std::cout << " Тип файловой системы : " << SystemName << std::endl;
			std::cout << " Системные флаги : " << SystemFlag << std::endl;
			//SystemFlag - переменная, которая получает флажки, связанные с указанной файловой системой.Возможны любые комбинации флажков.
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
			std::cout << "Ошибка в вызове GetVolumeInformation!" << std::endl;
		}
		// Число секторов в кластере, Число байт в секторе, Число свободных кластеров, Общее число кластеров
		DWORD sectorsPerCluster;
		DWORD bytesPerSector;
		DWORD numberOfFreeClusters;
		DWORD totalNumberOfClusters;
		if (GetDiskFreeSpace(L"C:\\", &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters, &totalNumberOfClusters))
		{
			std::cout << "Секторов в кластере : " << sectorsPerCluster << std::endl;
			std::cout << "Байтов в секторе : " << bytesPerSector << std::endl;
			std::cout << "Свободных кластеров : " << numberOfFreeClusters << std::endl;
			std::cout << "Количество кластеров : " << totalNumberOfClusters << std::endl;
			double frspace = (double)sectorsPerCluster * (double)bytesPerSector * (double)numberOfFreeClusters / 1024 / 1024;
			std::cout << "Количестов свободного места в мегабайтах : " << frspace << '\n';
		}
		else 
		{
			std::cout << "Ошибка в вызове GetDiskFreeSpace" << std::endl;
		}
		std::cout << std::endl;
}

void CreateAndDelete()
{
	std::cout << "0 – создание" << std::endl;
	std::cout << "1 – удаление" << std::endl;
	int choice;
	std::cin >> choice;
	// Ввод с консоли пути при необходимости типа LPCWSTR. 
	std::cout << "Введите путь : ";
	std::wstring path;
	std::wcin >> path;
	LPCWSTR pcwstr;
	pcwstr = path.c_str();

	if (choice == 0)
	{
		if (CreateDirectory(pcwstr, NULL)) std::cout << " Директория создана" << std::endl; //"C:\\Test"
		else std::cout << " Ошибка создания директории" << std::endl;
	}

	if (choice == 1)
	{
		if (RemoveDirectory(pcwstr)) std::cout << " Директория удалена" << std::endl;
		else std::cout << " Ошибка удаления директории" << std::endl;

	}
}

void Create_File()
{
	HANDLE hndl;
	std::cout << "Введите путь : ";

	LPCWSTR pcwstr;
	std::wstring path;
	std::wcin >> path;

	pcwstr = path.c_str();
	
	/*GENERIC_WRITE - открывается для записи, 
	0 -совместно не используется, 
	NULL - защита по умолчанию, 
	CREATE_ALWAYS - переписывает существующий, 
	FILE_ATTRIBUTE_NORMAL -обычный файл, 
	NULL -атрибутов шаблона нет*/
	hndl = CreateFile(pcwstr, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hndl != INVALID_HANDLE_VALUE) 
	{
		std::wcout << " Файл " << path << " создан " << std::endl;
	}
	else 
	{
		std::cout << "Ошибка в создании файла";
	}
	//CloseHandle закрывает дескриптор открытого объекта.
	CloseHandle(hndl);
	std::cout << std::endl;
}

void CopyAndMove()
{
	std::cout << "0 – копировать" << std::endl;
	std::cout << "1 – переместить" << std::endl;
	int ch;
	std::cin >> ch;

	LPCWSTR path_before, path_after;
	std::wstring path1, path2;

	std::cout << "Введите путь откуда копировать / перемещать: ";
	std::wcin >> path1;
	std::cout << "Введите путь куда копировать / перемещать: ";
	std::wcin >> path2;
	path_before = path1.c_str();
	path_after = path2.c_str();

	if (ch == 0)
	{
		if (CopyFile(path_before, path_after, false)) 
		{
			std::cout << "Файл успешно скопирован " << std::endl;
		}
		else 
		{
			std::cout << "Ошибка копирования файла " << GetLastError() << std::endl;
		}
	}
	if (ch == 1)
	{
		if (MoveFile(path_before, path_after))
		{
			std::cout << " Файл успешно перемещен " << std::endl;
		}
		else
		{
			std::cout << " Ошибка перемещения файла " << GetLastError() << std::endl;
		}
	}
	std::cout << std::endl;
}