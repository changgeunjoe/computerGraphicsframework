#pragma once
#include<physx/PxPhysicsAPI.h>
#include<physx/cooking/PxCooking.h>
#include"stdafx.h"
class CObject;
class CPhysx
{
public:
	CPhysx();
	~CPhysx();


public:
	void init();

	bool BuildActor();

	void addDynamicTriangleMeshInstance(const physx::PxTransform& transform, physx::PxTriangleMesh* mesh);
	void addDynamicTriangleMeshInstancemove(const physx::PxTransform& transform, physx::PxTriangleMesh* mesh);
	void UpdatePhysics(vector<CObject*> mppObjects);
	physx::PxTriangleMesh* CreateTriangleMesh(CObject* gm);
private:
	physx::PxPhysics* mPhysics{};
	physx::PxScene* mScene{};
	physx::PxMaterial* mMaterial{};

	physx::PxCookingParams* Pxcooking{};
	physx::PxConvexMeshDesc convexDesc;

	physx::PxReal denstiy = 10;
	physx::PxRigidDynamic* aCubeActor;
	physx::PxRigidDynamic* aCubeActor2;
	
	vector< physx::PxRigidDynamic*> dyns;
	physx::PxRigidStatic* plane;
};

