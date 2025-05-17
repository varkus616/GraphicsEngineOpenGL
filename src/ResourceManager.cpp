//#include "ResourceManager.hpp"
//#include <iostream>
//
//template<typename T>
//ResourceManager<T>::ResourceManager() {
//    resources_.clear();
//    inUse_.clear();
//    generations_.clear();
//}
//
//template<typename T>
//typename ResourceManager<T>::Handle ResourceManager<T>::create(const T& value, const std::string& name) {
//    // Szukamy dost�pnego slotu
//    for (size_t i = 0; i < inUse_.size(); ++i) {
//        if (!inUse_[i]) {
//            inUse_[i] = true;
//            resources_[i] = value;
//            Handle h = Handle{ static_cast<uint32_t>(i), generations_[i] };
//
//            // Je�li podano nazw�, zapisujemy j� w cache
//            if (!name.empty()) {
//                nameToHandle_[name] = h;
//            }
//            return h;
//        }
//    }
//
//    // Je�li nie ma dost�pnego miejsca, rozszerzamy
//    resources_.push_back(value);
//    inUse_.push_back(true);
//    generations_.push_back(0);
//    Handle h = Handle{ static_cast<uint32_t>(resources_.size() - 1), 0 };
//
//    // Dodanie zasobu do cache
//    if (!name.empty()) {
//        nameToHandle_[name] = h;
//    }
//    return h;
//}
//
//template<typename T>
//T* ResourceManager<T>::get(const Handle& h) {
//    // Sprawdzamy, czy uchwyt jest wa�ny
//    if (h.index >= resources_.size()) return nullptr;
//    if (!inUse_[h.index]) return nullptr;
//    if (generations_[h.index] != h.generation) return nullptr;
//    return &resources_[h.index];
//}
//
//template<typename T>
//T* ResourceManager<T>::getByName(const std::string& name) {
//    // Je�li nie ma zasobu w cache, zwr�� nullptr
//    auto it = nameToHandle_.find(name);
//    if (it == nameToHandle_.end()) {
//        return nullptr;
//    }
//
//    Handle h = it->second;
//    return get(h);
//}
//
//template<typename T>
//void ResourceManager<T>::destroy(const Handle& h) {
//    // Sprawdzamy, czy zas�b mo�na usun��
//    if (h.index >= resources_.size()) return;
//    if (!inUse_[h.index]) return;
//    if (generations_[h.index] != h.generation) return;
//
//    // Usuwamy zas�b, resetujemy dane
//    inUse_[h.index] = false;
//    generations_[h.index]++;
//    resources_[h.index] = T();  // Resetowanie zasobu
//}
//
//template<typename T>
//size_t ResourceManager<T>::capacity() const {
//    return resources_.size();
//}
//
//// Musimy zdefiniowa� szablonowe klasy w pliku �r�d�owym, bo s� templatowane
////template class ResourceManager<int>;  // Przyk�ad dla int
////template class ResourceManager<float>;  // Przyk�ad dla float
////template class ResourceManager<std::string>;  // Przyk�ad dla string
