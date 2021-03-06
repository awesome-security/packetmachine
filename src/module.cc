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

#include <assert.h>
#include "./module.hpp"
#include "./decoder.hpp"

namespace pm {

void build_module_map(std::map<std::string, Module*> *mod_map) {
#define INSTALL_MOD(CNAME)                                      \
  {                                                             \
    extern Module* __new_module_##CNAME##_factory();            \
    mod_map->insert(std::make_pair(#CNAME, NEW_MODULE(CNAME))); \
  }

  INSTALL_MOD(Ethernet);
  INSTALL_MOD(PPPoE);
  INSTALL_MOD(ARP);
  INSTALL_MOD(IPv4);
  INSTALL_MOD(ICMP);
  INSTALL_MOD(UDP);
  INSTALL_MOD(TCP);
  INSTALL_MOD(TCPSession);
  INSTALL_MOD(DNS);
  INSTALL_MOD(MDNS);
}



ParamDef::ParamDef(const std::string& local_name, Value*(*constructor)()) :
    local_name_(local_name), constructor_(constructor) {
}
ParamDef::~ParamDef() {
}





Module::Module() : dec_(nullptr), id_(Module::NONE) {
}

Module::~Module() {
}

Value* Module::new_value() {
  return new Value();
}
/*
Object* Module::new_array() {
  return new Array();
}
Object* Module::new_map() {
  return new Map();
}
*/

const ParamDef* Module::define_param(const std::string& name,
                                     Value*(*new_object)()) {
  ParamDef *def = new ParamDef(name, new_object);
  this->param_map_.insert(std::make_pair(name, def));
  return def;
}

const EventDef* Module::define_event(const std::string& name) {
  EventDef *def = new EventDef(name);
  this->event_map_.insert(std::make_pair(name, def));
  return def;
}


mod_id Module::lookup_module(const std::string& name) {
  // lookup_module must not be called before set decoder.
  assert(this->dec_);
  return this->dec_->lookup_module(name);
}

param_id Module::lookup_param_id(const std::string& name) {
  assert(this->dec_);
  return this->dec_->lookup_param_id(name);
}

void Module::set_decoder(Decoder* dec) {
  this->dec_ = dec;
}

void Module::set_mod_id(mod_id id) {
  this->id_ = id;
}

void Module::set_name(const std::string& name) {
  this->name_ = name;
}



}   // namespace pm
