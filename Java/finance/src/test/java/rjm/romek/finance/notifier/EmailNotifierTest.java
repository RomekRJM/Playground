package rjm.romek.finance.notifier;

import java.util.Map;
import javax.money.Monetary;
import javax.money.MonetaryAmount;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import rjm.romek.finance.DateUtil;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.rule.PriceAboveRule;

@SpringBootTest
class EmailNotifierTest {

  @Autowired
  EmailNotifier emailNotifier;

  @Test
  public void shouldSendEmail() {
    emailNotifier.notify("romek.rjm@gmail.com",
        new Alert(
            new PriceAboveRule(
                getDollars(1234)
            ),
            2000
        ),
        Map.of(
            DateUtil.createDate(14, 11, 00), getDollars(1500),
            DateUtil.createDate(14, 12, 00), getDollars(1502),
            DateUtil.createDate(14, 13, 00), getDollars(1506)
        )
    );
  }

  private MonetaryAmount getDollars(Integer amount) {
    return Monetary.getDefaultAmountFactory()
        .setCurrency(Monetary.getCurrency("USD"))
        .setNumber(amount)
        .create();
  }
}