/******************************************************************************

	This source file is part of Viewizard Game Engine
	For the latest info, see http://www.viewizard.com/

	File name: Model3DManager.cpp

	Copyright (c) 2006-2007 Michael Kurinnoy, Viewizard
	All Rights Reserved.

	File Version: 3.0

******************************************************************************

	AstroMenace game source code available under "dual licensing" model.
	The licensing options available are:

	* Commercial Licensing. This is the appropriate option if you are
	  creating proprietary applications and you are not prepared to
	  distribute and share the source code of your application.
	  Contact us for pricing at viewizard@viewizard.com

	* Open Source Licensing. This is the appropriate option if you want
	  to share the source code of your application with everyone you
	  distribute it to, and you also want to give them the right to share
	  who uses it. You should have received a copy of the GNU General Public
	  License version 3 with this source codes.
	  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/


#include "Model3D.h"
#include "../System/System.h"


eModel3D *StartModel3D = 0;
eModel3D *EndModel3D = 0;








//-----------------------------------------------------------------------------
// Нахождение геометрии, или ее загрузка
//-----------------------------------------------------------------------------
eModel3D *vw_LoadModel3D(const char *nName)
{
	// сначала пытаемся найти уже сущ.
	eModel3D *tmp = StartModel3D;
	while (tmp != 0)
	{
		eModel3D *tmp2 = tmp->Next;
		if(!strcmp(tmp->Name, nName)) return tmp;
		tmp = tmp2;
	}

	// если ничего нет, значит нужно загрузить
	eModel3D * Model = 0;
	Model = new eModel3D;
	if (Model == 0) return 0;

	Model->ReadVW3D(nName);

	printf("Loaded ... %s\n", nName);

	return Model;
}



//-----------------------------------------------------------------------------
//	Присоеденяем Model3D к списку
//-----------------------------------------------------------------------------
void vw_AttachModel3D(eModel3D * NewModel3D)
{
	if (NewModel3D == 0) return;

	// первый в списке...
	if (EndModel3D == 0)
	{
		NewModel3D->Prev = 0;
		NewModel3D->Next = 0;
		StartModel3D = NewModel3D;
		EndModel3D = NewModel3D;
	}
	else // продолжаем заполнение...
	{
		NewModel3D->Prev = EndModel3D;
		NewModel3D->Next = 0;
		EndModel3D->Next = NewModel3D;
		EndModel3D = NewModel3D;
	}
}




//-----------------------------------------------------------------------------
//	Удаляем Model3D из списка
//-----------------------------------------------------------------------------
void vw_DetachModel3D(eModel3D * OldModel3D)
{
	if (OldModel3D == 0) return;

	// переустанавливаем указатели...
	if (StartModel3D == OldModel3D) StartModel3D = OldModel3D->Next;
	if (EndModel3D == OldModel3D) EndModel3D = OldModel3D->Prev;


	if (OldModel3D->Next != 0) OldModel3D->Next->Prev = OldModel3D->Prev;
		else if (OldModel3D->Prev != 0) OldModel3D->Prev->Next = 0;
	if (OldModel3D->Prev != 0) OldModel3D->Prev->Next = OldModel3D->Next;
		else if (OldModel3D->Next != 0) OldModel3D->Next->Prev = 0;
}




//-----------------------------------------------------------------------------
//	Удаляем все Model3D в списке
//-----------------------------------------------------------------------------
void vw_ReleaseAllModel3D()
{
	eModel3D *tmp = StartModel3D;
	while (tmp!=0)
	{
		eModel3D *tmp2 = tmp->Next;
		delete tmp; tmp = 0;
		tmp = tmp2;
	}

	StartModel3D = 0;
	EndModel3D = 0;
}



