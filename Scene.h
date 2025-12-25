<<<<<<< HEAD
﻿ // Scene.h
=======
// Scene.h
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
#pragma once
#include <vector>
#include "SceneObject.h"

class Scene {
private:
    std::vector<SceneObject*> objects;

public:
    Scene() {}

    ~Scene() {
        for (auto obj : objects) {
            delete obj;
        }
        objects.clear();
    }

    void addObject(SceneObject* object) {
        objects.push_back(object);
    }

    void removeObject(SceneObject* object) {
        auto it = std::find(objects.begin(), objects.end(), object);
        if (it != objects.end()) {
            delete* it;
            objects.erase(it);
        }
    }

    const std::vector<SceneObject*>& getObjects() const {
        return objects;
    }

    SceneObject* getObject(size_t index) {
        if (index < objects.size()) {
            return objects[index];
        }
        return nullptr;
    }
};