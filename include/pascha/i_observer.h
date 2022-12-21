#ifndef PASCHA_I_OBSERVER_H
#define PASCHA_I_OBSERVER_H

#include "date.h"
#include "output_date.h"

#include <string_view>

namespace pascha
{

class IObserver
{
 public:
  virtual ~IObserver() = default;
  // Used to receive date outputs (e.g. from the model).
  virtual void update(const OutputDate&) = 0;
  // Used to receive number of week updates (e.g. from the model).
  virtual void update(Weeks) = 0;
  // Used to receive number of day updates (e.g. from the model).
  virtual void update(Days) = 0;
  // Used to receive string messages, such as errors.
  virtual void update(std::string_view) = 0;
}; // class IObserver

} // namespace pascha

#endif // !PASCHA_I_OBSERVER_H_20221215
