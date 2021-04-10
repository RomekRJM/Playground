package rjm.romek.finance.rule;

import javax.money.MonetaryAmount;
import lombok.NoArgsConstructor;
import rjm.romek.finance.monetary.SimpleMonetaryAmount;
import rjm.romek.finance.validator.CurrencyValidator;

@NoArgsConstructor
public class PriceBelowRule extends Rule {

  public PriceBelowRule(SimpleMonetaryAmount targetValue) {
    super(targetValue);
  }

  @Override
  public boolean applies(MonetaryAmount value) {
    assert targetValue != null;
    CurrencyValidator.validate(targetValue.getMonetaryAmount(), value);
    return value.isLessThan(targetValue.getMonetaryAmount());
  }
}
