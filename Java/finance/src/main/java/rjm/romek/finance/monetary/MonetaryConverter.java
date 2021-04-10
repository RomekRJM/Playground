package rjm.romek.finance.monetary;

import javax.money.MonetaryAmount;

public interface MonetaryConverter {
  MonetaryAmount convert(String unit, Double amount);
}
