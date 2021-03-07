package rjm.romek.finance.alert;

import lombok.Getter;
import lombok.RequiredArgsConstructor;
import rjm.romek.finance.rule.Rule;

import javax.money.MonetaryAmount;
import java.util.Date;

@Getter
@RequiredArgsConstructor
public abstract class Alert {

  private final MonetaryAmount target;
  private final Rule rule;

  public abstract boolean isTriggered(Date atTimestamp, MonetaryAmount value);
}
