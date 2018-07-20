/************************************************************************************

	AstroMenace
	Hardcore 3D space scroll-shooter with spaceship upgrade possibilities.
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
	along with AstroMenace. If not, see <https://www.gnu.org/licenses/>.


	Website: https://www.viewizard.com/
	Project: https://github.com/viewizard/astromenace
	E-mail: viewizard@viewizard.com

*************************************************************************************/

// TODO translate comments

// TODO switch to enumerations

// TODO correct hierarchy, explosion to "dust" and explosion to "debris" should be separated

#ifndef OBJECT3D_EXPLOSION_EXPLOSION_H
#define OBJECT3D_EXPLOSION_EXPLOSION_H

#include "../object3d.h"
#include "../projectile/projectile.h"

// NOTE switch to nested namespace definition (namespace A::B::C { ... }) (since C++17)
namespace viewizard {
namespace astromenace {

class cGroundObject;

struct sExplosionPiece {
	// вектор направления движения частицы (скорости включены)
	sVECTOR3D Velocity;
	// оставшееся время жизни частицы
	float Life;
};

class cExplosion : public cObject3D
{
	friend void UpdateAllExplosion(float Time);
	friend void ReleaseAllExplosions();

protected:
	// don't allow object of this class creation
	cExplosion();
	virtual ~cExplosion();

public:
	// Обновление данных объектa
	virtual bool Update(float Time) override;

	int ExplosionType{0};
	int ExplosionTypeByClass{0};

	// набор управления частицами
	sExplosionPiece *ExplosionPieceData{nullptr};

	float ExplosionGeometryMoveLastTime{-1}; // последнее время изменения геометрии, нет смысла постоянно менять геометрию, делаем это 30 раз в секунду только

	sVECTOR3D VelocityOrientation{0.0f, 0.0f, 0.0f};
	float OldSpeed{0.0f};
	bool NeedStop{true};

	// скорость изменения AABB
	float AABBSpeed{0.0f};

	// для прорисовки графических эффектов
	std::vector<std::weak_ptr<cParticleSystem>> GraphicFX{};

	// для собственного списка
	cExplosion *Next{nullptr};
	cExplosion *Prev{nullptr};
};

class cBulletExplosion : public cExplosion
{
	friend void CreateBulletExplosion(const cObject3D *Object, cProjectile *Projectile,
					  int ExplType, const sVECTOR3D &ExplLocation,
					  float Speed, bool NeedExplosionSFX);
private:
	explicit cBulletExplosion(const cObject3D *Object, cProjectile *Projectile,
				  int ExplType, const sVECTOR3D &ExplLocation,
				  float Speed, bool NeedExplosionSFX);
};

class cGroundExplosion : public cExplosion
{
	friend void CreateGroundExplosion(cGroundObject &Object, int ExplType,
					  const sVECTOR3D &ExplLocation,
					  int ObjectChunkNum, bool NeedExplosionSFX);
private:
	explicit cGroundExplosion(cGroundObject &Object, int ExplType, const sVECTOR3D &ExplLocation,
				  int ObjectChunkNum, bool NeedExplosionSFX);
};

class cSpaceExplosion : public cExplosion
{
	friend void CreateSpaceExplosion(cObject3D &Object, int ExplType,
					 const sVECTOR3D &ExplLocation, float Speed,
					 int ObjectChunkNum, bool NeedExplosionSFX);
private:
	explicit cSpaceExplosion(cObject3D &Object, int ExplType,
				 const sVECTOR3D &ExplLocation, float Speed,
				 int ObjectChunkNum, bool NeedExplosionSFX);
};


// Create cBulletExplosion object.
void CreateBulletExplosion(const cObject3D *Object, cProjectile *Projectile,
			   int ExplType, const sVECTOR3D &ExplLocation,
			   float Speed, bool NeedExplosionSFX = true);
// Create cGroundExplosion object.
void CreateGroundExplosion(cGroundObject &Object, int ExplType,
			   const sVECTOR3D &ExplLocation,
			   int ObjectChunkNum, bool NeedExplosionSFX = true);
// Create cSpaceExplosion object.
void CreateSpaceExplosion(cObject3D &Object, int ExplType,
			  const sVECTOR3D &ExplLocation, float Speed,
			  int ObjectChunkNum, bool NeedExplosionSFX = true);
// Проверяем все объекты, обновляем данные
void UpdateAllExplosion(float Time);
// Прорисовываем все объекты
void DrawAllExplosions(bool VertexOnlyPass);
// Удаляем все объекты в списке
void ReleaseAllExplosions();
//
void SetExplosionGFX(std::shared_ptr<cParticleSystem> &ParticleSystem, int GFXNum);

} // astromenace namespace
} // viewizard namespace

#endif // OBJECT3D_EXPLOSION_EXPLOSION_H
