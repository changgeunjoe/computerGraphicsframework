#include "Physx.h"
#include"Object.h"
#include"stdafx.h"

CPhysx::CPhysx()
{


}

CPhysx::~CPhysx()
{
}

void CPhysx::init()
{
    static physx::PxDefaultAllocator gDefaultAllocatorCallback;
    static physx::PxDefaultErrorCallback gDefaultErrorCallback;
    static physx::PxDefaultCpuDispatcher* mCpuDispatcher;
    static physx::PxPvd* mPvd;

    physx::PxFoundation* mFoundation;
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
    if (!mFoundation)
        std::cout << "PHYSX ERROR!!: PxCreateFoundation failed!" << std::endl;

    bool recordMemoryAllocations = true;

    mPvd = physx::PxCreatePvd(*mFoundation);
    physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);


    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation,
         physx::PxTolerancesScale(), recordMemoryAllocations, mPvd);
    if (!mPhysics)
    {
        std::cout << "PHYSX ERROR!!: PxCreatePhysics failed!" << std::endl;   
    }
    if (!PxInitExtensions(*mPhysics, mPvd))
        std::cout << "PxInitExtensions failed!" << std::endl;
    

  //  Pxcooking->meshWeldTolerance = 0.01f; // 메시 용접 허용 오차 설정 (원하는 값으로 변경)
   // Pxcooking->meshPreprocessParams = physx::PxMeshPreprocessingFlag::eWELD_VERTICES;
       // physx::PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH; // 메시 전처리 매개변수 설정 (원하는 값으로 변경)


    physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    mCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    sceneDesc.cpuDispatcher = mCpuDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    mScene = mPhysics->createScene(sceneDesc);
    if (!mScene)
        std::cout << "PHYSX ERROR!!: createScene failed!" << std::endl;


    if (!PxInitExtensions(*mPhysics, mPvd))
        std::cout << "PHYSX ERROR!!: PxInitExtensions failed!" << std::endl;

    physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();

    if (pvdClient)
    {
        pvdClient->setScenePvdFlags(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS | physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS | physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES);
    }

    mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.05f);    //static friction, dynamic friction, restitution
    if (!mMaterial)
    {
        std::cout << "PHYSX ERROR!!: createMaterial failed!" << std::endl;
      //  return false;
    }

}

bool CPhysx::BuiidActor()
{
    aCubeActor = physx::PxCreateDynamic(*mPhysics, physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f)), physx::PxBoxGeometry(1.0f, 1.0f, 1.0f),
        *mMaterial, denstiy);

    if (aCubeActor == nullptr)
    {
        std::cout << "PHYSX ERROR!!: create aCubeActor failed!" << std::endl;
        return -1;
    }
    mScene->addActor(*aCubeActor);
    
    aCubeActor2 = physx::PxCreateDynamic(*mPhysics, physx::PxTransform(physx::PxVec3(0.0f, 30.0f, 0.0f)), physx::PxBoxGeometry(1.0f, 1.0f, 1.0f),
        *mMaterial, denstiy);
    if (aCubeActor2 == nullptr)
    {
        std::cout << "PHYSX ERROR!!: create aCubeActor failed!" << std::endl;
        return -1;
    }
    mScene->addActor(*aCubeActor2);


     plane = PxCreatePlane(*mPhysics, physx::PxPlane(physx::PxVec3(0, 1, 0), 0), *mMaterial);
     //physx::PxTransform newTransform; // 새로운 위치와 방향을 나타내는 PxTransform

     //// 새로운 위치 설정 (예: (1, 0, 2)로 이동)
     //newTransform.p = physx::PxVec3(0.0f, 0.0f, 0.0f);

     //// 새로운 방향 설정 (평면이면 방향 변경 필요 없음)
     //newTransform.q = physx::PxQuat(0.0f, 0.0f, 0.0f, 1.0f); // 단위 쿼터니언

     //plane->setGlobalPose(newTransform);
    if (plane == nullptr)
    {
        std::cout << "FATAL ERROR!!: create shape failed!" << std::endl;
        return -1;
    }
    mScene->addActor(*plane);

}

void CPhysx::UpdatePhysics(vector<CObject*> mppObjects)
{
    mScene->simulate(1.0f / 144.0f);
    mScene->fetchResults(true);

    physx::PxVec3 aPos = aCubeActor->getGlobalPose().p;
    physx::PxQuat pxQuat = aCubeActor->getGlobalPose().q;

    glm::quat glmQuat = glm::quat(pxQuat.w, pxQuat.x, pxQuat.y, pxQuat.z);

    glm::vec3 euler = glm::eulerAngles(glmQuat);

    mppObjects[0]->SetPosition(vec3( aPos.x, aPos.y, aPos.z));
    mppObjects[0]->SetinitRotate(glm::vec3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z)));

    aPos = aCubeActor2->getGlobalPose().p;
    pxQuat = aCubeActor2->getGlobalPose().q;

    glmQuat = glm::quat(pxQuat.w, pxQuat.x, pxQuat.y, pxQuat.z);

    euler = glm::eulerAngles(glmQuat);

    mppObjects[1]->SetPosition(vec3(aPos.x, aPos.y, aPos.z));
    mppObjects[1]->SetinitRotate(glm::vec3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z)));
}
