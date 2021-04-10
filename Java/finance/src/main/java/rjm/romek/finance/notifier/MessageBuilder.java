package rjm.romek.finance.notifier;

import java.util.Date;
import java.util.Map;
import javax.money.MonetaryAmount;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.rule.PriceAboveRule;
import rjm.romek.finance.rule.PriceBelowRule;
import rjm.romek.finance.rule.Rule;

public class MessageBuilder {

  private static final String MESSAGE =
      "{} has been {} the price point {} for {} times in a row.<br/>" +
          "Data points: {}";
  private static final String SUBJECT = "Finance Alert";
  private static final Map<Class<? extends Rule>, String> meaning = Map.of(
      PriceAboveRule.class, "above",
      PriceBelowRule.class, "below"
  );

  public Notification build(Alert what, Map<Date, MonetaryAmount> when) {
    return new Notification(String.format(MESSAGE, what.getOccurrencesToActivate()), SUBJECT);
  }


}
