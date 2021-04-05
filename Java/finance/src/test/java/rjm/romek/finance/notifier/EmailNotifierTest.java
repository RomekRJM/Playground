package rjm.romek.finance.notifier;

import java.util.Map;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import rjm.romek.finance.DateUtil;
import rjm.romek.finance.MonetaryUtil;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.rule.PriceAboveRule;

@SpringBootTest
@ActiveProfiles(profiles = "test")
class EmailNotifierTest {

  @Autowired
  EmailNotifier emailNotifier;

  @Test
  public void shouldSendEmail() {
    emailNotifier.notify(
        new Alert(
            new PriceAboveRule(
                MonetaryUtil.getDollars(1234)
            ),
            2000
        ),
        Map.of(
            DateUtil.createDate(14, 11, 0), MonetaryUtil.getDollars(1500).getMonetaryAmount(),
            DateUtil.createDate(14, 12, 0), MonetaryUtil.getDollars(1502).getMonetaryAmount(),
            DateUtil.createDate(14, 13, 0), MonetaryUtil.getDollars(1506).getMonetaryAmount()
        )
    );
  }
}