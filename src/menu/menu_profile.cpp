/****************************************************************************

    AstroMenace
    Hardcore 3D space scroll-shooter with spaceship upgrade possibilities.
    Copyright (c) 2006-2019 Mikhail Kurinnoi, Viewizard


    AstroMenace is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AstroMenace is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AstroMenace. If not, see <https://www.gnu.org/licenses/>.


    Website: https://viewizard.com/
    Project: https://github.com/viewizard/astromenace
    E-mail: viewizard@viewizard.com

*****************************************************************************/

// FIXME ostringstream is not so fast, move all string initialization into setup,
//       all ostringstream-related code should be called only one time in init

// TODO translate comments

#include "../core/core.h"
#include "../enum.h"
#include "../config/config.h"
#include "../assets/audio.h"
#include "../assets/texture.h"
#include "../ui/cursor.h"
#include "../command.h"
#include "../game.h" // FIXME "game.h" should be replaced by individual headers
#include <sstream>
#include <iomanip>

// NOTE switch to nested namespace definition (namespace A::B::C { ... }) (since C++17)
namespace viewizard {
namespace astromenace {

// вот тут храним самый важный номер! - номер текущего профайла!!!
int CurrentProfile=-1;


std::u32string NewProfileName;
float LastProfileNameTime = 0.0f;
float CurrentProfileNameTransp = 0.9f;
int SoundOnProfileID = -1;

unsigned int SoundTaping{0};



//------------------------------------------------------------------------------------
// создание новой записи
//------------------------------------------------------------------------------------
void NewRecord()
{
    // заносим в новый профайл (последний)
    int ProfileNum = -1;
    for (int i = 4; i >= 0; i--) {
        if (!GameConfig().Profile[i].Used) {
            ProfileNum = i;
        }
    }


    // выводим диалог - все заняты!
    if (ProfileNum == -1) {
        SetCurrentDialogBox(eDialogBox::ProfileCreationError);
        return;
    }

    if (NewProfileName.empty()) {
        return;
    }


    // пишем данные в профайл

    ChangeGameConfig().Profile[ProfileNum] = sPilotProfile{};
    ChangeGameConfig().Profile[ProfileNum].Used = true;
    strcpy(ChangeGameConfig().Profile[ProfileNum].Name, ConvertUTF8.to_bytes(NewProfileName).c_str());

    // подготавливаем, для новой записи
    NewProfileName.clear();

    CurrentProfile = ProfileNum;
    ChangeGameConfig().LastProfile = CurrentProfile;
    // сразу ставим первую миссию все равно выбирать не из чего
    CurrentMission = 0;
    ChangeGameConfig().Profile[CurrentProfile].LastMission = CurrentMission;
    ProfileDifficulty(ProfileNum, eDifficultyAction::Update);
}




//------------------------------------------------------------------------------------
// создание дубликата записи
//------------------------------------------------------------------------------------
void DuplicateRecord()
{
    // ищем номер пустого слота для создания копии профайла
    int ProfileNum = -1;
    for (int i = 4; i >= 0; i--) {
        if (!GameConfig().Profile[i].Used) {
            ProfileNum = i;
        }
    }

    // выводим диалог - все слоты заняты!
    if (ProfileNum == -1) {
        SetCurrentDialogBox(eDialogBox::ProfileCreationError);
        return;
    }

    // копируем данные в новый профайл
    memcpy(&ChangeGameConfig().Profile[ProfileNum], &GameConfig().Profile[CurrentProfile], sizeof(GameConfig().Profile[0]));

    CurrentProfile = ProfileNum;
    ChangeGameConfig().LastProfile = CurrentProfile;
    CurrentMission = GameConfig().Profile[CurrentProfile].LastMission;
    ProfileDifficulty(ProfileNum, eDifficultyAction::Update);
}




//------------------------------------------------------------------------------------
// удаление записи
//------------------------------------------------------------------------------------
void DeleteRecord()
{
    if (CurrentProfile == -1) {
        return;
    }

    // если это последняя запись
    if (CurrentProfile == 4) {
        ChangeGameConfig().Profile[CurrentProfile].Used = false;
        CurrentProfile -= 1;
    } else {
        // или после этой записи - ничего нет
        if (!GameConfig().Profile[CurrentProfile+1].Used) {
            ChangeGameConfig().Profile[CurrentProfile].Used = false;
            CurrentProfile -= 1;
        } else {
            // удалили где-то в середине, сдвигаем все записи
            for (int i = CurrentProfile; i < 4; i++) {
                memcpy(&ChangeGameConfig().Profile[i], &GameConfig().Profile[i + 1], sizeof(GameConfig().Profile[0]));
                ChangeGameConfig().Profile[i+1].Used = false;
            }
        }
    }


    // проверяем, текущий номер
    if (CurrentProfile == -1 && GameConfig().Profile[0].Used) {
        CurrentProfile = 0;
    }

    ChangeGameConfig().LastProfile = CurrentProfile;
    ProfileDifficulty(config::MAX_PROFILES /*out of range*/, eDifficultyAction::UpdateAll);
}










//------------------------------------------------------------------------------------
// ввод названия
//------------------------------------------------------------------------------------
void ProfileInputText()
{

    if (!vw_GetCurrentUnicodeChar().empty()) {// если тут не ноль, а юникод - значит нажали
        if (vw_TextWidthUTF32(NewProfileName) < 540) {
            NewProfileName += vw_GetCurrentUnicodeChar();

            if (vw_IsSoundAvailable(SoundTaping)) {
                vw_StopSound(SoundTaping, 0);
            }
            SoundTaping = PlayMenuSFX(eMenuSFX::TapingClick, 1.0f);
        }
        vw_SetCurrentUnicodeChar(nullptr); // сразу сбрасываем данные
    }



    // проверяем, может спец-код
    if (vw_GetKeyStatus(SDLK_BACKSPACE) && !NewProfileName.empty()) {
        NewProfileName.pop_back();

        if (vw_IsSoundAvailable(SoundTaping)) {
            vw_StopSound(SoundTaping, 0);
        }
        SoundTaping = PlayMenuSFX(eMenuSFX::TapingClick, 1.0f);

        vw_SetKeyStatus(SDLK_BACKSPACE, false);
    }

    // ввод названия
    if ((vw_GetKeyStatus(SDLK_KP_ENTER) || vw_GetKeyStatus(SDLK_RETURN)) && !NewProfileName.empty()) {
        NewRecord();
        //Audio_PlayMenuSound(4,1.0f);
        vw_SetKeyStatus(SDLK_KP_ENTER, false);
        vw_SetKeyStatus(SDLK_RETURN, false);
    }



    int X1 = GameConfig().InternalWidth / 2 - 372;
    int Y1 = 230;

    // находим положения ввода
    int Size = vw_TextWidthUTF32(NewProfileName);
    sRECT SrcRect{0, 0, 2, 2};
    sRECT DstRect{X1 + Size + 2, Y1 - 2, X1 + 26 + Size, Y1 + 24};
    vw_Draw2D(DstRect, SrcRect, GetPreloadedTextureAsset("menu/whitepoint.tga"),
              true, CurrentProfileNameTransp * MenuContentTransp);

    float DeltaTime = vw_GetTimeThread(0) - LastProfileNameTime;
    LastProfileNameTime = vw_GetTimeThread(0);
    CurrentProfileNameTransp -= 2.0f * DeltaTime;
    if (CurrentProfileNameTransp < 0.2f) {
        CurrentProfileNameTransp = 0.9f;
    }

}

















//------------------------------------------------------------------------------------
// выбор текущего профайла
//------------------------------------------------------------------------------------
void ProfileMenu()
{
    sRECT SrcRect(2, 2, 861, 482);
    sRECT DstRect(GameConfig().InternalWidth / 2 - 427, 160, GameConfig().InternalWidth / 2 + 432, 160 + 480);
    vw_Draw2D(DstRect, SrcRect, GetPreloadedTextureAsset("menu/panel800_444_back.tga"), true, 0.9f*MenuContentTransp);


    int X1 = GameConfig().InternalWidth / 2 - 372;
    int Y1 = 200;
    int Prir1 = 24;

    // надпись
    vw_DrawTextUTF32(X1, Y1, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::orange}, MenuContentTransp, vw_GetTextUTF32("New Pilot Profile"));


    Y1 += 30;
    SrcRect(0,0,2,2);
    DstRect(X1-2,Y1-6,X1+2+590,Y1-2+30);
    vw_Draw2D(DstRect, SrcRect, GetPreloadedTextureAsset("menu/blackpoint.tga"), true, 0.2f*MenuContentTransp);
    DstRect(X1,Y1-4,X1+590,Y1-4+30);
    vw_Draw2D(DstRect, SrcRect, GetPreloadedTextureAsset("menu/blackpoint.tga"), true, 0.5f*MenuContentTransp);
    // кнопка, создания новой записи
    bool Off = false;
    if (NewProfileName.empty()) {
        Off = true;
    }
    if (DrawButton128_2(X1+616, Y1-6, vw_GetTextUTF32("Create"), MenuContentTransp, Off)) {
        NewRecord();
    }

    // ввод текста
    if (!isDialogBoxDrawing() && MenuContentTransp == 1.0f) {
        ProfileInputText();
    }

    vw_DrawTextUTF32(X1, Y1, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, MenuContentTransp, NewProfileName);

    Y1 += Prir1;







    // список для выбора записи
    Y1 += Prir1;
    vw_DrawTextUTF32(X1, Y1, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::orange}, MenuContentTransp, vw_GetTextUTF32("Pilot Profiles"));
    int Size = vw_TextWidthUTF32(vw_GetTextUTF32("Money"));
    float WScale = 0;
    if (Size > 70) {
        Size = 70;
        WScale = -70;
    }
    int SizeI = GameConfig().InternalWidth / 2 + 2 + (130 - Size) / 2;
    vw_DrawTextUTF32(SizeI, Y1, WScale, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::orange}, MenuContentTransp, vw_GetTextUTF32("Money"));

    Size = vw_TextWidthUTF32(vw_GetTextUTF32("Exp"));
    WScale = 0;
    if (Size > 100) {
        Size = 100;
        WScale = -100;
    }
    SizeI = GameConfig().InternalWidth / 2 + 132 + (130 - Size) / 2;
    vw_DrawTextUTF32(SizeI, Y1, WScale, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::orange}, MenuContentTransp, vw_GetTextUTF32("Exp"));

    Size = vw_TextWidthUTF32(vw_GetTextUTF32("Difficulty"));
    WScale = 0;
    if (Size > 100) {
        Size = 100;
        WScale = -100;
    }
    SizeI = GameConfig().InternalWidth / 2 + 262 + (130 - Size) / 2;
    vw_DrawTextUTF32(SizeI, Y1, WScale, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::orange}, MenuContentTransp, vw_GetTextUTF32("Difficulty"));


    Y1 += 30;
    SrcRect(0,0,2,2);
    DstRect(X1-2,Y1-6,X1+2+750,Y1-2+230);
    vw_Draw2D(DstRect, SrcRect, GetPreloadedTextureAsset("menu/blackpoint.tga"), true, 0.2f*MenuContentTransp);
    DstRect(X1,Y1-4,X1+750,Y1-4+230);
    vw_Draw2D(DstRect, SrcRect, GetPreloadedTextureAsset("menu/blackpoint.tga"), true, 0.5f*MenuContentTransp);
    Y1 += 230;



    int TMPSoundOnProfileID = -1;
    int TmpY = Y1-230+8;
    std::ostringstream tmpStream;
    tmpStream << std::fixed << std::setprecision(0);
    for (int i = 0; i < 5; i++) {
        if (GameConfig().Profile[i].Used) {
            tmpStream.clear();
            tmpStream.str(std::string{});
            tmpStream << i + 1 << ".";
            vw_DrawText(X1+10, TmpY, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, MenuContentTransp, tmpStream.str());

            if (vw_TextWidth(GameConfig().Profile[i].Name) > 300) {
                vw_DrawText(X1+50, TmpY, 0, 300, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, MenuContentTransp, GameConfig().Profile[i].Name);
                vw_DrawText(X1+50+310, TmpY, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, MenuContentTransp, "...");
            } else {
                vw_DrawText(X1+50, TmpY, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, MenuContentTransp, GameConfig().Profile[i].Name);
            }


            tmpStream.clear();
            tmpStream.str(std::string{});
            tmpStream << GameConfig().Profile[i].Money;
            Size = vw_TextWidth(tmpStream.str());
            SizeI = GameConfig().InternalWidth/2+2 + (130 - Size)/2;
            vw_DrawText(SizeI, TmpY, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, MenuContentTransp, tmpStream.str());

            tmpStream.clear();
            tmpStream.str(std::string{});
            tmpStream << GameConfig().Profile[i].Experience;
            Size = vw_TextWidth(tmpStream.str());
            SizeI = GameConfig().InternalWidth/2+132 + (130 - Size)/2;
            vw_DrawText(SizeI, TmpY, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, MenuContentTransp, tmpStream.str());

            tmpStream.clear();
            tmpStream.str(std::string{});
            tmpStream << ProfileDifficulty(i) << "%";
            Size = vw_TextWidth(tmpStream.str());
            SizeI = GameConfig().InternalWidth/2+262 + (130 - Size)/2;
            vw_DrawText(SizeI, TmpY, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, MenuContentTransp, tmpStream.str());


            // работаем с клавиатурой
            if (MenuContentTransp >= 0.99f && !isDialogBoxDrawing()) {
                CurrentActiveMenuElement++;
            }
            bool InFocusByKeyboard = false;
            if (CurrentKeyboardSelectMenuElement > 0) {
                if (CurrentKeyboardSelectMenuElement == CurrentActiveMenuElement) {
                    InFocusByKeyboard = true;
                }
            }

            // проверяем, если стоим над записью
            SrcRect(0,0,2,2);
            DstRect(X1,Y1-233+46*i,X1+750,Y1-234+46+46*i);
            if (!isDialogBoxDrawing() && (vw_MouseOverRect(DstRect) || InFocusByKeyboard)) {
                TMPSoundOnProfileID = i;
                SetCursorStatus(eCursorStatus::ActionAllowed);
                // если только встали - нужно звуком это показать
                if (SoundOnProfileID != i) {
                    SoundOnProfileID = i;
                    // если задействуем клавиатуру - неиграем тут звук
                    if (CurrentKeyboardSelectMenuElement == 0) {
                        PlayMenuSFX(eMenuSFX::OverLine, 1.0f);
                    }
                }

                if (vw_GetMouseLeftClick(true) || (InFocusByKeyboard && (vw_GetKeyStatus(SDLK_KP_ENTER) || vw_GetKeyStatus(SDLK_RETURN)))) {
                    // если другой - нужно сбросить миссию...
                    if (CurrentProfile != i) {
                        CurrentMission = GameConfig().Profile[i].LastMission;
                    }
                    CurrentProfile = i;
                    ChangeGameConfig().LastProfile = CurrentProfile;
                    // играем звук выбора
                    PlayMenuSFX(eMenuSFX::SelectLine, 1.0f);
                    if (InFocusByKeyboard) {
                        vw_SetKeyStatus(SDLK_KP_ENTER, false);
                        vw_SetKeyStatus(SDLK_RETURN, false);
                    }
                }

                if (CurrentProfile != i) {
                    // переход по 2-му клику
                    if (vw_GetMouseLeftDoubleClick(true)) {
                        CurrentProfile = i;
                        ChangeGameConfig().LastProfile = CurrentProfile;
                        // если другой - нужно сбросить миссию...
                        CurrentMission = GameConfig().Profile[CurrentProfile].LastMission;
                        cCommand::GetInstance().Set(eCommand::SWITCH_TO_MISSION);
                    }


                    DstRect(X1+2,Y1-233+46*i,X1+748,Y1-235+46+46*i);
                    if (CurrentProfile != i) {
                        vw_Draw2D(DstRect, SrcRect, GetPreloadedTextureAsset("menu/whitepoint.tga"), true, 0.1f*MenuContentTransp);
                    }
                } else {
                    // переход по 2-му клику
                    if (vw_GetMouseLeftDoubleClick(true)) {
                        cCommand::GetInstance().Set(eCommand::SWITCH_TO_MISSION);
                    }
                }
            }

        } else {
            float transp = 0.3f;
            tmpStream.clear();
            tmpStream.str(std::string{});
            tmpStream << i + 1 << ".";
            vw_DrawText(X1+10, TmpY, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, transp*MenuContentTransp, tmpStream.str());
            vw_DrawTextUTF32(X1+50, TmpY, 0, 0, 1.0f, sRGBCOLOR{eRGBCOLOR::white}, transp*MenuContentTransp, vw_GetTextUTF32("empty"));
        }

        TmpY += 46;
    }
    // если не стоим над профайлами - нужно сбросить флаг
    if (TMPSoundOnProfileID == -1) {
        SoundOnProfileID = -1;
    }


    // подсветка выбранного...
    if (CurrentProfile != -1) {
        SrcRect(0,0,2,2);
        DstRect(X1+2,Y1-233+46*CurrentProfile,X1+748,Y1-235+46+46*CurrentProfile);
        vw_Draw2D(DstRect, SrcRect, GetPreloadedTextureAsset("menu/whitepoint.tga"), true, 0.1f*MenuContentTransp);
    }








    Y1 += Prir1;


    // кнопка создания дубликата
    Off = true;
    if (CurrentProfile >= 0) {
        Off = false;
    }
    if (DrawButton200_2(X1+6, Y1-6, vw_GetTextUTF32("Duplicate"), MenuContentTransp, Off)) {
        DuplicateRecord();
    }

    // кнопка удаления записи
    Off = true;
    if (CurrentProfile >= 0) {
        Off = false;
    }
    if (DrawButton128_2(X1+240, Y1-6, vw_GetTextUTF32("Delete"), MenuContentTransp, Off)) {
        SetCurrentDialogBox(eDialogBox::DeleteProfile);
    }


    // кнопка установки сложности
    Off = true;
    if (CurrentProfile >= 0) {
        Off = false;
    }
    if (DrawButton200_2(X1+544, Y1-6, vw_GetTextUTF32("Difficulty"), MenuContentTransp, Off)) {
        cCommand::GetInstance().Set(eCommand::SWITCH_TO_DIFFICULTY);
    }



    int X = GameConfig().InternalWidth / 2 - 284;
    int Y = 165+100*5;
    if (DrawButton256(X,Y, vw_GetTextUTF32("MAIN MENU"), MenuContentTransp, Button10Transp, LastButton10UpdateTime)) {
        cCommand::GetInstance().Set(eCommand::SWITCH_TO_MAIN_MENU);
    }

    Off = true;
    if (CurrentProfile >= 0) {
        Off = false;
    }
    X = GameConfig().InternalWidth / 2 + 28;
    if (DrawButton256(X,Y, vw_GetTextUTF32("MISSION LIST"), MenuContentTransp, Button11Transp, LastButton11UpdateTime, Off)) {
        cCommand::GetInstance().Set(eCommand::SWITCH_TO_MISSION);
    }

}

} // astromenace namespace
} // viewizard namespace
