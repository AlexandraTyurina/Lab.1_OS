#pragma once
#include <iostream>
#include <windows.h>
#include <io.h> // ������� ��� ������ � ���������� �����
#include <stdio.h> 
#include <tchar.h> // ����� ������� ����������� ���
#include <string>
#include <sstream> // ����������� ������ �� ��������, ����� ��������� �������
#include <bitset>
#include <fileapi.h>
#include <iomanip> // ����������� ��� ������ � ��������������� ������
#include <winbase.h>

#define _CRT_SECURE_NO_WARNINGS //������������� � ������������� ���������

void DisksList();
void InfSpace();
void CreateAndDelete();
void Create_File(); 
void CopyAndMove();
