package rjm.romek.finance.rule;

import javax.money.MonetaryAmount;
import lombok.NoArgsConstructor;
import rjm.romek.finance.validator.CurrencyValidator;

@NoArgsConstructor
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
