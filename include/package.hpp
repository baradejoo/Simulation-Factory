//
// klasa Package
//

#ifndef LAB10_PACKAGE_HPP
#define LAB10_PACKAGE_HPP

#include <set>
#include "types.hpp"


class Package {
public:
    Package();
    Package(Package&& p);
//    Package& operator=(Package& p);
    ElementID get_id() const {return id_;}
    ~Package();

private:
    ElementID id_=0;
    inline static ElementID id;
    inline static std::set<ElementID> assigned_IDs_;
    inline static std::set<ElementID> freed_IDs_;

};


#endif //LAB10_PACKAGE_HPP
