#pragma once

#include "types.hh"

namespace nix {

enum class LogFormat {
  raw,
  rawWithLogs,
  internalJSON,
  bar,
};

void setLogFormat(const std::string & logFormatStr);
void setLogFormat(const LogFormat & logFormat);

void createDefaultLogger();

}