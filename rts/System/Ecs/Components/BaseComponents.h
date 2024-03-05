/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef BASE_COMPONENTS_H__
#define BASE_COMPONENTS_H__

#include "System/Ecs/EcsMain.h"

template<class T>
struct BasicComponentType {
    T value = 0;
};

template<>
struct BasicComponentType<entt::entity> {
    entt::entity value{entt::null};
};

struct DoubleLinkedChain {
	DoubleLinkedChain() {}

	DoubleLinkedChain(entt::entity initPrev, entt::entity initNext)
		: prev(initPrev), next(initNext) {}

    entt::entity prev{entt::null};
    entt::entity next{entt::null};
};

#define ALIAS_COMPONENT_DEF(Component, T, DefaultValue) \
struct Component : public BasicComponentType<T> { \
    Component(){ value = DefaultValue; } \
    Component(T val){ value = val; } \
    ~Component() = default; \
    Component(const Component &) = default; \
    Component& operator=(const Component &) = default; \
    Component(Component &&) = default; \
    Component& operator=(Component &&) = default; \
};
#define ALIAS_COMPONENT(Component, T) struct Component : public BasicComponentType<T> {};
#define VOID_COMPONENT(Component) struct Component {};

#define DOUBLE_LINKED_LIST_COMPONENT(Component) \
struct Component : public DoubleLinkedChain { \
    Component() = default; \
    Component(entt::entity initPrev, entt::entity initNext) \
        : DoubleLinkedChain(initPrev, initNext) {} \
    ~Component() = default; \
    Component(const Component &) = default; \
    Component& operator=(const Component &) = default; \
    Component(Component &&) = default; \
    Component& operator=(Component &&) = default; \
};

#endif