package rjm.romek.finance.rule;

import javax.money.MonetaryAmount;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public abstract class Rule {

  protected final MonetaryAmount targetValue;
  protected final RuleType type;

  public abstract boolean applies(MonetaryAmount value);
}
