#include "system_icon.hpp"

template <>
void SystemIconAsyncWorker<ExtensionTag>::Execute()
{
  // Do nothing.
}

template <>
void SystemIconAsyncWorker<PathTag>::Execute()
{
  // Do nothing.
}
