//
// klasa Package
//

#ifndef LAB10_PACKAGE_HPP
#define LAB10_PACKAGE_HPP

#include <set>

using ElementID = int;

class Package {
public:
    Package();
    Package(Package& p){ id_ = p.id_;};
    Package(Package&& p);
    //tego nie wiem jak zrobić
   // Package& operator=(Package&& p);
    ElementID get_id() const {return id_;}
    ~Package();

private:
    ElementID id_=0;
    _inline static ElementID id;
    _inline static std::set<ElementID> assigned_IDs_;
    _inline static std::set<ElementID> freed_IDs_;

};


#endif //LAB10_PACKAGE_HPP
