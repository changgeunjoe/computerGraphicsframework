#include "Physx.h"
#include "Object.h"
#include"Mesh.h"
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
    Pxcooking = new physx::PxCookingParams(physx::PxTolerancesScale());
    Pxcooking->meshWeldTolerance = 0.001f;
    Pxcooking->meshPreprocessParams = physx::PxMeshPreprocessingFlag::eWELD_VERTICES; // 메시 전처리 옵션을 설정
    Pxcooking->buildTriangleAdjacencies = true;
    Pxcooking->buildGPUData = true;
   // Pxcooking->mesh = physx::PxMeshCookingHint::eCOOKING_PERFORMANCE; // 요리 힌트 설정

   // Pxcooking(physx::PxTolerancesScale());


 /*   cook::PxCooking* cook = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, cookingParams);
    physx::pxcooking*/


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

bool CPhysx::BuildActor()
{
    aCubeActor = physx::PxCreateDynamic(*mPhysics, physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f)), physx::PxBoxGeometry(1.0f, 1.0f, 1.0f),
        *mMaterial, denstiy);

    if (aCubeActor == nullptr)
    {
        std::cout << "PHYSX ERROR!!: create aCubeActor failed!" << std::endl;
        return -1;
    }
   // mScene->addActor(*aCubeActor);
    
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

void CPhysx::addDynamicTriangleMeshInstance(const physx::PxTransform& transform, physx::PxTriangleMesh* mesh)
{
    //dyn = mPhysics->createRigidDynamic(transform);

    //dyn->setLinearDamping(0.2f);
    //dyn->setAngularDamping(0.1f);
    //physx::PxTriangleMeshGeometry geom;//물체의 기하 구조
    //geom.triangleMesh = mesh;
    //geom.scale = physx::PxVec3(0.1f, 0.1f, 0.1f);

    //dyn->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_GYROSCOPIC_FORCES, true);
    //dyn->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD, true);

    //physx::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(*dyn, geom, *mMaterial, physx::PxShapeFlag::eTRIGGER_SHAPE);
    //shape->setContactOffset(0.1f);
    //shape->setRestOffset(0.02f);

    //physx::PxReal density = 100.f;
    //physx::PxRigidBodyExt::updateMassAndInertia(*dyn, density);

    //mScene->addActor(*dyn);

    //dyn->setSolverIterationCounts(50, 1);
    //dyn->setMaxDepenetrationVelocity(5.f);

    physx::PxRigidDynamic* dyn= mPhysics->createRigidDynamic(transform);
    physx::PxShape* meshShape, * convexShape;
    if (dyn)
    {
        dyn->setRigidBodyFlag(physx::PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, true);
       // meshActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::el, true);
       // meshActor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);

        physx::PxTriangleMeshGeometry triGeom;
        triGeom.triangleMesh = mesh;
        meshShape = physx::PxRigidActorExt::createExclusiveShape(*dyn, triGeom,
            *mMaterial);
        mScene->addActor(*dyn);
        /*physx::PxConvexMeshGeometry convexGeom = physx::PxConvexMeshGeometry();
        meshShape = physx::PxRigidActorExt::createExclusiveShape(*dyn, convexGeom,
            *mMaterial);*/
    }
    dyns.push_back(dyn);
}
void CPhysx::addDynamicTriangleMeshInstancemove(const physx::PxTransform& transform, physx::PxTriangleMesh* mesh)
{
    //dyn = mPhysics->createRigidDynamic(transform);

    //dyn->setLinearDamping(0.2f);
    //dyn->setAngularDamping(0.1f);
    //physx::PxTriangleMeshGeometry geom;//물체의 기하 구조
    //geom.triangleMesh = mesh;
    //geom.scale = physx::PxVec3(0.1f, 0.1f, 0.1f);

    //dyn->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_GYROSCOPIC_FORCES, true);
    //dyn->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD, true);

    //physx::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(*dyn, geom, *mMaterial, physx::PxShapeFlag::eTRIGGER_SHAPE);
    //shape->setContactOffset(0.1f);
    //shape->setRestOffset(0.02f);

    //physx::PxReal density = 100.f;
    //physx::PxRigidBodyExt::updateMassAndInertia(*dyn, density);

    //mScene->addActor(*dyn);

    //dyn->setSolverIterationCounts(50, 1);
    //dyn->setMaxDepenetrationVelocity(5.f);

    physx::PxRigidDynamic* dyn = mPhysics->createRigidDynamic(transform);
    physx::PxShape* meshShape, * convexShape;
    if (dyn)
    {
        dyn->setActorFlag(physx::PxActorFlag::eVISUALIZATION, true);
        // meshActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::el, true);
        // meshActor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);

        physx::PxTriangleMeshGeometry triGeom;
        triGeom.triangleMesh = mesh;
        meshShape = physx::PxRigidActorExt::createExclusiveShape(*dyn, triGeom,
            *mMaterial);
        mScene->addActor(*dyn);
        /*physx::PxConvexMeshGeometry convexGeom = physx::PxConvexMeshGeometry();
        meshShape = physx::PxRigidActorExt::createExclusiveShape(*dyn, convexGeom,
            *mMaterial);*/
    }
    dyns.push_back(dyn);
}

void CPhysx::UpdatePhysics(vector<CObject*> mppObjects)
{
    mScene->simulate(1.0f / 144.0f);
    mScene->fetchResults(true);

    physx::PxVec3 aPos = dyns[0]->getGlobalPose().p;
    physx::PxQuat pxQuat = dyns[0]->getGlobalPose().q;

    glm::quat glmQuat = glm::quat(pxQuat.w, pxQuat.x, pxQuat.y, pxQuat.z);

    glm::vec3 euler = glm::eulerAngles(glmQuat);

    mppObjects[0]->SetPosition(vec3( aPos.x, aPos.y, aPos.z));
    mppObjects[0]->SetinitRotate(glm::vec3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z)));

    aPos = dyns[1]->getGlobalPose().p;
    pxQuat = dyns[1]->getGlobalPose().q;

    glmQuat = glm::quat(pxQuat.w, pxQuat.x, pxQuat.y, pxQuat.z);

    euler = glm::eulerAngles(glmQuat);

    mppObjects[1]->SetPosition(vec3(aPos.x, aPos.y, aPos.z));
    mppObjects[1]->SetinitRotate(glm::vec3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z)));
}

physx::PxTriangleMesh* CPhysx::CreateTriangleMesh(CObject* Object)
{
    std::vector<physx::PxVec3> cVerts;
    std::vector<physx::PxU32> cInds;

    //Drawable* drw = dynamic_cast<Drawable*>(gm);

    for (int i = 0; i < Object->m_pMesh->m_vVertices.size(); i++)
    {

        cVerts.push_back(physx::PxVec3(Object->m_pMesh->m_vVertices[i].m_xmf3Coordinate.x, Object->m_pMesh->m_vVertices[i].m_xmf3Coordinate.y, Object->m_pMesh->m_vVertices[i].m_xmf3Coordinate.z));
    }

    for (int i = 0; i < Object->m_pMesh->m_nindices.size(); i++)
    {
        cInds.push_back(Object->m_pMesh->m_nindices[i]);
    }

    physx::PxTriangleMeshDesc meshDesc;
    meshDesc.points.count = static_cast<physx::PxU32>(cVerts.size());
    meshDesc.points.stride = sizeof(physx::PxVec3);
    meshDesc.points.data = &cVerts[0];

    meshDesc.triangles.count = static_cast<physx::PxU32>(cInds.size() / 3);
    meshDesc.triangles.stride = 3 * sizeof(physx::PxU32);
    meshDesc.triangles.data = &cInds[0];

    physx::PxDefaultMemoryOutputStream writeBuffer;
    physx::PxTriangleMeshCookingResult::Enum result;
    bool status =PxCookTriangleMesh(*Pxcooking,meshDesc, writeBuffer, &result);
      // bool status = rbDesc.mCooking->cookTriangleMesh(meshDesc, writeBuffer, &result);

       if (!status)
       {
       	std::cout << "PHYSX ERROR!!: cookTriangleMesh failed!" << std::endl;
       	return nullptr;
       }

    physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
    return mPhysics->createTriangleMesh(readBuffer);
}
