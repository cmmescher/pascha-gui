#ifndef PASCHA_TARGET_DATES_H
#define PASCHA_TARGET_DATES_H

#include "target_date.h"

namespace pascha
{

class Meatfare : public TargetDate
{
 public:
  Meatfare(std::unique_ptr<ICalculationMethod> calculation_method)
    : TargetDate(std::move(calculation_method), -56) {}
}; // class Meatfare

class Cheesefare : public TargetDate
{
 public:
  Cheesefare(std::unique_ptr<ICalculationMethod> calculation_method)
    : TargetDate(std::move(calculation_method), -49) {}
}; // class Cheesefare

class AshWednesday : public TargetDate
{
 public:
  AshWednesday(std::unique_ptr<ICalculationMethod> calculation_method)
    : TargetDate(std::move(calculation_method), -46) {}
}; // class AshWednesday

class MidfeastPentecost : public TargetDate
{
 public:
  MidfeastPentecost(std::unique_ptr<ICalculationMethod> calculation_method)
    : TargetDate(std::move(calculation_method), 24) {}
}; // class MidfeastPentecost

class LeavetakingPascha : public TargetDate
{
 public:
  LeavetakingPascha(std::unique_ptr<ICalculationMethod> calculation_method)
    : TargetDate(std::move(calculation_method), 38) {}
}; // class LeavetakingPascha

class Ascension : public TargetDate
{
 public:
  Ascension(std::unique_ptr<ICalculationMethod> calculation_method)
    : TargetDate(std::move(calculation_method), 39) {}
}; // class Ascension

class Pentecost : public TargetDate
{
 public:
  Pentecost(std::unique_ptr<ICalculationMethod> calculation_method)
    : TargetDate(std::move(calculation_method), 49) {}
}; // class Pentecost

} // namespace pascha

#endif // !PASCHA_TARGET_DATES_H
