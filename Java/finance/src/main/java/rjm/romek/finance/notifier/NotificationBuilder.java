package rjm.romek.finance.notifier;

import java.util.Date;
import java.util.Map;
import javax.money.MonetaryAmount;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.rule.PriceAboveRule;
import rjm.romek.finance.rule.PriceBelowRule;
import rjm.romek.finance.rule.Rule;

public class NotificationBuilder {

  private static final String MESSAGE =
      "%s has been %s the price point %s for %s times in a row.<br/>Data points: ";
  private static final String SUBJECT = "Finance Alert";
  private static final String DP1 = ": ";
  private static final String DP2 = ", ";

  private static final Map<Class<? extends Rule>, String> meaning = Map.of(
      PriceAboveRule.class, "above",
      PriceBelowRule.class, "below"
  );

  public Notification build(String advisorName, Alert what, Map<Date, MonetaryAmount> when) {
    return new Notification(
        String.format(
            MESSAGE,
            advisorName,
            meaning.get(what.getRule().getClass()),
            what.getRule().getTargetValue().getAmount(),
            what.getOccurrencesToActivate()
        ) + dataPointsAsString(when),
        SUBJECT
    );
  }

  private String dataPointsAsString(Map<Date, MonetaryAmount> when) {
    StringBuilder sb = new StringBuilder();
    for (Date d : when.keySet()) {
      sb.append(d);
      sb.append(DP1);
      sb.append(when.get(d));
      sb.append(DP2);
    }

    return sb.length() > DP2.length() ?
        sb.delete(sb.length() - DP2.length(), sb.length()).toString() : sb.toString();
  }

}
