#pragma once
#include "renderer/core/CoreStd.h"

#undef __SSE__ //undefine it since variables of type __m128 are automatically aligned on 16-byte boundaries, result in incorrectly mapping to shared memory.
#include "bindings/dop/ArrayPool.h"
#include "bindings/dop/BufferPool.h"
#include "bindings/dop/ObjectPool.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace cc {
namespace gfx {
class DescriptorSet;
}

namespace pipeline {
struct RenderingSubMesh;
struct FlatBuffer;
class RenderPipeline;

struct CC_DLL ModelView {
    uint32_t enabled = 0;
    uint32_t visFlags = 0;
    uint32_t castShadow = 0;
    uint32_t worldBoundsID = 0; // aabb
    uint32_t nodeID = 0;
    uint32_t transformID = 0;
    uint32_t subModelsID = 0; // array pool id
    //    InstancedAttributeBlock instancedAttributeBlock;

    const static se::PoolType type;
};

struct CC_DLL SubModelView {
    uint32_t priority = 0;
    uint32_t passCount = 0;
    uint32_t pass0ID = 0;
    uint32_t pass1ID = 0;
    uint32_t pass2ID = 0;
    uint32_t pass3ID = 0;
    uint32_t shader0ID = 0;
    uint32_t shader1ID = 0;
    uint32_t shader2ID = 0;
    uint32_t shader3ID = 0;
    uint32_t descriptorSetID = 0;
    uint32_t inputAssemblerID = 0;

    const static se::PoolType type;
};

struct CC_DLL PassView {
    uint32_t priority = 0;
    uint32_t stage = 0;
    uint32_t phase = 0;
    uint32_t batchingScheme = 0;
    uint32_t primitive = 0;
    uint32_t dynamicState = 0;
    uint32_t hash = 0;
    uint32_t rasterizerStateID = 0;
    uint32_t depthStencilStateID = 0;
    uint32_t blendStateID = 0;
    uint32_t descriptorSetID = 0;
    uint32_t pipelineLayoutID = 0;

    const static se::PoolType type;
};

//
//struct CC_DLL InstancedAttributeBlock {
//    uint32_t bufferViewID = 0;
//    uint32_t bufferViewSize = 0;
//
//    uint32_t instancedAttributesID = 0; //array pool
//};

class CC_DLL Camera {
private:
    uint32_t width = 0;
    uint32_t height = 0;
    float exposure = 0;
    uint32_t clearFlag = 0;
    float clearDepth = 0;
    uint32_t clearStencil = 0;
    uint32_t nodeID = 0;
    uint32_t sceneID = 0;
    uint32_t frustumID = 0;
    cc::Vec3 forward;
    cc::Vec3 position;
    uint32_t viewportX;
    uint32_t viewportY;
    uint32_t viewportWidth;
    uint32_t viewportHeight;
    gfx::Color clearColor;
    cc::Mat4 matView;
    cc::Mat4 matViewProj;
    cc::Mat4 matViewProjInv;
    cc::Mat4 matProj;
    cc::Mat4 matProjInv;

public:
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }
    float getExposure() const { return exposure; }
    float getClearDepth() const { return clearDepth; }
    uint32_t getClearFlag() const { return clearFlag; }
    float getClearStencil() const { return clearStencil; }
    uint32_t getNodeID() const { return nodeID; }
    uint32_t getSceneID() const { return sceneID; }
    uint32_t getFrustumID() const { return frustumID; }
    uint32_t getViewportX() const { return viewportX; }
    uint32_t getViewportY() const { return viewportY; }
    uint32_t getViewportWidth() const { return viewportWidth; }
    uint32_t getViewportHeight() const { return viewportHeight; }
    const cc::Vec3 &getForward() const { return forward; }
    const cc::Vec3 &getPosition() const { return position; }
    const gfx::Color &getClearColor() const { return clearColor; }
    const cc::Mat4 &getMatView() const { return matView; }
    const cc::Mat4 &getMatViewProj() const { return matViewProj; }
    const cc::Mat4 &getMatViewProjInv() const { return matViewProjInv; }
    const cc::Mat4 &getMatProj() const { return matProj; }
    const cc::Mat4 &getMatProjInv() const { return matProjInv; }

    const static se::PoolType type;
};

struct CC_DLL AABB {
    cc::Vec3 center;
    cc::Vec3 halfExtents;

    const static se::PoolType type;
};

struct CC_DLL Plane {
    cc::Vec3 normal;
    float distance;
};

struct CC_DLL Frustum {
    cc::Vec3 vertices[8];
    Plane planes[6];

    const static se::PoolType type;
};

struct CC_DLL Scene {
    uint32_t mainLightID = 0;
    uint32_t modelsID = 0; //array pool

    const static se::PoolType type;
};

struct CC_DLL Light {
    uint32_t useColorTemperature = 0;
    float illuminance = 0;
    uint32_t nodeID = 0;
    cc::Vec3 direction;
    cc::Vec3 color;
    cc::Vec3 colorTemperatureRGB;

    const static se::PoolType type;
};

struct CC_DLL Ambient {
    float enabled = 0;
    float skyIllum = 0;
    cc::Vec4 skyColor;
    cc::Vec4 groundAlbedo;

    const static se::PoolType type;
};

struct CC_DLL Fog {
    uint32_t enabled = 0;
    uint32_t fogType = 0;
    float fogDensity = 0;
    float fogStart = 0;
    float fogEnd = 0;
    float fogAtten = 0;
    float fogTop = 0;
    float fogRange = 0;
    cc::Vec4 fogColor;

    const static se::PoolType type;
};

struct CC_DLL Shadows {
    uint32_t enabled = 0;
    uint32_t shadowType = 0;
    float distance = 0;
    uint32_t instancePass = 0;
    uint32_t planarPass = 0;
    float nearValue = 0;
    float farValue = 0;
    float aspect = 0;
    uint32_t pcfType = 0;
    uint32_t dirty = 0;
    uint32_t orthoSize = 0;
    cc::Vec2 size;
    cc::Vec3 normal;
    cc::Vec4 color;
    cc::Vec4 sphere;

    const static se::PoolType type;
};

struct CC_DLL InstancedAttribute {
    uint32_t nameID = 0;
    uint32_t format = 0;
    uint32_t isNormalized = 0;
    uint32_t viewID = 0;

    const static se::PoolType type;
};

struct CC_DLL Skybox {
    uint32_t enabled = 0;
    uint32_t isRGBE = 0;
    uint32_t useIBL = 0;
    uint32_t model = 0;

    const static se::PoolType type;
};

struct CC_DLL BufferView {
    uint8_t *data = nullptr;

    const static se::PoolType type;
};

struct CC_DLL FlatBuffer {
    uint32_t stride = 0;
    uint32_t count = 0;
    uint32_t bufferViewID = 0;
    uint32_t bufferViewSize = 0;

    const static se::PoolType type;
};

struct CC_DLL RenderingSubMesh {
    uint32_t vertexBuffersID = 0;

    uint32_t attributesID = 0;

    uint32_t flatBuffersID = 0;

    uint32_t primitiveMode = 0;
    uint32_t indexBufferID = 0;
    uint32_t indirectBufferID = 0;
    uint32_t meshID = 0;
    uint32_t subMeshIndex = 0;

    const static se::PoolType type;
};

class CC_DLL Node {
private:
    uint32_t layer = 0;
    cc::Vec3 worldScale;
    cc::Vec3 worldPosition;
    cc::Vec4 worldRotation;
    cc::Mat4 worldMatrix;

public:
    uint getLayer() const { return layer; }
    const cc::Vec3 &getWorldScale() const { return worldScale; }
    const cc::Vec3 &getWorldPosition() const { return worldPosition; }
    const cc::Vec4 &getWorldRotation() const { return worldRotation; }
    const cc::Mat4 &getWorldMatrix() const { return worldMatrix; }

    const static se::PoolType type;
};

struct CC_DLL Root {
    float cumulativeTime = 0;
    float frameTime = 0;

    const static se::PoolType type;
};

struct CC_DLL RenderWindow {
    uint32_t hasOnScreenAttachments = 0;
    uint32_t hasOffScreenAttachments = 0;
    uint32_t framebufferID = 0;

    const static se::PoolType type;
};

//Get buffer pool data
#define GET_SUBMODEL(index) SharedMemory::getBuffer<SubModelView>(index)
#define GET_PASS(index)     SharedMemory::getBuffer<PassView>(index)
#define GET_MODEL(index)    SharedMemory::getBuffer<ModelView>(index)

#define GET_INSTANCE_ATTRIBUTE(index, offset) (SharedMemory::getBuffer<InstancedAttribute>(index) + offset)
#define GET_RENDER_SUBMESH(index)             SharedMemory::getBuffer<RenderingSubMesh>(index)
#define GET_FLAT_BUFFER(index, offset)        (SharedMemory::getBuffer<FlatBuffer>(index) + offset)
#define GET_BUFFERVIEW(index)                 SharedMemory::getBuffer<BufferView>(index)
#define GET_NODE(index)                       SharedMemory::getBuffer<Node>(index)
#define GET_ROOT()                            SharedMemory::getBuffer<Root>(se::BufferPool::getPoolFlag())
#define GET_CAMERA(index)                     SharedMemory::getBuffer<Camera>(index)
#define GET_SCENE(index)                      SharedMemory::getBuffer<Scene>(index)
#define GET_LIGHT(index)                      SharedMemory::getBuffer<Light>(index)
#define GET_AMBIENT(index)                    SharedMemory::getBuffer<Ambient>(index)
#define GET_FOG(index)                        SharedMemory::getBuffer<Fog>(index)
#define GET_SKYBOX(index)                     SharedMemory::getBuffer<Skybox>(index)
#define GET_FRUSTUM(index)                    SharedMemory::getBuffer<Frustum>(index)
#define GET_AABB(index)                       SharedMemory::getBuffer<AABB>(index)
#define GET_WINDOW(index)                     SharedMemory::getBuffer<RenderWindow>(index)
#define GET_SHADOWS(index)                    SharedMemory::getBuffer<Shadows>(index)

//TODO
#define GET_NAME(index) (String(0))

//Get object pool data
#define GET_DESCRIPTOR_SET(index)      SharedMemory::getObject<gfx::DescriptorSet, se::PoolType::DESCRIPTOR_SETS>(index)
#define GET_IA(index)                  SharedMemory::getObject<gfx::InputAssembler, se::PoolType::INPUT_ASSEMBLER>(index)
#define GET_SHADER(index)              SharedMemory::getObject<gfx::Shader, se::PoolType::SHADER>(index)
#define GET_RASTERIZER_STATE(index)    SharedMemory::getObject<gfx::RasterizerState, se::PoolType::RASTERIZER_STATE>(index)
#define GET_DEPTH_STENCIL_STATE(index) SharedMemory::getObject<gfx::DepthStencilState, se::PoolType::DEPTH_STENCIL_STATE>(index)
#define GET_BLEND_STATE(index)         SharedMemory::getObject<gfx::BlendState, se::PoolType::BLEND_STATE>(index)
#define GET_FRAMEBUFFER(index)         SharedMemory::getObject<gfx::Framebuffer, se::PoolType::FRAMEBUFFER>(index)
#define GET_PIPELINE_LAYOUT(index)     SharedMemory::getObject<gfx::PipelineLayout, se::PoolType::PIPELINE_LAYOUT>(index)

//Get array pool data
#define GET_MODEL_ARRAY(index)    SharedMemory::getArray(se::PoolType::MODEL_ARRAY, index)
#define GET_SUBMODEL_ARRAY(index) SharedMemory::getArray(se::PoolType::SUB_MODEL_ARRAY, index)
#define GET_PLANE_ARRAY(index)    (static_cast<uint32_t *>(0))

class CC_DLL SharedMemory : public Object {
public:
    template <typename T>
    static T *getBuffer(uint index) {
        const auto &bufferMap = se::BufferPool::getPoolMap();
        if (bufferMap.count(T::type) != 0) {
            const se::BufferPool *bufferPool = bufferMap.at(T::type);
            return bufferPool->getTypedObject<T>(index);
        } else {
            return nullptr;
        }
    }

    template <typename T, se::PoolType p>
    static T *getObject(uint index) {
        const auto &poolMap = se::ObjectPool::getPoolMap();
        if (poolMap.count(p) != 0) {
            const se::ObjectPool *objectPool = poolMap.at(p);
            return objectPool->getTypedObject<T>(index);
        } else {
            return nullptr;
        }
    }

    static uint32_t *getArray(se::PoolType type, uint index) {
        return se::ArrayPool::getArray(type, index);
    }
};

} //namespace pipeline
} //namespace cc
