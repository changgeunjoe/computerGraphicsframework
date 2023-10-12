#pragma once
#include<physx/PxPhysicsAPI.h>
#include"stdafx.h"
class CObject;
class CPhysx
{
public:
	CPhysx();
	~CPhysx();


public:
	void init();

	bool BuiidActor();

	void UpdatePhysics(vector<CObject*> mppObjects);

private:
	physx::PxPhysics* mPhysics{};
	physx::PxScene* mScene{};
	physx::PxMaterial* mMaterial{};

	physx::PxCookingParams* Pxcooking{};


	physx::PxReal denstiy = 10;
	physx::PxRigidDynamic* aCubeActor;
	physx::PxRigidDynamic* aCubeActor2;
	physx::PxRigidStatic* plane;
};

