package rjm.romek.finance.notifier;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.Date;
import java.util.SortedMap;
import java.util.TreeMap;
import javax.money.MonetaryAmount;
import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryDateUtil;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.rule.PriceAboveRule;

class MessageBuilderTest {

  private static final String EXPECTED = "Advisor has been above the price point 1234 for 2 "
      + "times in a row.<br/>Data points: Sun Mar 12 14:10:00 CET 2045: USD 1500.00, "
      + "Sun Mar 12 14:30:00 CET 2045: USD 1510.00";

  private NotificationBuilder notificationBuilder = new NotificationBuilder();

  @Test
  public void testBuild() {
    SortedMap<Date, MonetaryAmount> when = new TreeMap<>();
    when.put(MonetaryDateUtil.createDate(14, 10, 0),
        MonetaryDateUtil.getDollars(1500).getMonetaryAmount());
    when.put(MonetaryDateUtil.createDate(14, 30, 0),
        MonetaryDateUtil.getDollars(1510).getMonetaryAmount());

    Notification notification = notificationBuilder.build("Advisor",
        new Alert(
            new PriceAboveRule(
                MonetaryDateUtil.getDollars(1234)
            ),
            2
        ),
        when
    );

    assertEquals("Finance Alert", notification.getSubject());
    assertEquals(EXPECTED, notification.getBody());
  }
}