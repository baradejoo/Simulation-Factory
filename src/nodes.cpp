// 42: Burda (302827), Baradziej (302819), Bytnar (297074)

#include "nodes.hpp"

//============= Storehouse - Function definitions =============//

void Storehouse::receive_package(Package &&package) {
    d_->push(std::move(package));
}

//=============================================================//
//=========== PackageSender - Function definitions ============//

void PackageSender::send_package() {
    if (package_sender_buffor_) {
        IPackageReceiver *ipackage_receiver_ = receiver_preferences_.choose_receiver();
        ipackage_receiver_->receive_package(std::move(*package_sender_buffor_));
        package_sender_buffor_.reset();
    }
}

std::optional<Package> &PackageSender::get_sending_buffer() {
    return package_sender_buffor_;
}

//=============================================================//
//=============== Worker - Function definitions ===============//

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q) {
    id_ = id;
    pd_ = pd;
    q_ = std::move(q);
}

void Worker::do_work(Time t) {
    if (!(q_->empty()) && !worker_buffer_) {
        worker_buffer_ = q_->pop();
        t_ = t;
    }
    if (t - t_ == pd_ - 1 && worker_buffer_) {
        push_package(std::move(*worker_buffer_));
        worker_buffer_.reset();
    }
}

void Worker::receive_package(Package &&package) {
    q_->push(std::move(package));
}

//=============================================================//
//================ Ramp - Function definitions ================//

void Ramp::deliver_goods(Time t) {
    if (t % di_ == 1) {
        Package package;
        push_package(std::move(package));
    }
}

//=============================================================//
//======= ReceiverPreferences- Function definitions============//

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    double sum_temp = 0.0;
    double pref_temp = 1;
    preferences_list_[r] = pref_temp;

    for (auto &item : preferences_list_) {
        preferences_list_[item.first] = 1.0 / preferences_list_.size();
        sum_temp += item.second;
    }

    if (sum_temp != 1.0) {
        preferences_list_[r] = preferences_list_[r] + 1.0 - sum_temp;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    double sum_temp = 0.0;
    preferences_list_.erase(r);
    IPackageReceiver *temp = r;

    for (const auto &item: preferences_list_) {
        preferences_list_[item.first] = 1.0 / preferences_list_.size();
        sum_temp += item.second;
        temp = item.first;
    }

    if (sum_temp != 1.0) {
        preferences_list_[temp] = preferences_list_[temp] + 1.0 - sum_temp;
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    double number = probability_generator_();
    double sum = 0.0;
    preferences_t::reverse_iterator iter;
    preferences_t::reverse_iterator rbegin_it = preferences_list_.rbegin();
    preferences_t::reverse_iterator rend_it = preferences_list_.rend();

    IPackageReceiver *temp = rbegin_it->first;
    for (iter = rbegin_it; iter != rend_it; ++iter) {
        sum += iter->second;
        temp = iter->first;
        if (number < sum) {
            break;
        }
    }
    return temp;
}

// 42: Burda (302827), Baradziej (302819), Bytnar (297074)



