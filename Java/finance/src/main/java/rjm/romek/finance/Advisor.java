package rjm.romek.finance;

import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import java.io.IOException;
import java.util.Date;
import java.util.Map;
import javax.money.MonetaryAmount;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.EmailNotifier;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;
import rjm.romek.finance.scraper.Grabber;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@JsonDeserialize
public class Advisor {

  private EmailNotifier notifier;
  private Grabber grabber;
  private String name;

  public void check(Alert alert) throws IOException, CouldNotGrabPriceException {
    Map<Date, MonetaryAmount> pricePoints = grabber.grabPrice();

    if (alert.checkTrigger(pricePoints)) {
      notifier.notify(alert, pricePoints);
    }

  }
}
