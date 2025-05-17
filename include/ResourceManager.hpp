// ResourceManager.hpp
#pragma once
#include <vector>
#include <unordered_map>
#include <string>

template<typename T>
class ResourceManager {
public:
    struct Handle {
        uint32_t index;
        uint32_t generation;
        bool isValid() const {
            return index != static_cast<uint32_t>(-1);
        }
        bool operator==(const Handle& other) const {
            return index == other.index && generation == other.generation;
        }
    };

    ResourceManager() = default;

    Handle create(const T& value, const std::string& name = "") {
        for (size_t i = 0; i < inUse_.size(); ++i) {
            if (!inUse_[i]) {
                inUse_[i] = true;
                resources_[i] = value;
                Handle h = { static_cast<uint32_t>(i), generations_[i] };
                if (!name.empty()) nameToHandle_[name] = h;
                return h;
            }
        }
        resources_.push_back(value);
        inUse_.push_back(true);
        generations_.push_back(0);
        Handle h = { static_cast<uint32_t>(resources_.size() - 1), 0 };
        if (!name.empty()) nameToHandle_[name] = h;
        return h;
    }

    T* get(const Handle& h) {
        if (h.index >= resources_.size()) return nullptr;
        if (!inUse_[h.index]) return nullptr;
        if (generations_[h.index] != h.generation) return nullptr;
        return &resources_[h.index];
    }

    T* getByName(const std::string& name) {
        auto it = nameToHandle_.find(name);
        if (it == nameToHandle_.end()) return nullptr;
        return get(it->second);
    }

    void destroy(const Handle& h) {
        if (h.index >= resources_.size()) return;
        if (!inUse_[h.index]) return;
        if (generations_[h.index] != h.generation) return;
        inUse_[h.index] = false;
        generations_[h.index]++;
        resources_[h.index] = T();
    }

    size_t capacity() const {
        return resources_.size();
    }

private:
    std::vector<T> resources_;
    std::vector<bool> inUse_;
    std::vector<uint32_t> generations_;
    std::unordered_map<std::string, Handle> nameToHandle_;
};
