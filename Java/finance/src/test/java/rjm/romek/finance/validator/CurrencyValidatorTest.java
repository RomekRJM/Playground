package rjm.romek.finance.validator;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertThrows;

import javax.money.MonetaryAmount;
import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryDateUtil;

class CurrencyValidatorTest {

  private final MonetaryAmount dollars = MonetaryDateUtil.getDollars(123).getMonetaryAmount();
  private final MonetaryAmount euros = MonetaryDateUtil.getSimpleMonetaryAmount("EUR", 123)
      .getMonetaryAmount();

  @Test
  public void shouldPassValidation() {
    assertDoesNotThrow(() -> CurrencyValidator.validate(dollars, dollars));
  }

  @Test
  public void shouldFailValidation() {
    assertThrows(IllegalArgumentException.class, () -> CurrencyValidator.validate(dollars, euros));
  }
}