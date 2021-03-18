package rjm.romek.finance;

import javax.money.Monetary;
import javax.money.MonetaryAmount;

public class MonetaryUtil {
  public static MonetaryAmount getDollars(Integer amount) {
    return Monetary.getDefaultAmountFactory()
        .setCurrency(Monetary.getCurrency("USD"))
        .setNumber(amount)
        .create();
  }
}
