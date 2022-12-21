#ifndef PASCHA_I_VIEW_H
#define PASCHA_I_VIEW_H

#include "i_observer.h"

#include <string_view>

namespace pascha
{

class IView : public IObserver
{
 public:
  virtual ~IView() = default;
  virtual void createView() = 0;
}; // class IView

} // namespace pascha

#endif // !PASCHA_I_VIEW_H
