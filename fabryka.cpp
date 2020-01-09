#include <cstdlib>
#include <iostream>
#include "storage_types.hpp"
#include "package.hpp"
#include "types.hpp"
#include "nodes.hpp"

int main() {
    PackageQueue q(PackageQueueType::FIFO);
    std::unique_ptr<IPackageStockpile> ptr = std::make_unique<PackageQueue>(q);
    Storehouse s(1, std::move(ptr));
    Ramp r(1,2);
    r.mReceiverPreferences.add_receiver(&s);
    r.deliver_goods(0);
    std::cout<< "Pierwszy z kontenera: " <<s.cbegin()->get_id()<< std::endl;
    r.deliver_goods(1);
    std::cout<< "Pierwszy z kontenera: " <<s.cbegin()->get_id()<< std::endl;

    r.deliver_goods(2);
    std::cout<< "1 z kontenera: " <<s.cbegin()->get_id()<< std::endl;
    std::cout<< "2 z kontenera: " <<s.cend()->get_id()<< std::endl;
    r.deliver_goods(3);
    std::cout<< "1 z kontenera: " <<s.cbegin()->get_id()<< std::endl;
    std::cout<< "2 z kontenera: " <<s.cend()->get_id()<< std::endl;
    r.deliver_goods(4);
    std::cout<< "1 z kontenera: " <<s.cbegin()->get_id()<< std::endl;
    std::cout<< "2 z kontenera: " <<s.cend()->get_id()<< std::endl;
    return 0;
}
