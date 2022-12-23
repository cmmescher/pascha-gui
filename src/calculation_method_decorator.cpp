#include "pascha/calculation_method_decorator.h"

namespace pascha
{

CalculationMethodDecorator::CalculationMethodDecorator(std::shared_ptr<ICalculationMethod> calculation_method)
    : m_calculation_method{calculation_method}
{
} // CalculationMethodDecorator::CalculationMethodDecorator

CalculationMethodDecorator::~CalculationMethodDecorator() = default;

} // namespace pascha
