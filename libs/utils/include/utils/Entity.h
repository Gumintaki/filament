/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_UTILS_ENTITY_H
#define TNT_UTILS_ENTITY_H

// FIXME: could we get rid of <functional>
#include <functional>

#include <stdint.h>
#include <stddef.h>

namespace utils {

class Entity {
public:
    // this can be used to create an array of to-be-filled entities (see create())
    Entity() noexcept = default;

    // Entities can be copied
    Entity(const Entity& e) noexcept = default;
    Entity(Entity&& e) noexcept = default;
    Entity& operator=(const Entity& e) noexcept = default;
    Entity& operator=(Entity&& e) noexcept = default;

    // Entities can be compared
    bool operator==(Entity e) const { return e.mIdentity == mIdentity; }
    bool operator!=(Entity e) const { return e.mIdentity != mIdentity; }

    // Entities can be sorted
    bool operator<(Entity e) const { return e.mIdentity < mIdentity; }

    bool isNull() const noexcept {
        return mIdentity == 0;
    }

    uint32_t getId() const noexcept {
        return mIdentity;
    }

    explicit operator bool() const noexcept { return !isNull(); }

    void clear() noexcept  { mIdentity = 0; }

private:
    friend class EntityManager;
    friend class EntityManagerImpl;
    friend struct std::hash<Entity>;
    using Type = uint32_t;

    explicit Entity(Type identity) noexcept : mIdentity(identity) { }

    Type mIdentity = 0;
};

} // namespace utils


namespace std {

template<>
struct hash<utils::Entity> {
    typedef utils::Entity argument_type;
    typedef size_t result_type;
    result_type operator()(argument_type const& e) const {
        return e.getId();
    }
};

} // namespace std

#endif // TNT_UTILS_ENTITY_H
