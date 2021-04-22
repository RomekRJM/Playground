package rjm.romek.finance.monetary;

import javax.money.Monetary;
import javax.money.MonetaryAmount;

public class DefaultConverter implements MonetaryConverter {

  @Override
  public MonetaryAmount convert(String unit, Double amount) {
    return Monetary.getDefaultAmountFactory()
            .setCurrency(Monetary.getCurrency(unit))
            .setNumber(amount)
            .create();
  }
}
