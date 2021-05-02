package rjm.romek.finance.monetary;

import javax.money.MonetaryAmount;
import javax.money.MonetaryException;

public class GBXConverter implements MonetaryConverter {

  private static final String GBP = "GBP";
  private static final String GBX = "GBX";
  private static final DefaultConverter DEFAULT_CONVERTER = new DefaultConverter();

  @Override
  public MonetaryAmount convert(String unit, Double amount) {
    if (!GBX.equals(unit)) {
      throw new MonetaryException(String.format("Can not convert %s to %s", unit, GBP));
    }

    return DEFAULT_CONVERTER.convert(GBP, amount / 100);
  }
}
