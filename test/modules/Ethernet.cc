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

#include "./fixtures.hpp"


TEST_F(ModuleTesterData1, Ethernet_simple) {
  const pm::Property* p;

  p = get_property();   // packet #1
  ASSERT_NE(nullptr, p);
  EXPECT_EQ("b8:f6:b1:19:b0:b5", p->value("Ethernet.src").mac());
  EXPECT_EQ("00:00:0c:07:ac:04", p->value("Ethernet.dst").mac());
  EXPECT_EQ(0x800, p->value("Ethernet.type").uint());

  p = get_property(1295);    // packet #1297
  ASSERT_NE(nullptr, p);
  EXPECT_EQ("b8:f6:b1:19:b0:b5", p->value("Ethernet.src").mac());
  EXPECT_EQ("ff:ff:ff:ff:ff:ff", p->value("Ethernet.dst").mac());
  EXPECT_EQ(0x806, p->value("Ethernet.type").uint());
}
