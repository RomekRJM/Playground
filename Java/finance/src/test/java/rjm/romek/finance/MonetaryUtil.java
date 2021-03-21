package rjm.romek.finance;

import javax.money.Monetary;
import rjm.romek.finance.monetary.SimpleMonetaryAmount;

public class MonetaryUtil {
  public static SimpleMonetaryAmount getDollars(Number amount) {
    return getSimpleMonetaryAmount("USD", amount);
  }

  public static SimpleMonetaryAmount getSimpleMonetaryAmount(String currencyCode, Number amount) {
    return new SimpleMonetaryAmount(Monetary.getDefaultAmountFactory()
        .setCurrency(Monetary.getCurrency(currencyCode))
        .setNumber(amount)
        .create());
  }
}
