#pragma once

#include <fmt/format.h>
#include <sys/sysinfo.h>
#include "util/chrono.hpp"
#include "ALabel.hpp"

namespace waybar::modules {

class Memory : public ALabel {
  public:
    Memory(const Json::Value&);
    auto update() -> void;
  private:
    waybar::util::SleeperThread thread_;
};

}
