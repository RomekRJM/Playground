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
      "%s has been %s the price point %s for %s times in a row.<br/>"
          + "<a href=\"%s\">Click to see the chart</a>.<br/><br/>Data points: %s";
  private static final String SUBJECT = "Finance Alert for %s";
  public static final String TR = "<tr style=\"background-color: %s\"><td>";
  public static final String TABLE = "<table border=\"1\" style=\"background-color: lightgrey\">"
      + "<tr ><th>Date</th><th>Price</th><tr>";
  public static final String WHITE = "white";
  public static final String LIGHTBLUE = "lightblue";
  public static final String TD = "</td><td>";
  public static final String TR_CLOSE = "</td></tr>";
  public static final String TABLE_CLOSE = "</table>";
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
        String.format(
            SUBJECT,
            advisorName
        )
    );
  }

  private String dataPointsAsString(List<DataPoint> dataPoints) {
    StringBuilder sb = new StringBuilder(TABLE);

    int index = 0;
    for (DataPoint dp : dataPoints) {
      MonetaryConverter monetaryConverter = monetaryFactory.create(dp.getCurrencyCode());
      MonetaryAmount monetaryAmount = monetaryConverter
          .convert(dp.getCurrencyCode(), dp.getValue());

      String color = index % 2 == 0 ? WHITE : LIGHTBLUE;

      sb.append(String.format(TR, color));
      sb.append(dp.getDate());
      sb.append(TD);
      sb.append(monetaryAmount);
      sb.append(TR_CLOSE);

      ++index;
    }

    sb.append(TABLE_CLOSE);

    return sb.toString();
  }

}
