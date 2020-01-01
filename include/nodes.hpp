//
// Created by Kamil Baradziej on 28/12/2019.
//

#ifndef FABRYKA_NODES_HPP
#define FABRYKA_NODES_HPP

#include <map>
#include "package.hpp"
#include "storage_types.hpp"

enum class ReceiverType{
    Ramp, Worker, Storehouse
};

class IPackageReceiver{
public:
    virtual void receive_package(Package&& p) = 0;
    virtual ReceiverType get_receiver_type() const = 0;
    virtual ElementID get_id() const = 0;

    virtual ~IPackageReceiver() {};
};

class Worker : public IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    Worker(const Worker&) = delete;
    Worker& operator=(Worker&) = delete;

    void do_work(Time t);
    TimeOffset get_processing_duration();
    Time get_package_processing_start_time();

    ReceiverType get_receiver_type() const override { return rec_tp; }
    ElementID  get_id() const override { return id_; }
    void receive_package(Package&& p) override {};

    ~Worker() override = default;

private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<PackageQueue> q_;
    ReceiverType rec_tp = ReceiverType::Worker;

};

class PackageSender {
protected:
    push_package(Package);

public:
    send_package();

    std::optional<Package> get_sending_buffer();

    RecieverPreferences receiver_preferences_

private:


};

class Ramp : public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}

    void deliver_goods(Time t);
    TimeOffset get_delivery_interval();
    ElementID get_id ();



    ~Ramp() = default;

private:
    ElementID id_;
    TimeOffset di_;
};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;


    void add_reciever(IPackageReceiver* r);

    void remove_reciever(IPackageReceiver* r);

    IPackageReceiver* choose_receiver;
private:
    IPackageReceiver* r;
};
#endif //FABRYKA_NODES_HPP
