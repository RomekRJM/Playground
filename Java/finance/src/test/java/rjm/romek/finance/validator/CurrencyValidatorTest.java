package rjm.romek.finance.validator;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertThrows;

import javax.money.MonetaryAmount;
import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryUtil;

class CurrencyValidatorTest {

  private final MonetaryAmount dollars = MonetaryUtil.getDollars(123).getMonetaryUnit();
  private final MonetaryAmount euros = MonetaryUtil.getSimpleMonetaryAmount("EUR", 123)
      .getMonetaryUnit();

  @Test
  public void shouldPassValidation() {
    assertDoesNotThrow(() -> CurrencyValidator.validate(dollars, dollars));
  }

  @Test
  public void shouldFailValidation() {
    assertThrows(IllegalArgumentException.class, () -> CurrencyValidator.validate(dollars, euros));
  }
}