// 42: Burda (302827), Baradziej (302819), Bytnar (297074)

#ifndef NET_SIMULATION_NODES_HPP
#define NET_SIMULATION_NODES_HPP

#include <optional>
#include <map>
#include <memory>
#include "storage_types.hpp"
#include "package.hpp"
#include "types.hpp"
#include "helpers.hpp"
#include "config.hpp"

//============ ReceiverType ===========//

enum class ReceiverType {
    Ramp, Worker, Storehouse
};

//=====================================//
//========== IPackageReceiver =========//

class IPackageReceiver {
public:
    using pacReceiverIt = std::list<Package>::const_iterator;

    virtual void receive_package(Package &&package) = 0;

    virtual ReceiverType get_receiver_type() const = 0; // TODO in FACTORY

    virtual ElementID get_id() const = 0;

    //virtual ~IPackageReceiver() {};
};

//=====================================//
//======== ReceiverPreferences ========//

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver *, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;

    ReceiverPreferences(ProbabilityGenerator probability_function = probability_generator) : probability_generator_(
            probability_function) {}

    void add_receiver(IPackageReceiver *r);

    void remove_receiver(IPackageReceiver *r);

    IPackageReceiver *choose_receiver();

//    const preferences_t &get_preferences() const { return preferences_list_; };
//
//    preferences_t &get_preferences() { return preferences_list_; };
    const preferences_t& get_preferences() const { return preferences_list_; }


    iterator begin(){return preferences_list_.begin();}
    const_iterator cbegin() const {return preferences_list_.cbegin();}
    iterator end(){return preferences_list_.end();}
    const_iterator cend() const {return preferences_list_.cend();}

    preferences_t preferences_list_;

    ~ReceiverPreferences() = default;
private:

    ProbabilityGenerator probability_generator_;
};

//=====================================//
//=========== PackageSender ===========//

class PackageSender {
public:
    PackageSender() = default;
//    PackageSender(const PackageSender&) noexcept ; // TODO Do przemyslenia ...
    PackageSender(PackageSender&&) = default; //TODO dla factory wymagane
//    PackageSender& operator=(const PackageSender&) noexcept ;
//    PackageSender&& operator=(PackageSender&&) noexcept ;

    void send_package();

    std::optional<Package> &get_sending_buffer();

    ReceiverPreferences receiver_preferences_;

    ~PackageSender() = default;
protected:
    void push_package(Package &&package) { package_sender_buffor_ = std::move(package); }

private:
    std::optional<Package> package_sender_buffor_ = std::nullopt;
};

//=====================================//
//============== Worker ===============//

class Worker : public IPackageReceiver, public PackageSender {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q);
    Worker(Worker&&) = default;

    void do_work(Time t);

    TimeOffset get_processing_duration() { return pd_; };

    Time get_package_processing_start_time() const { return t_; }

    //ReceiverType get_receiver_type() const override { return rec_tp; } // TODO in FACTORY
    ReceiverType get_receiver_type() const override { return ReceiverType::Worker;}

    ElementID get_id() const override { return id_; }

    void receive_package(Package &&package) override;

    IPackageStockpile::const_iterator begin() const { return q_->begin(); }
    IPackageStockpile::const_iterator cbegin() const { return q_->cbegin(); }
    IPackageStockpile::const_iterator end() const { return q_->end(); }
    IPackageStockpile::const_iterator cend() const { return q_->cend(); }

//    pacReceiverIt begin() override { return q_->begin(); }
//
//    const pacReceiverIt cbegin() override { return q_->cbegin(); }
//
//    pacReceiverIt end() override { return q_->end(); }
//
//    const pacReceiverIt cend() override { return q_->cend(); }
    ~Worker() = default;

private:
    ElementID id_;
    TimeOffset pd_;
    Time t_ = 0;
    std::unique_ptr<PackageQueue> q_;
    std::optional<Package> worker_buffer_ = std::nullopt;
    //ReceiverType rec_tp = ReceiverType::Worker; // TODO in FACTORY
};

//=====================================//
//============= Storehouse ============//

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::FIFO)) : id_(id), d_(std::move(d)) {}
    Storehouse(Storehouse&&) = default;

    //ReceiverType get_receiver_type() const override { return rec_tp; } // TODO in FACTORY
    ReceiverType get_receiver_type() const override { return ReceiverType::Storehouse;}

    ElementID get_id() const override { return id_; }

    void receive_package(Package &&package) override;

    IPackageStockpile::const_iterator cbegin() const  { return d_->cbegin();}
    IPackageStockpile::const_iterator begin() const  { return d_->begin();}
    IPackageStockpile::const_iterator end() const  { return d_->end();}
    IPackageStockpile::const_iterator cend() const  { return d_->cend();}

    ~Storehouse() = default;

//    pacReceiverIt begin() override { return d_->begin(); };
//    const pacReceiverIt cbegin() override { return d_->cbegin(); };
//    pacReceiverIt end() override { return d_->end(); };
//    const pacReceiverIt cend() override { return d_->cend(); };

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
    //ReceiverType rec_tp = ReceiverType::Storehouse; // TODO in FACTORY

};

//=====================================//
//================ Ramp ===============//

class Ramp : public PackageSender {
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}
    Ramp(Ramp&&) = default;

    void deliver_goods(Time t);

    TimeOffset get_delivery_interval() { return di_; }

    ElementID get_id() const { return id_; }

    ~Ramp() = default;
private:
    ElementID id_;
    TimeOffset di_;
};

//=====================================//

#endif //NET_SIMULATION_NODES_HPP

// 42: Burda (302827), Baradziej (302819), Bytnar (297074)