package rjm.romek.finance.rule;

import javax.money.MonetaryAmount;
import lombok.NoArgsConstructor;
import rjm.romek.finance.monetary.SimpleMonetaryAmount;
import rjm.romek.finance.validator.CurrencyValidator;

@NoArgsConstructor
public class PriceBelowRule extends Rule {

  public PriceBelowRule(SimpleMonetaryAmount targetValue) {
    super(targetValue, RuleType.BELOW_PRICE_POINT);
  }

  @Override
  public boolean applies(MonetaryAmount value) {
    assert targetValue != null;
    CurrencyValidator.validate(targetValue.getMonetaryUnit(), value);
    return value.isLessThan(targetValue.getMonetaryUnit());
  }
}
