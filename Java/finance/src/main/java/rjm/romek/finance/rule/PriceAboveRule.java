package rjm.romek.finance.rule;

import javax.money.MonetaryAmount;
import rjm.romek.finance.validator.CurrencyValidator;

public class PriceAboveRule extends Rule {

  public PriceAboveRule(MonetaryAmount targetValue) {
    super(targetValue, RuleType.ABOVE_PRICE_POINT);
  }

  @Override
  public boolean applies(MonetaryAmount value) {
    CurrencyValidator.validate(targetValue, value);
    return value.isGreaterThan(targetValue);
  }
}
