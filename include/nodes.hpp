//
// Created by Kamil Baradziej on 28/12/2019.
//

#ifndef FABRYKA_NODES_HPP
#define FABRYKA_NODES_HPP

#include <map>
#include <memory>
#include <optional>
#include <functional>
#include "storage_types.hpp"
#include "helpers.hpp"
#include "config.hpp"

//============ ReceiverType ===========//

enum class ReceiverType{
    Ramp, Worker, Storehouse
};

//=====================================//
//========== IPackageReceiver =========//

class IPackageReceiver{
public:
    using pacReceiverIt = std::list<Package>::const_iterator;

    virtual void receive_package(Package&& package) = 0;
    //virtual ReceiverType get_receiver_type() const = 0; // TODO in FACTORY
    virtual ElementID get_id() const = 0;

    virtual pacReceiverIt begin() = 0;
    virtual const pacReceiverIt cbegin() = 0;
    virtual pacReceiverIt end() = 0;
    virtual const pacReceiverIt cend() = 0;

    virtual ~IPackageReceiver() {};
};

//=====================================//
//======== ReceiverPreferences ========//

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);

    IPackageReceiver* choose_receiver();

    ReceiverPreferences(ProbabilityGenerator probability_generator) { ProbabilityGenerator random_generator = probability_generator;};

    ReceiverPreferences( preferences_t preferences_list): preferences_list_(preferences_list) {}

    iterator begin()  { return preferences_list_.begin(); };
    const const_iterator cbegin()  { return preferences_list_.cbegin(); };
    iterator end()  { return preferences_list_.end(); };
    const const_iterator cend()  { return preferences_list_.cend(); };


private:
    preferences_t preferences_list_;
    ProbabilityGenerator probability_generator_;
};

//=====================================//
//=========== PackageSender ===========//

class PackageSender {
protected:
    void push_package(Package&& package) { package_sender_buffor_=std::move(package); }

public:
    void send_package();
    std::optional<Package> get_sending_buffer();
    ReceiverPreferences preferences_list_;

private:
    std::optional<Package> package_sender_buffor_ = std::nullopt;
};

//=====================================//
//============== Worker ===============//

class Worker : public IPackageReceiver, public PackageSender{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q);

    void do_work(Time t);
    TimeOffset get_processing_duration() {return pd_; };
    Time get_package_processing_start_time() const { return t_; }

    //ReceiverType get_receiver_type() const override { return rec_tp; } // TODO in FACTORY
    ElementID  get_id() const override { return id_; }
    void receive_package(Package&& package) override;

    pacReceiverIt begin() override { return q_->begin(); }
    const pacReceiverIt cbegin() override { return q_->cbegin(); }
    pacReceiverIt end() override { return q_->end(); }
    const pacReceiverIt cend() override { return q_->cend(); }

private:
    ElementID id_;
    TimeOffset pd_;
    Time t_ = 0;
    std::unique_ptr<PackageQueue> q_;
    std::optional<Package> worker_buffer_ = std::nullopt;
    //ReceiverType rec_tp = ReceiverType::Worker; // TODO in FACTORY

//=====================================//
//============= Storehouse ============//

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) : id_(id), d_(std::move(d)) {}

    // ReceiverType get_receiver_type() const override { return rec_tp; } // TODO in FACTORY
    ElementID get_id() const override { return id_; }
    void receive_package(Package && package) override;

//    pacReceiverIt begin() override { return d_->begin(); };
//    const pacReceiverIt cbegin() override { return d_->cbegin(); };
//    pacReceiverIt end() override { return d_->end(); };
//    const pacReceiverIt cend() override { return d_->cend(); };

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
    // ReceiverType rec_tp = ReceiverType::Storehouse; // TODO in FACTORY

};

//=====================================//
//================ Ramp ===============//

class Ramp : public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}

    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() { return di_; }
    ElementID  get_id() const { return id_; }

private:
    ElementID id_;
    TimeOffset di_;
};

//=====================================//

#endif //FABRYKA_NODES_HPP

