#include <iostream>
#include <windows.h>
#include "winapi.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice;

	do {
		std::cout << "1)Вывод списка дисков" << std::endl;
		std::cout << "2)Вывод информации об одном диске (C) и размер свободного пространства" << std::endl;
		std::cout << "3)Создание и удаление заданных каталогов" << std::endl;
		std::cout << "4)Создание файлов" << std::endl;
		std::cout << "5)Копирование / перемещение файла между каталогами" << std::endl;
		std::cout << "6)Получить атрибуты файла/папки" << std::endl;
		std::cout << "7)Установить атрибуты/время файла/папки" << std::endl;
		std::cout << "8)Выход" << std::endl;

		std::cin >> choice;

		if (choice == 1)
		{
			DisksList();
		}
			

		if (choice == 2)
		{
			InfSpace();
		}
			

		if (choice == 3)
		{
			CreateAndDelete();
		}
			

		if (choice == 4)
		{
			Create_File();
		}
			

		if (choice == 5)
		{
			CopyAndMove();
		}
			

		if (choice == 6)
		{
			Getattrib();
		}
		
		if (choice == 7)
		{
			Setattrib();
		}

		if (choice == 8)
		{
			break;
		}

	} while (choice);
	std::cin.get();
	system("CLS");
	return 0;
}
