package rjm.romek.finance.validator;

import javax.money.MonetaryAmount;

public class CurrencyValidator {
  public static final void validate(MonetaryAmount expected, MonetaryAmount actual) {
    if (actual.getCurrency().equals(expected.getCurrency())) {
      return;
    }

    throw new IllegalArgumentException(String.format("Expected value to be in %s, but got %s.",
        expected.getCurrency(), actual.getCurrency()
    ));
  }
}
