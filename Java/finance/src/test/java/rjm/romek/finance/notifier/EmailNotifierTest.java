package rjm.romek.finance.notifier;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import rjm.romek.finance.MonetaryDateUtil;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.rule.PriceAboveRule;

@SpringBootTest
@ActiveProfiles(profiles = "test")
class EmailNotifierTest {

  private final EmailNotifier emailNotifier = new EmailNotifier("wawel@o2.pl", "mail.o2.pl", "457", "test",
      "test");

  @Test
  public void shouldSendEmail() {
    emailNotifier.notify(
        new Alert(
            new PriceAboveRule(
                MonetaryDateUtil.getDollars(1234)
            ),
            2000
        ),
        MonetaryDateUtil.createDataPoints("USD", 1500, 1501, 1501)
    );
  }
}