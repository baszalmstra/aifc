#pragma once

#include <memory>
#include <string>

class IAIPlugin;
class PluginWrapper final
{
protected:
  PluginWrapper();

  // Called to try and load the plugin
  bool Load(const std::string& path);

public:
  ~PluginWrapper();

  /// Returns the plugin
  IAIPlugin *plugin() { return plugin_.get(); }

public:
  /// Loads a plugin from a given path
  static std::unique_ptr<PluginWrapper> LoadPlugin(const std::string& path);

private:
  void* sharedObject_;
  std::unique_ptr<IAIPlugin> plugin_;
};