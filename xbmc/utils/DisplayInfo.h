/*
 *  Copyright (C) 2023 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

struct di_info;
struct di_cta_hdr_static_metadata_block;

namespace KODI
{
namespace UTILS
{

enum class Eotf
{
  TRADITIONAL_SDR,
  TRADITIONAL_HDR,
  PQ,
  HLG,
};

class CDisplayInfo
{
public:
  static std::unique_ptr<CDisplayInfo> Create(const std::vector<uint8_t>& edid);

  ~CDisplayInfo();

  bool SupportsHDRStaticMetadataType1() const;

  bool SupportsEOTF(Eotf eotf) const;

private:
  explicit CDisplayInfo(const std::vector<uint8_t>& edid);

  bool IsValid() const;
  void Parse();
  void LogInfo() const;

  struct DiInfoDeleter
  {
    void operator()(di_info* p);
  };

  std::unique_ptr<di_info, DiInfoDeleter> m_info;

  std::string m_make;
  std::string m_model;

  const di_cta_hdr_static_metadata_block* m_hdr_static_metadata = nullptr;
};

} // namespace UTILS
} // namespace KODI
