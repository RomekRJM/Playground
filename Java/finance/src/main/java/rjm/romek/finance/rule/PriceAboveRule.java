package rjm.romek.finance.rule;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;
import javax.money.MonetaryAmount;
import rjm.romek.finance.monetary.SimpleMonetaryAmount;
import rjm.romek.finance.validator.CurrencyValidator;

public class PriceAboveRule extends Rule {

  @JsonCreator
  public PriceAboveRule(@JsonProperty("targetValue") SimpleMonetaryAmount targetValue) {
    super(targetValue);
  }

  @Override
  public boolean applies(MonetaryAmount value) {
    assert targetValue != null;
    CurrencyValidator.validate(targetValue.getMonetaryAmount(), value);
    return value.isGreaterThan(targetValue.getMonetaryAmount());
  }
}
