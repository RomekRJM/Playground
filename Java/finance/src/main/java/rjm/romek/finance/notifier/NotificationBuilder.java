package rjm.romek.finance.notifier;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.money.MonetaryAmount;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.monetary.MonetaryConverter;
import rjm.romek.finance.monetary.MonetaryFactory;
import rjm.romek.finance.datapoint.model.DataPoint;
import rjm.romek.finance.rule.PriceAboveRule;
import rjm.romek.finance.rule.PriceBelowRule;
import rjm.romek.finance.rule.Rule;

public class NotificationBuilder {

  private static final String MESSAGE =
      "%s has been %s the price point %s for %s times in a row."
          + " <a href=\"%s\">Click to see the chart</a>.<br/><br/>Data points: %s";
  private static final String SUBJECT = "Finance Alert";
  private final MonetaryFactory monetaryFactory = new MonetaryFactory();

  private static final Map<Class<? extends Rule>, String> meaning;

  static {
    meaning = new HashMap<>();
    meaning.put(PriceAboveRule.class, "above");
    meaning.put(PriceBelowRule.class, "below");
  }

  public Notification build(String advisorName, Alert what, List<DataPoint> dataPoints,
      String url) {
    return new Notification(
        String.format(
            MESSAGE,
            advisorName,
            meaning.get(what.getRule().getClass()),
            what.getRule().getTargetValue().getAmount(),
            what.getOccurrencesToActivate(),
            url,
            dataPointsAsString(dataPoints)
        ),
        SUBJECT
    );
  }

  private String dataPointsAsString(List<DataPoint> dataPoints) {
    StringBuilder sb = new StringBuilder(
        "<table border=\"1\"><tr><th>Date</th><th>Price</th><tr>");
    for (DataPoint dp : dataPoints) {
      MonetaryConverter monetaryConverter = monetaryFactory.create(dp.getCurrencyCode());
      MonetaryAmount monetaryAmount = monetaryConverter
          .convert(dp.getCurrencyCode(), dp.getValue());

      sb.append("<tr><td>");
      sb.append(dp.getDate());
      sb.append("</td><td>");
      sb.append(monetaryAmount);
      sb.append("</td></tr>");
    }

    sb.append("</table>");

    return sb.toString();
  }

}
