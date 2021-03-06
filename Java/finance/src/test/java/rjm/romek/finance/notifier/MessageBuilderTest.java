package rjm.romek.finance.notifier;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.List;
import org.assertj.core.util.Lists;
import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryDateUtil;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.datapoint.model.DataPoint;
import rjm.romek.finance.rule.PriceAboveRule;

class MessageBuilderTest {

  private static final String ADVISOR = "adv";
  private static final String CURRENCY = "USD";

  private static final String EXPECTED = "Advisor has been above the price point 1234 for 2 times "
      + "in a row.<br/><a href=\"https://google.com\">Click to see the chart</a>.<br/><br/>"
      + "Data points: <table border=\"1\" style=\"background-color: lightgrey\"><tr ><th>Date"
      + "</th><th>Price</th><tr><tr style=\"background-color: white\"><td>"
      + "Sun Mar 12 14:10:00 CET 2045</td><td>USD 1500.00</td></tr>"
      + "<tr style=\"background-color: lightblue\"><td>Sun Mar 12 14:30:00 CET 2045</td>"
      + "<td>USD 1510.00</td></tr></table>";

  private final NotificationBuilder notificationBuilder = new NotificationBuilder();

  @Test
  public void testBuild() {
    List<DataPoint> dataPoints = Lists.list(
        new DataPoint(1L, MonetaryDateUtil.createDate(14, 10), ADVISOR, CURRENCY, 1500d),
        new DataPoint(2L, MonetaryDateUtil.createDate(14, 30), ADVISOR, CURRENCY, 1510d)
    );

    Notification notification = notificationBuilder.build("Advisor",
        new Alert(
            new PriceAboveRule(
                MonetaryDateUtil.getDollars(1234)
            ),
            2, 2
        ),
        dataPoints, "https://google.com"
    );

    assertEquals("Finance Alert for Advisor", notification.getSubject());
    assertEquals(EXPECTED, notification.getBody());
  }
}