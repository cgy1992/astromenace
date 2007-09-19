/////////////////////////////////////////////////
// Viewizard Game Engine
/////////////////////////////////////////////////
// File: vfs_var..cpp
/////////////////////////////////////////////////
// Copyright (c) 2001-2006, Michael Kurinnoy
// All Rights Reserved.
/////////////////////////////////////////////////
// Ver : 2.0
/////////////////////////////////////////////////


//------------------------------------------------------------------------------------
// include � lib...
//------------------------------------------------------------------------------------
#include "vfs_var.h"


//------------------------------------------------------------------------------------
// ����������
//------------------------------------------------------------------------------------
char *VFSFileName = 0;		// ��� ����� VFS
FILE *VFSFile = 0;			// ��������� �� ���� ����������� �������
byte *dstVFS = 0;			// ������ ��� �������/������
byte *srcVFS = 0;			// ������ ��� �������/������
int  dsizeVFS = 0;			// ������ ��� �������/������
int  ssizeVFS = 0;			// ������ ��� �������/������
int  DataStartOffsetVFS = 0;// �������� ������ � ��������� VFS (��� 8 ���� ���� ����)
int  HeaderOffsetVFS = 0;	// �������� ������� ������ � ��������� VFS
int  HeaderLengthVFS = 0;	// ����� ������� ������ ��������� VFS
int  NumberOfFilesVFS = 0;	// ���������� ������ � VFS
bool VFSFileOpen = false;	// ������ �������� VFS
bool VFSFileWritable = false;	// ����� ������ � VFS ����
eVFS_Entry *VFSdirArray = 0;// ������ ������� VFS
bool SetUpperVFS = false;	// ��������� ���� � �������� ����� � ������� ������� (�������� ��� ����� ��������)
char *ArhKeyVFS = 0;		// ����-��������
eFILE *StartFileVFS = 0;	// ��������� �� ������ ���� � ������...
eFILE *EndFileVFS = 0;		// ��������� �� ��������� ���� � ������...

int VFSversion = 2;


