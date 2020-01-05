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

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    ReceiverPreferences(ProbabilityGenerator pg) {ProbabilityGenerator random_generator = pg;};

    //ReceiverPreferences( preferences_t preferences_list): preferences_list_(preferences_list) {}

//    const_iterator begin() = { return preferences_list_.begin(); };
//    const const_iterator cbegin() = { return preferences_list_.cbegin(); };
//    const_iterator end() = { return preferences_list_.end(); };
//    const const_iterator cend() = { return preferences_list_.cend(); };


private:
    preferences_t preferences_list_;
    ProbabilityGenerator pg;
};

class PackageSender {
protected:
    void push_package(Package pack);

public:
    void send_package();
    std::optional<Package> get_sending_buffer() { return std::move(PackageSenderBuffor); }
    ReceiverPreferences preferences_list_;

private:
    std::optional<Package> PackageSenderBuffor = std::nullopt;

};



class Worker : public IPackageReceiver, public PackageSender{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}

    Worker(const Worker&) = delete;
    Worker& operator=(Worker&) = delete;

    void do_work(Time t);
    TimeOffset get_processing_duration() const {return pd_; };
    Time get_package_processing_start_time() const { return t_; }

    ReceiverType get_receiver_type() const override { return rec_tp; }
    ElementID  get_id() const override { return id_; }
    void receive_package(Package&& prod) override;

    pacReceiverIt begin() override { return q_->begin(); }
    const pacReceiverIt cbegin() override { return q_->cbegin(); }
    pacReceiverIt end() override { return q_->end(); }
    const pacReceiverIt cend() override { return q_->cend(); }

    ~Worker() = default;

private:
    ElementID id_;
    TimeOffset pd_;
    Time t_ = 0;
    std::unique_ptr<PackageQueue> q_ = nullptr;
    std::optional<Package> WorkerBuffer = std::nullopt;
    ReceiverType rec_tp = ReceiverType::Worker;
};


class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) : id_(id), d_(std::move(d)) {}

    ReceiverType get_receiver_type() const override { return rec_tp; }
    ElementID get_id() const override { return id_; }
    void receive_package(Package &&prod) override { prod.get_id(); };

    pacReceiverIt begin() override { return d_->begin(); };
    const pacReceiverIt cbegin() override { return d_->cbegin(); };
    pacReceiverIt end() override { return d_->end(); };
    const pacReceiverIt cend() override { return d_->cend(); };

    ~Storehouse() = default;

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
    ReceiverType rec_tp = ReceiverType::Storehouse;

};


class Ramp : public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}

    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const { return di_; }
    ElementID  get_id() const { return id_; }

    ~Ramp() = default;

private:
    ElementID id_;
    TimeOffset di_;
};


#endif //FABRYKA_NODES_HPP