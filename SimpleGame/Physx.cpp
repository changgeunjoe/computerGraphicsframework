#include "Physx.h"
#include"stdafx.h"

CPhysx::CPhysx()
{
    static physx::PxDefaultAllocator gDefaultAllocatorCallback;
    static physx::PxDefaultErrorCallback gDefaultErrorCallback;
    static physx::PxDefaultCpuDispatcher* mCpuDispatcher;
    static physx::PxPvd* mPvd;

    physx::PxFoundation* mFoundation;
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
    if (!mFoundation)
        std::cout << "PHYSX ERROR!!: PxCreateFoundation failed!" << std::endl;


}

CPhysx::~CPhysx()
{
}

void CPhysx::init()
{
}
