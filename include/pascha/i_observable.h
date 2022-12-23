#ifndef PASCHA_I_OBSERVABLE_H
#define PASCHA_I_OBSERVABLE_H

#include <string_view>

#include "date.h"
#include "i_observer.h"

namespace pascha
{

class IObservable
{
 public:
  virtual ~IObservable() = default;
  virtual void addObserver(IObserver&) = 0;
  virtual void removeObserver(IObserver&) = 0;
  // Used to nofify date outputs from the model.
  virtual void notify(const Date&) const = 0;
  // Used to notify number of week updates from the model.
  virtual void notify(Weeks) const = 0;
  // Used to notify number of day updates from the model.
  virtual void notify(Days) const = 0;
  // Used to notify string messages, such as errors.
  virtual void notify(std::string_view) const = 0;
}; // class IObservable

} // namespace pascha

#endif // !PASCHA_I_OBSERVABLE_H
