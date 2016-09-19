/*
 * Copyright (c) 2016 Masayoshi Mizutani <mizutani@sfc.wide.ad.jp> All
 * rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PACKETMACHINE_DECODER_HPP__
#define __PACKETMACHINE_DECODER_HPP__

#include <map>
#include <vector>
#include <string>

#include "./module.hpp"
#include "./packetmachine/property.hpp"

namespace pm {

class Module;
class Property;
class Packet;

struct ParamInfo {
  mod_id mod_id_;
  param_id local_id_;
  param_id global_id_;
  std::string name_;
};

class Decoder {
 private:
  std::map<std::string, mod_id> mod_map_;
  std::map<std::string, ParamDef*> param_map_;
  std::vector<ParamDef*> params_;
  std::vector<Module*> modules_;
  mod_id mod_ethernet_;

 public:
  Decoder();
  ~Decoder();
  void decode(Payload* pd, Property* prop);
  mod_id lookup_module(const std::string& name) const;

  size_t param_size() const { return this->params_.size(); }
  param_id lookup_param_id(const std::string& name) const;
  const std::string& lookup_param_name(param_id pid) const;
};

}   // namespace pm

#endif   // __PACKETMACHINE_DECODER_HPP__
