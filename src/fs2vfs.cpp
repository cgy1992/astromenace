/************************************************************************************

	AstroMenace (Hardcore 3D space shooter with spaceship upgrade possibilities)
	Copyright (c) 2006-2018 Mikhail Kurinnoi, Viewizard


	AstroMenace is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	AstroMenace is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with AstroMenace. If not, see <http://www.gnu.org/licenses/>.


	Web Site: http://www.viewizard.com/
	Project: https://github.com/viewizard/astromenace
	E-mail: viewizard@viewizard.com

*************************************************************************************/

#include "core/vfs/vfs.h"
#include "config.h"

std::string GameData[] = {
	"lang/ru/voice/EngineMalfunction.wav",
	"lang/ru/voice/WeaponDamaged.wav",
	"lang/ru/voice/MissileDetected.wav",
	"lang/ru/voice/PrepareForAction.wav",
	"lang/ru/voice/Attention.wav",
	"lang/ru/voice/WeaponDestroyed.wav",
	"lang/ru/voice/WeaponMalfunction.wav",
	"lang/ru/voice/CeaseFire.wav",
	"lang/ru/voice/PowerSupplyReestablished.wav",
	"lang/ru/voice/ReactorMalfunction.wav",
	"lang/ru/voice/Warning.wav",
	"lang/ru/menu/button_weaponry_in.tga",
	"lang/ru/menu/button_weaponry_out.tga",
	"lang/ru/game/pause.tga",
	"lang/ru/game/mission.tga",
	"lang/ru/game/missionfailed.tga",
	"loading/loading_back.tga",
	"menu/weapon_empty_icon.tga",
	"menu/system_engine1.tga",
	"menu/system_engine2.tga",
	"menu/system_engine3.tga",
	"menu/system_engine4.tga",
	"menu/system_target1.tga",
	"menu/system_target2.tga",
	"menu/system_target3.tga",
	"menu/system_target4.tga",
	"menu/system_power1.tga",
	"menu/system_power2.tga",
	"menu/system_power3.tga",
	"menu/system_power4.tga",
	"menu/system_protect1.tga",
	"menu/system_protect2.tga",
	"menu/system_protect3.tga",
	"menu/system_protect4.tga",
	"menu/system_mechan1.tga",
	"menu/system_mechan2.tga",
	"menu/system_mechan3.tga",
	"menu/system_mechan4.tga",
	"menu/system_empty.tga",
	"glsl/light.vert",
	"glsl/light.frag",
	"glsl/light_shadowmap.vert",
	"glsl/light_shadowmap.frag",
	"glsl/particle.frag",
	"glsl/particle_stars.vert",
	"glsl/light_explosion.frag",
	"glsl/light_explosion.vert",
	"glsl/particle.vert",
	"credits/gentoo.tga",
	"credits/gimp.tga",
	"credits/sdl.tga",
	"credits/opengl.tga",
	"credits/gnugcc.tga",
	"credits/codeblocks.tga",
	"credits/openal.tga",
	"credits/git.tga",
	"menu/cursor.tga",
	"lang/en/voice/EngineMalfunction.wav",
	"lang/en/voice/WeaponDamaged.wav",
	"lang/en/voice/MissileDetected.wav",
	"lang/en/voice/PrepareForAction.wav",
	"lang/en/voice/Attention.wav",
	"lang/en/voice/WeaponDestroyed.wav",
	"lang/en/voice/WeaponMalfunction.wav",
	"lang/en/voice/CeaseFire.wav",
	"lang/en/voice/PowerSupplyReestablished.wav",
	"lang/en/voice/ReactorMalfunction.wav",
	"lang/en/voice/Warning.wav",
	"lang/en/menu/button_weaponry_in.tga",
	"lang/en/menu/button_weaponry_out.tga",
	"lang/en/game/pause.tga",
	"lang/en/game/mission.tga",
	"lang/en/game/missionfailed.tga",
	"sfx/weaponfire12.wav",
	"sfx/drag_offslot.wav",
	"sfx/menu_click.wav",
	"sfx/drag_error.wav",
	"sfx/menu_onbutton.wav",
	"sfx/weapon1probl.wav",
	"sfx/weaponfire3.wav",
	"sfx/gausshit.wav",
	"sfx/menu_online.wav",
	"sfx/weaponfire5.wav",
	"sfx/weapon4probl.wav",
	"sfx/drag_release.wav",
	"sfx/menu_selectline.wav",
	"sfx/weaponfire1.wav",
	"sfx/weaponfire14.wav",
	"sfx/weaponfire13.wav",
	"sfx/weaponfire16.wav",
	"sfx/weaponfire17.wav",
	"sfx/explosion4.wav",
	"sfx/weapon3probl.wav",
	"sfx/plasmahit.wav",
	"sfx/weaponfire19.wav",
	"sfx/menu_nclick.wav",
	"sfx/drag_onslot.wav",
	"sfx/weaponfire10.wav",
	"sfx/ionhit.wav",
	"sfx/weaponfire6.wav",
	"sfx/weaponfire7.wav",
	"sfx/weaponfire15.wav",
	"sfx/explosion2.wav",
	"sfx/weaponfire8.wav",
	"sfx/weaponfire2.wav",
	"sfx/menu_onbutton2.wav",
	"sfx/weaponfire18.wav",
	"sfx/menu_new.wav",
	"sfx/weaponfire4.wav",
	"sfx/antimaterhit.wav",
	"sfx/weapon5probl.wav",
	"sfx/explosion3.wav",
	"sfx/kinetichit.wav",
	"sfx/weaponfire9.wav",
	"sfx/menu_taping.wav",
	"sfx/game_showmenu.wav",
	"sfx/game_hidemenu.wav",
	"sfx/weaponfire11.wav",
	"sfx/weapon2probl.wav",
	"sfx/explosion1.wav",
	"sfx/lowlife.wav",
	"models/mine/mine2i.tga",
	"models/mine/mine1.tga",
	"models/mine/mine3i.tga",
	"models/mine/mine3.tga",
	"models/mine/mine-04.vw3d",
	"models/mine/mine-01.vw3d",
	"models/mine/mine2.tga",
	"models/mine/mine-03.vw3d",
	"models/mine/mine1i.tga",
	"models/mine/mine-02.vw3d",
	"models/mine/mine4i.tga",
	"models/mine/mine4.tga",
	"models/planet/planet5.vw3d",
	"models/planet/aplanet.vw3d",
	"models/planet/dplanet.vw3d",
	"models/planet/m_class7.tga",
	"models/planet/a_class4.tga",
	"models/planet/d_class3.tga",
	"models/planet/planet6.vw3d",
	"models/planet/q_class2.tga",
	"models/planet/gplanet.vw3d",
	"models/planet/moon.vw3d",
	"models/planet/clouds.tga",
	"models/planet/asteroid.tga",
	"models/spacebase/4/1.vw3d",
	"models/spacebase/3/1.vw3d",
	"models/spacebase/7/1.vw3d",
	"models/spacebase/1/2.vw3d",
	"models/spacebase/1/4.vw3d",
	"models/spacebase/1/3.vw3d",
	"models/spacebase/1/1.vw3d",
	"models/spacebase/1/5.vw3d",
	"models/spacebase/metal.tga",
	"models/spacebase/5/1.vw3d",
	"models/spacebase/6/2.vw3d",
	"models/spacebase/6/4.vw3d",
	"models/spacebase/6/3.vw3d",
	"models/spacebase/6/1.vw3d",
	"models/spacebase/6/5.vw3d",
	"models/spacebase/8/2.vw3d",
	"models/spacebase/8/4.vw3d",
	"models/spacebase/8/3.vw3d",
	"models/spacebase/8/1.vw3d",
	"models/spacebase/8/5.vw3d",
	"models/spacebase/allalpha.tga",
	"models/spacebase/2/2.vw3d",
	"models/spacebase/2/4.vw3d",
	"models/spacebase/2/3.vw3d",
	"models/spacebase/2/1.vw3d",
	"models/spacebase/2/5.vw3d",
	"models/turret/turret-02.vw3d",
	"models/turret/turret-01.vw3d",
	"models/turret/turrets.tga",
	"models/space/asteroid-0118.vw3d",
	"models/space/asteroid-0116.vw3d",
	"models/space/asteroid-011.vw3d",
	"models/space/bigasteroid-03.vw3d",
	"models/space/asteroid-018.vw3d",
	"models/space/asteroid-017.vw3d",
	"models/space/asteroid-016.vw3d",
	"models/space/bigasteroid-02.vw3d",
	"models/space/bigasteroid-05.vw3d",
	"models/space/asteroid-01.tga",
	"models/space/asteroid-0110.vw3d",
	"models/space/asteroid-0115.vw3d",
	"models/space/asteroid-0112.vw3d",
	"models/space/asteroid-0117.vw3d",
	"models/space/asteroid-012.vw3d",
	"models/space/asteroid-019.vw3d",
	"models/space/bigasteroid-01.vw3d",
	"models/space/asteroid-013.vw3d",
	"models/space/asteroid-0119.vw3d",
	"models/space/asteroid-0114.vw3d",
	"models/space/asteroid-014.vw3d",
	"models/space/asteroid-0113.vw3d",
	"models/space/asteroid-015.vw3d",
	"models/space/bigasteroid-04.vw3d",
	"models/space/asteroid-010.vw3d",
	"models/space/asteroid-0111.vw3d",
	"models/earthfighter/lnch1.vw3d",
	"models/earthfighter/lnch2.vw3d",
	"models/earthfighter/lnch3.vw3d",
	"models/earthfighter/lnch4.vw3d",
	"models/earthfighter/rockets.tga",
	"models/earthfighter/torpedo.vw3d",
	"models/earthfighter/swarm.vw3d",
	"models/earthfighter/lnch34.tga",
	"models/earthfighter/missile.vw3d",
	"models/earthfighter/nuke.vw3d",
	"models/earthfighter/lnch12.tga",
	"menu/weapon4_icon.tga",
	"menu/ammo.tga",
	"menu/weapon17_icon.tga",
	"menu/workshop_panel1.tga",
	"menu/weapon18_icon.tga",
	"menu/weapon14_icon.tga",
	"menu/weapon19_icon.tga",
	"menu/weapon13_icon.tga",
	"menu/panel800_444_back.tga",
	"menu/button384_back.tga",
	"menu/panel444_333_back.tga",
	"menu/weapon2_icon.tga",
	"menu/button_dialog128_in.tga",
	"menu/weapon6_icon.tga",
	"menu/arrows_blue.tga",
	"menu/arrow_list_up.tga",
	"menu/arrow_list_down.tga",
	"menu/workshop_panel5.tga",
	"menu/workshop_panel3.tga",
	"menu/dialog768_600.tga",
	"menu/dialog512_256.tga",
	"menu/perc_none.tga",
	"menu/weapon5_icon.tga",
	"menu/panel444_333_border.tga",
	"menu/button_dialog200_out.tga",
	"menu/workshop_panel4.tga",
	"menu/weapon12_icon.tga",
	"menu/whitepoint.tga",
	"menu/weapon16_icon.tga",
	"menu/weapon11_icon.tga",
	"menu/back_spot2.tga",
	"menu/button256_off.tga",
	"menu/blackpoint.tga",
	"menu/checkbox_main.tga",
	"menu/button_dialog200_off.tga",
	"menu/workshop_panel1+.tga",
	"menu/weapon10_icon.tga",
	"menu/perc.tga",
	"menu/workshop_panel2.tga",
	"menu/dialog512_512.tga",
	"menu/button_dialog200_in.tga",
	"menu/button384_out.tga",
	"menu/button384_in.tga",
	"menu/weapon15_icon.tga",
	"menu/workshop_panel2+.tga",
	"menu/line.tga",
	"menu/button256_out.tga",
	"menu/weapon3_icon.tga",
	"menu/button256_in.tga",
	"menu/back_spot.tga",
	"menu/button256_back.tga",
	"menu/weapon_on_icon.tga",
	"menu/weapon8_icon.tga",
	"menu/astromenace.tga",
	"menu/weapon9_icon.tga",
	"menu/weapon1_icon.tga",
	"menu/checkbox_in.tga",
	"menu/weapon7_icon.tga",
	"menu/button_dialog128_out.tga",
	"menu/button_dialog128_off.tga",
	"game/ammo.tga",
	"game/weapon_panel_left.tga",
	"game/game_panel.tga",
	"game/weapon_ammo.tga",
	"game/game_panel2.tga",
	"game/energy.tga",
	"game/nums.tga",
	"game/game_num.tga",
	"game/weapon_panel_right.tga",
	"game/game_panel_el.tga",
	"game/weapon_energy.tga",
	"gfx/flare2.tga",
	"gfx/flare.tga",
	"gfx/flare1.tga",
	"gfx/flare3.tga",
	"loading/viewizardlogo.tga",
	"loading/loading03.tga",
	"loading/loading_line.tga",
	"loading/loading01.tga",
	"loading/loading02.tga",
	"loading/loading04.tga",
	"lang/de/voice/EngineMalfunction.wav",
	"lang/de/voice/WeaponDamaged.wav",
	"lang/de/voice/MissileDetected.wav",
	"lang/de/voice/PrepareForAction.wav",
	"lang/de/voice/Attention.wav",
	"lang/de/voice/WeaponDestroyed.wav",
	"lang/de/voice/WeaponMalfunction.wav",
	"lang/de/voice/CeaseFire.wav",
	"lang/de/voice/PowerSupplyReestablished.wav",
	"lang/de/voice/ReactorMalfunction.wav",
	"lang/de/voice/Warning.wav",
	"lang/de/menu/button_weaponry_in.tga",
	"lang/de/menu/button_weaponry_out.tga",
	"lang/de/game/pause.tga",
	"lang/de/game/mission.tga",
	"lang/de/game/missionfailed.tga",
	"menu/cursor_shadow.tga",
	"music/boss-intro.ogg",
	"music/menu.ogg",
	"music/boss-loop.ogg",
	"music/game.ogg",
	"music/missionfailed.ogg",
	"music/intro.ogg",
	"script/mission6.xml",
	"script/list.xml",
	"script/mission14.xml",
	"script/mission8.xml",
	"script/mission9_icon.tga",
	"script/mission15_icon.tga",
	"script/mission3.xml",
	"script/mission7.xml",
	"script/mission12.xml",
	"script/mission5.xml",
	"script/mission1.xml",
	"script/mission10_icon.tga",
	"script/mission13_icon.tga",
	"script/menu3.xml",
	"script/mission5_icon.tga",
	"script/mission13.xml",
	"script/mission14_icon.tga",
	"script/mission6_icon.tga",
	"script/mission3_icon.tga",
	"script/mission11.xml",
	"script/mission4.xml",
	"script/mission2.xml",
	"script/mission11_icon.tga",
	"script/mission4_icon.tga",
	"script/mission8_icon.tga",
	"script/mission7_icon.tga",
	"script/aimode.xml",
	"script/mission10.xml",
	"script/mission2_icon.tga",
	"script/mission12_icon.tga",
	"script/menu2.xml",
	"script/mission15.xml",
	"script/mission1_icon.tga",
	"script/mission9.xml",
	"script/menu1.xml",
	"skybox/1/skybox_front5.tga",
	"skybox/1/skybox_left2.tga",
	"skybox/1/skybox_right1.tga",
	"skybox/1/skybox_back6.tga",
	"skybox/1/skybox_bottom4.tga",
	"skybox/1/skybox_top3.tga",
	"skybox/tile_back.tga",
	"skybox/tile_stars.tga",
	"skybox/2/skybox_front5.tga",
	"skybox/2/skybox_left2.tga",
	"skybox/2/skybox_right1.tga",
	"skybox/2/skybox_back6.tga",
	"skybox/2/skybox_bottom4.tga",
	"skybox/2/skybox_top3.tga",
#ifndef fontconfig
	"font/LiberationMono-Bold.ttf",
	"font/LiberationSans-Bold.ttf",
	"font/LiberationSerif-Bold.ttf",
	"font/FreeMonoBold.ttf",
	"font/FreeSansBold.ttf",
	"font/FreeSerifBold.ttf",
	"font/LinBiolinumBold.ttf",
	"font/LinLibertineBold.ttf",
#endif /* fontconfig */
	"credits/freetype.tga",
	"credits/oggvorbis.tga",
	"lang/text.csv",
	"gfx/trail1.tga",
	"gfx/trail2.tga",
	"gfx/trail3.tga",
	"gfx/trail4.tga",
	"gfx/trail5.tga",
	"models/normalmap/alien_mothership_nm.tga",
	"models/normalmap/m_class7_nm.tga",
	"models/normalmap/d_class3_nm.tga",
	"models/normalmap/a_class4_nm.tga",
	"models/normalmap/planet_asteroids_nm.tga",
	"models/normalmap/q_class2_nm.tga",
	"models/normalmap/bomber_nm.tga",
	"models/normalmap/buildings_nm.tga",
	"lang/pl/menu/button_weaponry_in.tga",
	"lang/pl/menu/button_weaponry_out.tga",
};
#define GameDataCount sizeof(GameData)/sizeof(GameData[0])

/*
 * Create game data VFS file (convert FS to VFS).
 */
int ConvertFS2VFS(const std::string RawDataDir, const std::string VFSFileNamePath)
{
	return vw_CreateVFS(VFSFileNamePath, GAME_BUILD,
			    RawDataDir, "models/models.pack",
			    GameData, GameDataCount);
}
