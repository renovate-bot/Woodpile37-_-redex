/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "Pass.h"
#include "PassManager.h"

/**
 * This pass unmarks some over-strict proguard keep rule so that we can still
 * remove or optimize them.
 * To unmark keep rule like "-keep class * extend xxx" put the superclass
 * in "supercls_list".
 * To unmark keep for a certain class or a certain package, put the class path
 * in "package_list".
 * This pass should be put at beginning of passes list.
 */
class UnmarkProguardKeepPass : Pass {
 public:
  UnmarkProguardKeepPass() : Pass("UnmarkProguardKeepPass") {}

  void bind_config() override {
    bind("supercls_list", {}, m_supercls_list);
    bind("package_list", {}, m_package_list);
  }

  bool is_cfg_legacy() override { return true; }
  void run_pass(DexStoresVector&, ConfigFiles&, PassManager&) override;

 private:
  std::vector<std::string> m_supercls_list;
  std::vector<std::string> m_package_list;
};
