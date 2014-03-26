#pragma once

class Application final
{
public:
  /// Default constructor (does nothing but initialize default values)
  Application();

  /// Default destructor
  ~Application();

  /// Called to actually run the application
  int Run();
};