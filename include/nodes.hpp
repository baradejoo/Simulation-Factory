//
// Created by Kamil Baradziej on 28/12/2019.
//

#ifndef FABRYKA_NODES_HPP
#define FABRYKA_NODES_HPP

#include <map>
#include <memory>
#include <optional>
#include <functional>
#include "package.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"


enum class ReceiverType{
    Ramp, Worker, Storehouse
};

class IPackageReceiver{
public:
    using pacReceiverIt = std::list<Package>::const_iterator;

    virtual void receive_package(Package&& prod) = 0;
    virtual ReceiverType get_receiver_type() const = 0;
    virtual ElementID get_id() const = 0;

    virtual pacReceiverIt begin() = 0;
    virtual const pacReceiverIt cbegin() = 0;
    virtual pacReceiverIt end() = 0;
    virtual const pacReceiverIt cend() = 0;

    virtual ~IPackageReceiver() {};
};

class Worker : public IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    Worker(const Worker&) = delete;
    Worker& operator=(Worker&) = delete;

    void do_work(Time t) { t_ = t; }
    TimeOffset get_processing_duration() const {return pd_; };
    Time get_package_processing_start_time() const { return t_; }

    ReceiverType get_receiver_type() const override { return rec_tp; }
    ElementID  get_id() const override { return id_; }
    void receive_package(Package&& prod) override;

    ~Worker() = default;

private:
    ElementID id_;
    TimeOffset pd_;
    Time t_;
    std::unique_ptr<PackageQueue> q_;
    std::optional<Package> WorkerBuffer = std::nullopt;
    ReceiverType rec_tp = ReceiverType::Worker;
};

class PackageSender {
protected:
    void push_package(Package pack);

public:
    void send_package();
    std::optional<Package> get_sending_buffer();
    ReceiverPreferences receiver_preferences_;

private:
    std::optional<Package> PackageSenderBuffor = std::nullopt;

};

class Ramp : public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}

    void deliver_goods(Time t) { t_ = t;};
    TimeOffset get_delivery_interval() const { return di_; }
    ElementID get_id() const {return id_; }

    ~Ramp() = default;

private:
    ElementID id_;
    TimeOffset di_;
    Time t_;
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
