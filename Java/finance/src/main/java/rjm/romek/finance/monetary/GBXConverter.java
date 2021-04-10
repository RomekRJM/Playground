package rjm.romek.finance.monetary;

import javax.money.MonetaryAmount;

public class GBXConverter implements MonetaryConverter {

  private static final String GBP = "GBP";
  private static final DefaultConverter DEFAULT_CONVERTER = new DefaultConverter();

  @Override
  public MonetaryAmount convert(String unit, Double amount) {
    return DEFAULT_CONVERTER.convert(GBP, amount / 100);
  }
}
