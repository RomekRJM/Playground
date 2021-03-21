package rjm.romek.finance;

import javax.money.Monetary;
import rjm.romek.finance.monetary.SimpleMonetaryAmount;

public class MonetaryUtil {
  public static SimpleMonetaryAmount getDollars(Integer amount) {
    return new SimpleMonetaryAmount(Monetary.getDefaultAmountFactory()
        .setCurrency(Monetary.getCurrency("USD"))
        .setNumber(amount)
        .create());
  }
}
