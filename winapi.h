#pragma once
#include <iostream>
#include <windows.h>
#include <io.h> // Функции для работы с содержимым файла
#include <stdio.h> 
#include <tchar.h> // Чтобы работал одноименный тип
#include <string>
#include <sstream> // Организация работы со строками, через интерфейс потоков
#include <bitset>
#include <fileapi.h>
#include <iomanip> // Инструменты для работы с форматированием вывода
#include <winbase.h>

#define _CRT_SECURE_NO_WARNINGS //совместимость с классическими функциями

void DisksList();
void InfSpace();
void CreateAndDelete();
void Create_File(); 
void CopyAndMove();
