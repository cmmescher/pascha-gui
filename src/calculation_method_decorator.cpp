#include "calculation_method_decorator.h"

namespace pascha
{

CalculationMethodDecorator::CalculationMethodDecorator(std::shared_ptr<ICalculationMethod> calculation_method)
    : m_calculation_method{std::move(calculation_method)}
{
} // CalculationMethodDecorator::CalculationMethodDecorator

} // namespace pascha
