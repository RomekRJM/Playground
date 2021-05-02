package rjm.romek.finance.monetary;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import javax.money.MonetaryAmount;
import javax.money.MonetaryException;
import org.junit.jupiter.api.Test;

class GBXConverterTest {
  private GBXConverter converter = new GBXConverter();

  @Test
  public void shouldConvert() {
    MonetaryAmount monetaryAmount = converter.convert("GBX", 2210d);
    assertEquals("GBP", monetaryAmount.getCurrency().getCurrencyCode());
    assertEquals("22.1", monetaryAmount.getNumber().toString());
  }

  @Test
  public void shouldThrowMonetaryException() {
    assertThrows(MonetaryException.class, () -> converter.convert("USD", 2210d));
  }
}