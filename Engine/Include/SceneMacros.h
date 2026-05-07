#pragma once

#define REGISTER_SCENE(ClassName) \
    namespace { \
        std::unique_ptr<Scene> Create##ClassName() { \
            return std::make_unique<ClassName>(); \
        } \
        bool registered_##ClassName = []() { \
            SceneRegistry::Register(Create##ClassName); \
            return true; \
        }(); \
    }